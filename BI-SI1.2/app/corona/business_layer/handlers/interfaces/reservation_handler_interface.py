from abc import ABC, abstractmethod


class ReservationHandlerInterface(ABC):
    """!
    Interface of ReservationHandler
    """
    @abstractmethod
    def create_reservation(self, deadline, covidpass):
        """!
        Method creates a new instance of Reservation
        @param deadline: datetime, Deadline of the test
        @param patient: Patient database identifier
        @param covidpass: Covidpass database identifier
        @return: True if successful, otherwise False
        """
        pass
