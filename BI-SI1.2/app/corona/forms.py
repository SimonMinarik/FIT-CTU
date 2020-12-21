from django import forms
from corona.models import HygienicStation, CovidTest


class LoginForm(forms.Form):
    """!
    Form for logging in, using Django's form implementation class
    """
    username = forms.CharField(label='Uzivatelske jmeno', required=True)
    password = forms.CharField(label='Heslo', widget=forms.PasswordInput, required=True)


class PatientRegisterForm(forms.Form):
    """!
    Form for patient registration, using Django's form implementation class
    """
    username = forms.CharField(label='Uzivatelske jmeno', required=True)
    password = forms.CharField(label='Heslo', widget=forms.PasswordInput, required=True)
    name = forms.CharField(label='Jmeno', required=True)
    surname = forms.CharField(label='Prijmeni', required=True)
    birthid = forms.IntegerField(label='Rodne cislo', required=True)
    email = forms.EmailField(label='Email', required=True)
    phone = forms.CharField(label='Telefonni cislo', required=True)
    address = forms.CharField(label='Adresa', required=True)
    covidtest = forms.ModelChoiceField(CovidTest.objects.all(), label='Typ testu', required=True)


class ReservationForm(forms.Form):
    """!
    Form for reservation, using Django's form implementation class
    """
    deadline = forms.DateTimeField(
        input_formats=['%d.%m.%Y %H:%M'],
        label='Termin'
    )
    hygienicstation = forms.ModelChoiceField(HygienicStation.objects.all(), label='Hygienicka stanice')
