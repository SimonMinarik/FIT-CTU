from django.shortcuts import render
from django.views import View
from django.http import HttpResponseRedirect
from django.contrib.auth import login

from corona.data_layer.interfaces.data_access_factory import DataAccessFactory
from corona.business_layer.handlers.interfaces.handler_factory import HandlerFactory
from corona.forms import PatientRegisterForm


class DoctorRegisterPatientView(View):
    """!
    View controller class that implements GET and POST methods for DoctorRegisterPatientView
    """
    form = PatientRegisterForm
    data_access_factory = DataAccessFactory()
    handler_factory = HandlerFactory()

    def get(self, request):
        """!
        Method that handles GET request on the view
        @param request: request
        @return: render method, which renders the DoctorRegister html template with a form
        """
        return render(request, 'corona/doctor_register_patient.html', dict(form=self.form))

    def post(self, request):
        """!
        Method that handles POST request on the view
        @param request: request
        @return: Redirect to Doctor's site, if the registration was successful, otherwise render method which renders the same page again
        """
        user_handler = self.handler_factory.get_user_handler()
        patient_handler = self.handler_factory.get_patient_handler()
        user_data_access = self.data_access_factory.get_user_data_access()
        covid_pass_handler = self.handler_factory.get_covidpass_handler()
        covidtest_data_access = self.data_access_factory.get_covidtest_data_access()
        form = self.form(request.POST)
        if form.is_valid():
            user_handler.create_user(username=form.cleaned_data['username'], password=form.cleaned_data['password'])
            user = user_data_access.get_user(form.cleaned_data['username'])
            patient_handler.create_patient(name=form.cleaned_data['name'], surname=form.cleaned_data['surname'], birthid=form.cleaned_data['birthid'], email=form.cleaned_data['email'], phone=form.cleaned_data['phone'], address=form.cleaned_data['address'], user=user)
            covid_pass_handler.create_covidpass(patient_handler.get_patient(user), covidtest_data_access.get_covidtest(form.cleaned_data['covidtest']))
            return HttpResponseRedirect('/doctor')
        else:
            print("Invalid form")
            return render(request, 'corona/doctor_register_patient.html', dict(form=self.form))
