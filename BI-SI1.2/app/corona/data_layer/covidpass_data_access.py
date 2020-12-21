from corona.data_layer.interfaces.covidpass_data_access_interface import CovidpassDataAccessInterface
from corona.models import CovidPass


class CovidpassDataAccess(CovidpassDataAccessInterface):
    """!
    Implementation of CovidpassDataAccess interface
    """
    def add_covidpass(self, patient, covidtest):
        covidpass = CovidPass(patient=patient, covidtest=covidtest)
        covidpass.save()
        return True

    def get_active_covidpass(self, patient):
        print(f'patient: {patient}')
        covidpasses = self.get_all_patients_covidpasses(patient)
        for covidpass in covidpasses:
            if "Aktivní" in covidpass.__str__().split(' '):
                return covidpass
        return None

    def get_all_patients_covidpasses(self, patient):
        return CovidPass.objects.filter(patient=patient)
