from django.db import models
from django.utils import timezone



class PacketDate(models.Model):
    idInc = models.IntegerField()
    idSeq = models.IntegerField()
    temperature = models.FloatField()
    rh = models.FloatField()
    rhSensor = models.FloatField()
    eggTurned = models.BooleanField()
    incTime = models.CharField(max_length=100)
    recieved = models.DateTimeField(default = timezone.now)


class User(models.Model):
    isAdmin = models.BooleanField()
    username = models.CharField(max_length=20)
    password = models.CharField(max_length=100)


class UserIncubator(models.Model):
    user = models.ForeignKey(User, related_name='user', on_delete=models.CASCADE)
    incubator = models.IntegerField()
    addedBy = models.ForeignKey(User, related_name='addedBy',  on_delete=models.CASCADE)
    made = models.DateTimeField(default = timezone.now)



