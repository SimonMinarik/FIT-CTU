from abc import ABC, abstractmethod


class ReservationDataAccessInterface(ABC):
    """!
    Interface of ReservationDataAccess
    """
    @abstractmethod
    def add_reservation(self, createdate, deadline, covidpass):
        """!
        Method adds an instance of Reservation to the database
        @param createdate: datetime, Date, when the reservation was created
        @param deadline: datetime, Deadline of the test
        @param covidpass: CovidPass database identifier
        @return: True if successful, otherwise false
        """
        pass

    @abstractmethod
    def get_reservation(self, covidpass):
        """!
        Method gets an instance of Reservation based on CovidPass
        @param covidpass: CovidPass database identifier
        @return: Instance of Reservation
        """
        pass
