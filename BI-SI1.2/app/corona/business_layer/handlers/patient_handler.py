from corona.business_layer.handlers.interfaces.patient_handler_interface import PatientHandlerInterface
from corona.data_layer.interfaces.data_access_factory import DataAccessFactory


class PatientHandler(PatientHandlerInterface):
    """!
    Implementation of PatientHandler interface
    """
    data_access_factory = DataAccessFactory()

    def create_patient(self, name, surname, birthid, email, phone, address, user):
        patient_data_access = self.data_access_factory.get_patient_data_access()
        patient_data_access.add_patient(name=name, surname=surname, birthid=birthid, email=email, phone=phone, address=address, user=user)
        return True

    def get_patient(self, user):
        patient_data_access = self.data_access_factory.get_patient_data_access()
        return patient_data_access.get_patient(user)
