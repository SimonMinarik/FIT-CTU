from corona.data_layer.interfaces.covidtest_data_access_interface import CovidtestDataAccessInterface
from corona.models import CovidTest


class CovidtestDataAccess(CovidtestDataAccessInterface):
    """!
    Implementation of CovidtestDataAccess interface
    """
    def add_covidtest(self, waitdays, price, type):
        covidtest = CovidTest(waitdays, price, type)
        covidtest.save()
        return True

    def get_covidtest(self, type):
        return CovidTest.objects.filter(type=type)[0]
