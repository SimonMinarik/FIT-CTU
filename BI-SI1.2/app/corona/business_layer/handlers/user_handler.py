from corona.business_layer.handlers.interfaces.user_handler_interface import UserHandlerInterface
from corona.data_layer.interfaces.data_access_factory import DataAccessFactory


class UserHandler(UserHandlerInterface):
    """!
    Implementation of UserHandler interface
    """
    data_access_factory = DataAccessFactory()

    def create_user(self, username, password):
        user_data_access = self.data_access_factory.get_user_data_access()
        user_data_access.add_user(username=username, password=password)
        return True

    def check_password(self, username, password):
        user_data_access = self.data_access_factory.get_user_data_access()
        return user_data_access.get_user(username).check_password(password)
