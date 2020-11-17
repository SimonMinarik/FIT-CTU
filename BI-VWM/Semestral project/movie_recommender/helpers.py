def to_dict(x, obj):
    output = {}
    counter = 0
    if x == "user":
        output["username"] = obj.name
        output["ratings"] = {}
        for rating in obj.ratings:
            output["ratings"][rating.movieId] = rating.rating
    elif x == "users":
        for user in obj:
            output[user.name] = user.name
    elif x == "movies":
        for movie in obj:
            output[movie.movieId] = {"movieId": movie.movieId, "title": movie.title, "genre": movie.genre,
                                     "overview": movie.overview,
                                     "poster": movie.poster, "imdbId": movie.imdbId}
    elif x == "ratings":
        for user in obj:
            for rating in user.ratings:
                output[counter] = {"userId": rating.userId, "movieId": rating.movieId, "rating": float(rating.rating)}
                counter += 1
    elif x == "recommendations":
        for id, score in zip(obj[0], obj[1]):
            output[int(id)] = score
    # print(output)
    return output
