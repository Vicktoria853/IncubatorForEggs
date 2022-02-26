from django.shortcuts import render
from django.http import HttpResponse
#from . import mqtt




def index(request):
#    mqtt.client.loop_start()
    return HttpResponse("Hello, world. You're at the polls index.")
# Create your views here.

#mqtt.client.loop_start()
