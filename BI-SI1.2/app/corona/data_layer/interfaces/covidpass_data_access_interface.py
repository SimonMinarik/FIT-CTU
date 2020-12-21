from abc import ABC, abstractmethod


class CovidpassDataAccessInterface(ABC):
    """!
    Interface of CovidPassDataAccess
    """
    @abstractmethod
    def add_covidpass(self, patient, covidtest):
        """!
        Method add an Covidpass instance to the database
        @param patient: Patient databse identifier
        @param covidtest: Covidtest database identifier
        @return: True if successful, otherwise False
        """
        pass

    @abstractmethod
    def get_active_covidpass(self, patient):
        """!
        Method gets an active CovidPass
        @param patient: Patient database identifier
        @return: Instance of CovidPass
        """
        pass

    @abstractmethod
    def get_all_patients_covidpasses(self, patient):
        """!
        Method get all patient's CovidPasses, active or inactive
        @param patient: Patient database identifier
        @return: List of all patient's CovidPasses
        """
        pass