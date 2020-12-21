"""app URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/3.1/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path
from django.contrib.admin.views.decorators import staff_member_required
from django.contrib.auth.decorators import login_required

from corona.presentation_layer.views.index_view import IndexView
from corona.presentation_layer.views.register_patient_view import RegisterPatientView
from corona.presentation_layer.views.doctor_view import DoctorView
from corona.presentation_layer.views.logout_view import LogoutView
from corona.presentation_layer.views.doctor_login import DoctorLoginView
from corona.presentation_layer.views.reservation_view import ReservationView
from corona.presentation_layer.views.patient_login_view import PatientLoginView
from corona.presentation_layer.views.patient_view import PatientView
from corona.presentation_layer.views.doctor_register_patient_view import DoctorRegisterPatientView

urlpatterns = [
    path('', IndexView.as_view(), name='index'),  # include('corona.urls')
    path('register/', RegisterPatientView.as_view(), name='register'),
    path('doctor-login/', DoctorLoginView.as_view(), name='doctor-login'),
    path('patient-login/', PatientLoginView.as_view(), name='patient-login'),
    path('admin/', admin.site.urls),
    path('doctor/', staff_member_required(DoctorView.as_view(), login_url='/doctor-login'), name='doctor'),
    path('logout/', LogoutView.as_view(), name='logout'),
    path('reservation/', login_required(ReservationView.as_view(), login_url='/patient-login'), name='reservation'),
    path('patient/', login_required(PatientView.as_view(), login_url='/patient-login'), name='patient'),
    path('doctor-register-patient/', staff_member_required(DoctorRegisterPatientView.as_view(), login_url='/doctor-login'), name='doctor-register-patient')
]
