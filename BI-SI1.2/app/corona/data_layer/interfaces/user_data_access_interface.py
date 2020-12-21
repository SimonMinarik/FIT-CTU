from abc import ABC, abstractmethod


class UserDataAccessInterface(ABC):
    """!
    Interface of UserDataAccess
    """
    @abstractmethod
    def add_user(self, username, password):
        """!
        Method adds an instance of User to the database
        @param username: string, User's username
        @param password: string, User's password
        @return: True if successful, otherwise false
        """
        pass

    @abstractmethod
    def edit_user(self, username):
        """!
        Method edits User instance based on his username
        @param username: User's username
        @return: True if successful, otherwise false
        """
        pass

    @abstractmethod
    def get_user(self, username):
        """!
        Method gets an instance of User based on his username
        @param username: string, User's username
        @return: Instance of User
        """
        pass
