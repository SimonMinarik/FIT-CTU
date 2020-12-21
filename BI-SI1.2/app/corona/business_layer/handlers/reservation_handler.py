from corona.business_layer.handlers.interfaces.reservation_handler_interface import ReservationHandlerInterface
from corona.data_layer.interfaces.data_access_factory import DataAccessFactory
from datetime import datetime


class ReservationHandler(ReservationHandlerInterface):
    """!
    Implementation of ReservationHandler interface
    """
    data_access_factory = DataAccessFactory()

    def create_reservation(self, deadline, covidpass):
        reservation_data_access = self.data_access_factory.get_reservation_data_access()
        reservation_data_access.add_reservation(createdate=datetime.now().strftime('%Y-%m-%d %H:%M'), deadline=deadline, covidpass=covidpass)
        return True
