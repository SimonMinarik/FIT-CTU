from abc import ABC, abstractmethod


class CovidtestDataAccessInterface(ABC):
    """!
    Interface of CovidtestDataAccess
    """
    @abstractmethod
    def add_covidtest(self, waitdays, price, type):
        """!
        Method adds a CovidTest instance to the database
        @param waitdays: int, Number of days it takes to get a result
        @param price: int, Price of the test
        @param type: string, Type of the test
        @return: True if successful, otherwise False
        """
        pass

    @abstractmethod
    def get_covidtest(self, type):
        """!
        Method gets a CovidTest instance based on the type of the test
        @param type: string, Type of the test
        @return: CovidTest instance
        """
        pass
