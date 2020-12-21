from django.contrib import admin
from corona.models import *

"""!
Django's admin panel
"""
admin.site.register(Patient)
admin.site.register(HygienicStation)
admin.site.register(Facility)
admin.site.register(Place)
admin.site.register(Quarantine)
admin.site.register(Reservation)
admin.site.register(CovidTest)
admin.site.register(CovidPass)
