from django.shortcuts import render
from django.views import View
from corona.forms import ReservationForm
from django.contrib import messages
from django.contrib.auth import login
from django.http import HttpResponseRedirect

from corona.data_layer.interfaces.data_access_factory import DataAccessFactory
from corona.business_layer.handlers.interfaces.handler_factory import HandlerFactory


class ReservationView(View):
    """!
    View controller class that implements GET and POST methods for ReservationView
    """
    form = ReservationForm
    data_access_factory = DataAccessFactory()
    handler_factory = HandlerFactory()

    def get(self, request):
        """!
        Method that handles GET request on the view
        @param request: request
        @return: render method, which renders the Reservation html template with a form
        """
        return render(request, 'corona/reservation.html', {'form': self.form})

    def post(self, request):
        """!
        Method that handles POST request on the view
        @param request: request
        @return: Redirect to Patient's site, if the reservation was successful, otherwise render method which renders the same page again
        """
        form = self.form(request.POST)
        reservation_handler = self.handler_factory.get_reservation_handler()
        covidpass_data_access = self.data_access_factory.get_covidpass_data_access()
        patient_handler = self.handler_factory.get_patient_handler()
        if form.is_valid():
            print("Form valid")
            patient = patient_handler.get_patient(request.user)
            reservation_handler.create_reservation(form.cleaned_data['deadline'], covidpass_data_access.get_active_covidpass(patient))
            return HttpResponseRedirect("/patient")
        else:
            messages.error(request, form.errors)
            print(form['deadline'])
        return render(request, 'corona/reservation.html', {'form': self.form})
