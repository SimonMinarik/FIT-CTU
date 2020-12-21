from django.shortcuts import render
from django.views import View
from corona.forms import LoginForm
from django.contrib import messages
from django.contrib.auth import login
from django.http import HttpResponseRedirect

from corona.data_layer.interfaces.data_access_factory import DataAccessFactory
from corona.business_layer.handlers.interfaces.handler_factory import HandlerFactory


class DoctorLoginView(View):
    """!
    View controller class that implements GET and POST methods for DoctorLoginView
    """
    form = LoginForm
    data_access_factory = DataAccessFactory()
    handler_factory = HandlerFactory()

    def get(self, request):
        """!
        Method that handles GET request on the view
        @param request: request
        @return: render method, which renders the DoctorLogin html template with a form
        """
        return render(request, 'corona/doctor_login.html', {'form': self.form})

    def post(self, request):
        """!
        Method that handles POST request on the view
        @param request: request
        @return: Redirect to Doctor's site, if the login was successful, otherwise render method which renders the same page again
        """
        user_data_access = self.data_access_factory.get_user_data_access()
        user_handler = self.handler_factory.get_user_handler()
        form = self.form(request.POST)
        if form.is_valid():
            if user_handler.check_password(form.cleaned_data['username'], form.cleaned_data['password']):
                login(request, user_data_access.get_user(form.cleaned_data['username']))
                return HttpResponseRedirect('/doctor')
            else:
                messages.error(request, 'Spatne heslo')
        return render(request, 'corona/doctor_login.html', {'form': form})
