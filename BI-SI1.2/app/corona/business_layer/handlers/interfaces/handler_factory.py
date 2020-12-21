from corona.business_layer.handlers.patient_handler import PatientHandler
from corona.business_layer.handlers.covidpass_handler import CovidpassHandler
from corona.business_layer.handlers.reservation_handler import ReservationHandler
from corona.business_layer.handlers.user_handler import UserHandler


class HandlerFactory:
    """!
    Factory implementation which returns instances of handler implementation classes
    """
    __patient_handler = PatientHandler()
    __covidpass_handler = CovidpassHandler()
    __reservation_handler = ReservationHandler()
    __user_handler = UserHandler()

    def get_patient_handler(self):
        """!
        Method returns an instance of PatientHandler class
        @return: PatientHandler implementation
        """
        return self.__patient_handler

    def get_covidpass_handler(self):
        """!
        Method returns an instance of CovidPassHandler class
        @return: CovidPassHandler implementation
        """
        return self.__covidpass_handler

    def get_reservation_handler(self):
        """!
        Method returns an instance of ReservationHandler class
        @return: ReservationHandler implementation
        """
        return self.__reservation_handler

    def get_user_handler(self):
        """!
        Method returns an instance of UserHandler class
        @return: UserHandler implementation
        """
        return self.__user_handler
