from django.shortcuts import render
from django.views import View
from corona.data_layer.interfaces.data_access_factory import DataAccessFactory


class PatientView(View):
    """!
    View controller class that implements GET and POST methods for PatientView
    """
    def get(self, request):
        """!
        Method that handles GET request on the view
        @param request: request
        @return: render method, which renders the Patient html template with patient's CovidPasses
        """
        data_access_factory = DataAccessFactory()
        covidpass_data_access = data_access_factory.get_covidpass_data_access()
        patient_data_access = data_access_factory.get_patient_data_access()
        patient = patient_data_access.get_patient(request.user)
        patients_covidpasses = covidpass_data_access.get_all_patients_covidpasses(patient)
        return render(request, 'corona/patient.html', {'covidpasses': patients_covidpasses})
