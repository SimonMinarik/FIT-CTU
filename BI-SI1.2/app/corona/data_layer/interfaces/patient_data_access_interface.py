from abc import ABC, abstractmethod


class PatientDataAccessInterface(ABC):
    """!
    Interface of PatientDataAccess
    """
    @abstractmethod
    def add_patient(self, name, surname, birthid, email, phone, address, user):
        """!
        Method adds an instance of Patient to the database
        @param name: string, Name of the patient
        @param surname: string, Surname of the patient
        @param birthid: int, Patient's social security ID
        @param email: string, Patient's email address
        @param phone: string, Patient's phone number
        @param address: string, Patient's home address
        @param user: User database identifier
        @return: True if successful, otherwise false
        """
        pass

    @abstractmethod
    def get_patient(self, user_id):
        """!
        Method gets an instance of Patient based on User identifier
        @param user_id: User database identifier
        @return: Instance of Patient
        """
        pass
