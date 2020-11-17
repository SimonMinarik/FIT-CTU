import csv
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
movies = {}
with open('movie_db.csv') as ratings:
    movie_db_reader = csv.reader(ratings, delimiter='|')
    line_count = 0
    for row in movie_db_reader:
        if line_count == 0:
            line_count += 1
        else:
            movies[row[0]] = row[1]

x = input("User: ")
for user in users[x]:
    print(f'{movies[user[0]]}: {user[1]}')
