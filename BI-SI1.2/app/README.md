The app is available online at: https://minarsim.pythonanywhere.com<br>
<br>
In case of a localhost, the only requirement is django (`pip install django`), the app can be run with this command in the app/ folder:<br>
`python manage.py runserver PORT` - the app will run at localhost:PORT
<br>
 # Login credentials:
**Superuser login**:<br>
 - Username: admin<br>
 - Password: adminadmin<br>
 - url: /admin

**Doctor login**:
 - Username: Doctor1
 - Password: docpass1
 - url: /doctor

**Patient login**
 - Username: samoplatce
 - Password: samoplatce
 - url: /patient-login

 # Shortcut links:
  - /doctor - Doctor's site
  - /patient - Patient's site
  - /register - Registration for paying patients (Creates a patient-user and a valid CovidPass)
  - /reservation - Reservation of a CovidTest (with valid CovidPass)
  - /admin - Superuser interface