from abc import ABC, abstractmethod


class CovidpassHandlerInterface(ABC):
    """!
    Interface of CovidpassHandler
    """
    @abstractmethod
    def create_covidpass(self, patient, covidtest):
        """!
        Method creates a new CovidPass instance
        @param patient: Patient database identifier
        @param covidtest: Covidtest database identifier
        @return: True if successful, otherwise false
        """
        pass
