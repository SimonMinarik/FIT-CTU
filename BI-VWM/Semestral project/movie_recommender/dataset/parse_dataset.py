import csv

ratingz = {}
with open('new_ratings.csv') as ratings:
    ratings_reader = csv.reader(ratings, delimiter='|')
    line_count = 0
    for row in ratings_reader:
        if line_count == 0:
            line_count += 1
        else:
            if row[0] not in ratingz:
                ratingz[row[0]] = [Rating(movieId=int(row[1]), rating=row[2])]
            else:
                ratingz[row[0]].append(Rating(movieId=int(row[1]), rating=row[2]))

def addUsers():
    users = {}
    with open('new_ratings.csv') as ratings:
        ratings_reader = csv.reader(ratings, delimiter='|')
        line_count = 0
        for row in ratings_reader:
            if line_count == 0:
                line_count += 1
            else:
                if row[0] not in users:
                    users[row[0]] = [(row[1], row[2])]
                else:
                    users[row[0]].append((row[1], row[2]))
    for user in users.keys():
        new_user = User(name=user)
        new_user.ratings = ratingz[new_user.name]
        db.session.add(new_user)
        db.session.commit()


def deleteUsers():
    users = User.query.all()
    for user in users:
        try:
            db.session.delete(user)
            db.session.commit()
        except:
            return 'There was an issue deleting user'


def addMovies():
    movies = []
    with open('movie_db.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter='|')
        line_count = 0
        for row in csv_reader:
            if line_count == 0:
                print(f'Column names are {", ".join(row)}')
                line_count += 1
            else:
                movies.append(
                    {"movieId": row[0], "title": row[1], "genre": row[2], "overview": row[3], "poster_path": row[4],
                     "imdbId": row[5]})
    for movie in movies:
        new_movie = Movie(movieId=int(movie["movieId"]), title=movie["title"], genre=movie["genre"],
                          overview=movie["overview"], poster=movie["poster_path"], imdbId=movie["imdbId"])
        db.session.add(new_movie)
        db.session.commit()
