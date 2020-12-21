from corona.data_layer.interfaces.patient_data_access_interface import PatientDataAccessInterface
from corona.models import Patient


class PatientDataAccess(PatientDataAccessInterface):
    """!
    Implementation of PatientDataAccess interface
    """
    def add_patient(self, name, surname, birthid, email, phone, address, user):
        patient = Patient(name=name, surname=surname, birthid=birthid, email=email, phone=phone, address=address, user=user)
        patient.save()
        return patient

    def get_patient(self, user_id):
        return Patient.objects.filter(user=user_id)[0]
