from django.shortcuts import render
from django.views import View


class IndexView(View):
    """!
    View controller class that implements GET and POST methods for IndexView
    """
    def get(self, request):
        """!
        Method that handles GET request on the view
        @param request: request
        @return: render method, which renders the Index html template
        """
        return render(request, 'corona/index.html')

