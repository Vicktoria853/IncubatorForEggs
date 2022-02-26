from django.db import models

"""
class User(models.Model):
    username = models.CharField(max_length=20)
    password = models.CharField(max_length=100)

class IncubatorData(models.Model):
    serial_number = models.CharField(max_length=10)#not sure
    owner = models.ForeignKey(User)
    working = models.BooleanField()
    eggs_in_incubator = models.IntegerField()

"""


class DataParam(models.Model):
    dryTemp = models.IntegerField()
    wetTemp = models.IntegerField()
    recieved = models.DateTimeField(auto_now_add=True)
