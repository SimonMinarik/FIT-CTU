import pandas as pd
import numpy as np
import time


# Find n neighbours (similar users) to user
def find_n_neighbours(df, n):
    df = df.apply(lambda x: pd.Series(x.sort_values(ascending=False)
                                      .iloc[:n].index,
                                      index=['top{}'.format(i) for i in range(1, n + 1)]), axis=1)
    return df


# Get recommended movies based on the calculated score value
def calculate_score(check, sim_user_m, movie_user, final_movie, Mean, similarity_with_movie, user):
    movies_seen_by_user = check.columns[check[check.index == user].notna().any()].tolist()

    similar_users = sim_user_m.values.squeeze().tolist()

    l = ','.join(movie_user[movie_user.index.isin(similar_users)].values)
    movie_seen_by_similar_users = l.split(',')

    movies_under_consideration = list(set(movie_seen_by_similar_users) - set(list(map(str, movies_seen_by_user))))
    movies_under_consideration = list(map(float, movies_under_consideration))

    # Calculate score for each movie under consideration for selected user
    score = []
    for item in movies_under_consideration:
        c = final_movie.loc[:, item]
        d = c[c.index.isin(similar_users)]
        f = d[d.notnull()]
        avg_user = Mean.loc[Mean['userId'] == user, 'rating'].values[0]
        index = f.index.values.squeeze().tolist()
        corr = similarity_with_movie.loc[user, index]
        fin = pd.concat([f, corr], axis=1)
        fin.columns = ['adg_score', 'correlation']
        fin['score'] = fin.apply(lambda x: x['adg_score'] * x['correlation'], axis=1)
        nume = fin['score'].sum()
        deno = fin['correlation'].sum()
        final_score = avg_user + (nume / deno)
        score.append(final_score)
    data = pd.DataFrame({'movieId': movies_under_consideration, 'score': score})
    top_recommendation = data.sort_values(by='score', ascending=False).head(10)
    return top_recommendation.movieId.values.tolist(), top_recommendation.score.values.tolist()


# Calculate cosine similarity of pairwise matrix
def cosine_similarity(X):
    norm = pd.DataFrame(np.sqrt(np.square(X).sum(axis=1)))
    denominator = norm.dot(norm.T)
    numerator = X.dot(X.T)
    similarity_matrix = numerator.divide(denominator, axis=0)
    return similarity_matrix.to_numpy()


def recommend(ratings_df, user, n_neighbours):
    start_preprocess = time.time()

    # Normalize user ratings
    mean = ratings_df.groupby(by="userId", as_index=False)['rating'].mean()
    rating_avg = pd.merge(ratings_df, mean, on='userId')
    rating_avg['adg_rating'] = rating_avg['rating_x'] - rating_avg['rating_y']

    # Prepare the data
    check = pd.pivot_table(rating_avg, values='rating_x', index='userId', columns='movieId')
    final = pd.pivot_table(rating_avg, values='adg_rating', index='userId', columns='movieId')

    # Fill NaNs - the database is sparse, movie average over columns
    final_movie = final.fillna(final.mean(axis=0))
    final_user = final.apply(lambda row: row.fillna(row.mean()), axis=1)

    start_cosine = time.time()
    cosine = cosine_similarity(final_movie)
    np.fill_diagonal(cosine, 0)
    similarity_with_movie = pd.DataFrame(cosine, index=final_movie.index)
    similarity_with_movie.columns = final_user.index

    sim_user_m = find_n_neighbours(similarity_with_movie.iloc[[user - 1]], n_neighbours)

    rating_avg = rating_avg.astype({"movieId": str})
    movie_user = rating_avg.groupby(by='userId')['movieId'].apply(lambda x: ','.join(x))

    predicted_movies_id, predicted_movies_score = calculate_score(check, sim_user_m, movie_user, final_movie, mean,
                                                                  similarity_with_movie, user)
    return predicted_movies_id, predicted_movies_score, time.time() - start_cosine, time.time() - start_preprocess
