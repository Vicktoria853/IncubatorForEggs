from django.shortcuts import render
from django.http import HttpResponse

from django.http.response import JsonResponse
import requests

from django.contrib.auth import authenticate, login
from django.contrib.auth import logout
from .models import PacketDate

def index(request):
   return render(request, "home.html", {})
    # return HttpResponse("Hello, world.")


def my_view(request):
    username = request.POST['username']
    password = request.POST['password']
    user = authenticate(request, username=username, password=password)
    if user is not None:
        login(request, user)

    else:
        pass

def logout_view(request):
    logout(request)




def packet(request):
    data = PacketDate.objects.all()
    d = []
    for dt in data:
        a = {}
        a["Seq"] = dt.idSeq
        d.append(a)
    print(data[0]) 
  # idSeq = data[0].idSeq 
    content={
        "Seq" : d,
 #       "temp": data.temperature,
  #      "rh": data.rh


            }



    return render(request, "data.html", content)
