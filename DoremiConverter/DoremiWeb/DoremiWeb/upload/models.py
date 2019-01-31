from django.db import models

# Create your models here.

class Upload(models.Model):
    title = models.CharField(max_length = 100)
    photo = models.ImageField(blank = True)
