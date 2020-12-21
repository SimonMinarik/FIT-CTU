from django.shortcuts import render
from django.views import View


class DoctorView(View):
    """!
    View controller class that implements GET and POST methods for DoctorView
    """
    def get(self, request):
        """!
        Method that handles GET request on the view
        @param request: request
        @return: render method, which renders the Doctor html template
        """
        return render(request, 'corona/doctor.html')