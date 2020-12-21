from abc import ABC, abstractmethod


class UserHandlerInterface(ABC):
    """!
    Interface of UserHandler
    """
    @abstractmethod
    def create_user(self, username, password):
        """!
        Method creates a new instance of User
        @param username: string, User's username
        @param password: string, User's password
        @return: True if successful, otherwise False
        """
        pass

    @abstractmethod
    def check_password(self, username, password):
        """!
        Method checks, if the password passed in a form matches the one in the database
        @param username: string, User's username
        @param password: string, User's password
        @return: True if successful, otherwise False
        """
        pass
