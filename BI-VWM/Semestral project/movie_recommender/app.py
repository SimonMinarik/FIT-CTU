from flask import Flask, render_template, url_for, request, redirect
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy import ForeignKey
from sqlalchemy.orm import relationship
import pandas as pd
from recommend import recommend
from helpers import to_dict

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///test.db'
app.jinja_env.filters['zip'] = zip
db = SQLAlchemy(app)
movies_dict = {}
ratings_dict = {}
movies_df = pd.DataFrame()
ratings_df = pd.DataFrame()
n_neighbours = 30
loaded_data = False


class Rating(db.Model):
    __tablename__ = 'ratings'
    id = db.Column(db.Integer, primary_key=True)
    userId = db.Column(db.Integer, ForeignKey('users.id'))
    movieId = db.Column(db.Integer, nullable=False)
    rating = db.Column(db.String(5), nullable=False)
    user = relationship("User", back_populates="ratings")


class User(db.Model):
    __tablename__ = 'users'
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(50), nullable=False)

    def __repr__(self):
        return "<User(id='%r', name='%s')>" % (self.id, self.name)


User.ratings = relationship("Rating", order_by=Rating.id, back_populates="user")


class Movie(db.Model):
    __tablename__ = 'movie'
    id = db.Column(db.Integer, primary_key=True)
    movieId = db.Column(db.Integer, nullable=False)
    title = db.Column(db.String(200), nullable=False)
    genre = db.Column(db.String(50))
    overview = db.Column(db.String(1000))
    poster = db.Column(db.String(100))
    imdbId = db.Column(db.String(20))


@app.route('/movies', methods=['POST', 'GET'])
def login():
    userId = request.form['user']
    print(userId)
    user = User.query.get_or_404(int(userId))
    user = to_dict("user", user)
    ids, score, time_cosine, time_preprocess = recommend(ratings_df, int(userId), n_neighbours)
    recommendations = to_dict("recommendations", [ids, score])
    return render_template('movies.html', movies=movies_dict, user=user, recommendations=recommendations, time_cosine=time_cosine, time_preprocess=time_preprocess)


@app.route('/change_rating/<int:userId>/<int:movieId>', methods=['POST', 'GET'])
def change_rating(userId, movieId):
    user = User.query.get_or_404(userId)
    global ratings_df
    if request.form["myselect"] == "Delete":
        for rating in user.ratings:
            if rating.movieId == movieId:
                db.session.delete(rating)
                break
        user_list = ratings_df.index[ratings_df['userId'] == userId].tolist()
        movie_list = ratings_df.index[ratings_df['movieId'] == movieId].tolist()
        index = [value for value in user_list if value in movie_list]
        ratings_df = ratings_df.drop(index)
    else:
        user_ratings = []
        for rating in user.ratings:
            user_ratings.append(rating)
            if rating.movieId == movieId:
                rating.rating = float(request.form["myselect"])
                break
        user_list = ratings_df.index[ratings_df['userId'] == userId].tolist()
        movie_list = ratings_df.index[ratings_df['movieId'] == movieId].tolist()
        ratings_df.at[[value for value in user_list if value in movie_list][0], 'rating'] = float(
            request.form["myselect"])
    db.session.commit()
    user = to_dict("user", user)
    ids, score, time_cosine, time_preprocess = recommend(ratings_df, userId, n_neighbours)
    recommendations = to_dict("recommendations", [ids, score])
    return render_template('movies.html', movies=movies_dict, user=user, recommendations=recommendations, time_cosine=time_cosine, time_preprocess=time_preprocess)


@app.route('/change_rating_admin/<int:userId>/<int:movieId>', methods=['POST', 'GET'])
def change_rating_admin(userId, movieId):
    user = User.query.get_or_404(userId)
    global ratings_df
    if request.form["myselect"] == "Delete":
        for rating in user.ratings:
            if rating.movieId == movieId:
                db.session.delete(rating)
                break
        user_list = ratings_df.index[ratings_df['userId'] == userId].tolist()
        movie_list = ratings_df.index[ratings_df['movieId'] == movieId].tolist()
        index = [value for value in user_list if value in movie_list]
        ratings_df = ratings_df.drop(index)
    else:
        user_ratings = []
        for rating in user.ratings:
            user_ratings.append(rating)
            if rating.movieId == movieId:
                rating.rating = float(request.form["myselect"])
                break
        user_list = ratings_df.index[ratings_df['userId'] == userId].tolist()
        movie_list = ratings_df.index[ratings_df['movieId'] == movieId].tolist()
        ratings_df.at[[value for value in user_list if value in movie_list][0], 'rating'] = float(
            request.form["myselect"])
    db.session.commit()
    return render_template('admin.html', movies=movies_dict, users=to_dict("users", User.query.all()),
                           selected_user=to_dict("user", user))


@app.route('/add_rating/<int:userId>/<int:movieId>', methods=['POST', 'GET'])
def add_rating(userId, movieId):
    user = User.query.get_or_404(userId)
    global ratings_df
    user_ratings = []
    for rating in user.ratings:
        user_ratings.append(rating)
    user_ratings.append(Rating(movieId=movieId, rating=float(request.form["myselect"])))
    user.ratings = user_ratings
    db.session.commit()
    user = to_dict("user", user)
    ratings_df = ratings_df.append(
        {'movieId': movieId, 'rating': float(request.form["myselect"]), "userId": float(userId)}, ignore_index=True)
    ids, score, time_cosine, time_preprocess = recommend(ratings_df, userId, n_neighbours)
    recommendations = to_dict("recommendations", [ids, score])
    return render_template('movies.html', movies=movies_dict, user=user, recommendations=recommendations, time_cosine=time_cosine, time_preprocess=time_preprocess)


@app.route('/change_user', methods=["POST", "GET"])
def change_user():
    return render_template('admin.html', movies=movies_dict, users=to_dict("users", User.query.all()),
                           selected_user=to_dict("user", User.query.get_or_404(request.form["myselect"])))


@app.route('/admin', methods=["POST", "GET"])
def admin():
    if request.method == "POST":
        global n_neighbours
        n_neighbours = int(request.form['neighbours'])
    return render_template('admin.html', movies=movies_dict, users=to_dict("users", User.query.all()),
                           selected_user=to_dict("user", User.query.first()), neighbours=n_neighbours)


@app.route('/reset', methods=['POST', 'GET'])
def reset():
    # deleteUsers()
    # addUsers()
    # addMovies()
    return redirect('/')


@app.route('/', methods=['POST', 'GET'])
def index():
    if request.method == 'POST':
        return render_template('index.html')
    else:
        global loaded_data
        if not loaded_data:
            users = User.query.all()
            movies = Movie.query.all()
            global movies_dict, ratings_dict, movies_df, ratings_df
            movies_dict = to_dict("movies", movies)
            movies_df = pd.DataFrame.from_dict(movies_dict).T
            print(movies_df.head())
            ratings_dict = to_dict("ratings", users)
            ratings_df = pd.DataFrame.from_dict(ratings_dict).T
            print(ratings_df.head())
            loaded_data = True

        return render_template('index.html')


if __name__ == "__main__":
    app.run(debug=True)
