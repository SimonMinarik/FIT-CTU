"""!
Models representing database
"""
from django.db import models
from django.contrib.auth.models import User


class Patient(models.Model):
    """!
    Class of Patient database model, using Django's ORM implementation
    """
    name = models.TextField()
    surname = models.TextField()
    birthid = models.CharField(max_length=11)
    email = models.TextField()
    phone = models.TextField()
    address = models.TextField()
    user = models.ForeignKey(User, on_delete=models.CASCADE)

    def __str__(self):
        return f'{self.name} {self.surname}'


class HygienicStation(models.Model):
    """!
    Class of HygienicStation database model, using Django's ORM implementation
    """
    address = models.TextField()
    manager = models.TextField()
    openhour = models.TimeField()
    closehour = models.TimeField()

    def __str__(self):
        return self.address


class Facility(models.Model):
    """!
    Class of Facility database model, using Django's ORM implementation
    """
    address = models.TextField()


class Place(models.Model):
    """!
    Class of Place database model, using Django's ORM implementation
    """
    bed = models.TextField()
    standard = models.TextField(blank=True, null=True)
    facility = models.ForeignKey(Facility, on_delete=models.CASCADE)


class Quarantine(models.Model):
    """!
    Class of Quarantine database model, using Django's ORM implementation
    """
    startdate = models.DateField()
    duration = models.IntegerField()
    patient = models.ForeignKey(Patient, on_delete=models.CASCADE)
    place = models.ForeignKey(Place, on_delete=models.CASCADE)


class CovidTest(models.Model):
    """!
    Class of CovidTest database model, using Django's ORM implementation
    """
    waitdays = models.IntegerField()
    price = models.DecimalField(max_digits=10, decimal_places=2)
    type = models.TextField()

    def __str__(self):
        return self.type


class CovidPass(models.Model):
    """!
    Class of CovidPass database model, using Django's ORM implementation
    """
    TEST_RESULTS = [
        ('POS', 'Positive'),
        ('NEG', 'Negative')
    ]
    testresult = models.CharField(max_length=3, choices=TEST_RESULTS, blank=True, null=True)
    testdate = models.DateField(blank=True, null=True)
    patient = models.ForeignKey(Patient, on_delete=models.CASCADE)
    hygienicstation = models.ForeignKey(HygienicStation, on_delete=models.CASCADE, null=True, blank=True)
    covidtest = models.ForeignKey(CovidTest, on_delete=models.CASCADE, null=True)

    def __str__(self):
        if self.testresult is None:
            return f'{self.covidtest} - Aktivní'
        return f'{self.covidtest}, {self.testdate}, výsledek: {self.testresult}'


class Reservation(models.Model):
    """!
    Class of Reservation database model, using Django's ORM implementation
    """
    createdate = models.DateTimeField()
    deadline = models.DateTimeField(blank=True, null=True)
    covidpass = models.ForeignKey(CovidPass, on_delete=models.CASCADE, null=True)


class Administrative(models.Model):
    """!
    Class of Administrative database model, using Django's ORM implementation
    """
    name = models.TextField()
    surname = models.TextField()
    user = models.ForeignKey(User, on_delete=models.CASCADE)


class Doctor(models.Model):
    """!
    Class of Doctor database model, using Django's ORM implementation
    """
    name = models.TextField()
    surname = models.TextField()
    title = models.CharField(max_length=5, blank=True, null=True)
    address = models.TextField(blank=True, null=True)
    user = models.ForeignKey(User, on_delete=models.CASCADE)
