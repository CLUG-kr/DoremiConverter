from django.conf.urls import url
from . import views

urlpatterens=[
        url(r'^$', views.upload_file, name='upload_file'),
]
