from django.db import models
from django.utils import timezone
from django.contrib.auth.models import User
from rest_framework import serializers

class PacketDate(models.Model):
    idInc = models.IntegerField()
    idSeq = models.IntegerField()
    temperature = models.FloatField()
    rh = models.FloatField()
    rhSensor = models.FloatField()
    eggTurned = models.BooleanField()
    incTime = models.CharField(max_length=100)
    recieved = models.DateTimeField(blank=True, default = timezone.now)

    def __str__(self):
        return ("#" + str(self.idInc) + " -  " + str(self.recieved.year) + "/" + str(self.recieved.month)+ "/" + str(self.recieved.day) + " " + str(self.recieved.hour) + ":" + str(self.recieved.minute) + ":" + str(self.recieved.second))

class PacketDateSerializer(serializers.ModelSerializer):
    class Meta:
        model = PacketDate
        fields = ["idInc", "idSeq", "temperature", "rh", "rhSensor", "eggTurned", "incTime", "recieved"]







    

class UserIncubator(models.Model):
    user = models.ForeignKey(User, related_name='user', on_delete=models.CASCADE)
    incubator = models.IntegerField()
    addedBy = models.ForeignKey(User, related_name='addedBy',  on_delete=models.CASCADE)
    made = models.DateTimeField(default = timezone.now)

    def __str__(self):
        return (self.user.username + " #" + str(self.incubator))


