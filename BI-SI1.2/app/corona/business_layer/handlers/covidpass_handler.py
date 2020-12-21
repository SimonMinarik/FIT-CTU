from corona.business_layer.handlers.interfaces.covidpass_handler_interface import CovidpassHandlerInterface
from corona.data_layer.interfaces.data_access_factory import DataAccessFactory


class CovidpassHandler(CovidpassHandlerInterface):
    """!
    Implementation of CovidpassHandler interface
    """
    data_access_factory = DataAccessFactory()

    def create_covidpass(self, patient, covidtest):
        covidpass_data_access = self.data_access_factory.get_covidpass_data_access()
        covidpass_data_access.add_covidpass(patient=patient, covidtest=covidtest)
        return True
