from django.contrib.auth.models import User
from corona.data_layer.interfaces.user_data_access_interface import UserDataAccessInterface


class UserDataAccess(UserDataAccessInterface):
    """!
    Implementation of UserDataAccess interface
    """
    def add_user(self, username, password):
        user = User.objects.create_user(username=username, password=password)
        user.save()

    def edit_user(self, username):
        pass

    def get_user(self, username):
        return User.objects.filter(username=username)[0]
