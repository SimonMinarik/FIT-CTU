from abc import ABC, abstractmethod


class PatientHandlerInterface(ABC):
    """!
    Interface of PatientHandler
    """
    @abstractmethod
    def create_patient(self, name, surname, birthid, email, phone, address, user):
        """!
        Method creates a new Patient instance
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
    def get_patient(self, user):
        """!
        Method gets the database instance of the Patient based on his user identifier
        @param user: User database identifier
        @return: Patient database instance
        """
        pass
