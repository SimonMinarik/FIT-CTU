import requests
import json
import csv

API_KEY = "17caa9ef18f0efe23fffa64ae0c6297b"

"""movies = [["movie_id", "original_title", "genre", "overview", "poster_path", "imdbId"]]
tmdb_ids = []
with open('links.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    line_count = 0
    for row in csv_reader:
        if line_count == 0:
            print(f'Column names are {", ".join(row)}')
            line_count += 1
        else:
            # print(f'\t{row[0]} works in the {row[1]} department, and was born in {row[2]}.')
            if row[2] != '':
                movies.append([row[0]])
                tmdb_ids.append(row[2])

deleted_movies = []
file = open('movie_db.csv', 'a', newline='')
writer = csv.writer(file, delimiter='|')
for x, y in zip(movies[8800:], tmdb_ids[8800:]):
    MOVIE_ID = y
    request = 'https://api.themoviedb.org/3/movie/' + str(MOVIE_ID) + '?api_key=' + API_KEY
    answer = requests.get(request)
    movie_info = json.loads(answer.text)
    print("MOVIE_ID:", y)
    if answer.status_code == 200:
        # x.append(movie_info["title"])
        if len(movie_info["genres"]) > 0:
            x.append(movie_info["genres"][0]["name"])
            writer.writerow([x[0], movie_info["title"], movie_info["genres"][0]["name"], movie_info["overview"], movie_info["poster_path"], movie_info["imdb_id"]])
        else:
            writer.writerow([x[0], movie_info["title"], "Unspecified", movie_info["overview"], movie_info["poster_path"], movie_info["imdb_id"]])
        # x.append(movie_info["overview"])
        # x.append(movie_info["poster_path"])
        # x.append(movie_info["imdb_id"])
        print(movie_info["title"])
    else:
        deleted_movies.append(x[0])
        movies.remove(x)
        tmdb_ids.remove(y)

print("removed movies:", deleted_movies)
"""

movies = [{}]
with open('movie_db.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter='|')
    line_count = 0
    for row in csv_reader:
        if line_count == 0:
            print(f'Column names are {", ".join(row)}')
            line_count += 1
        else:
            # print(f'\t{row[0]} works in the {row[1]} department, and was born in {row[2]}.')
            movies.append({"movieId": row[0], "title": row[1], "genre": row[2], "overview": row[3], "poster_path": row[4], "imdbId": row[5]})

new_ratings = open('new_ratings.csv', 'w', newline='')
writer = csv.writer(new_ratings, delimiter='|')
writer.writerow(["userId", "movieId", "rating"])
with open('ratings.csv') as ratings:
    ratings_reader = csv.reader(ratings, delimiter=',')
    line_count = 0
    for row in ratings_reader:
        if line_count == 0:
            line_count += 1
        else:
            if row[1] in movies:
                writer.writerow([row[0], row[1], row[2]])
