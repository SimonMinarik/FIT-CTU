from django.contrib.auth import logout
from django.http import HttpResponseRedirect
from django.views import View


class LogoutView(View):
    """!
    View controller class that implements GET and POST methods for LogoutView
    """
    def get(self, request):
        """!
        Method which handles GET request on the view and logs out the user
        @param request: request
        @return: redirect to Index
        """
        logout(request)
        return HttpResponseRedirect("/")
