from django.shortcuts import render
from django.http import HttpResponse

from django.http.response import JsonResponse
import requests
import datetime

from django.contrib.auth import authenticate, login
from django.contrib.auth.decorators import login_required
from django.contrib.auth import logout
from .models import PacketDate, UserIncubator, User


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



@login_required(login_url='/login/')
def packet(request):
    data = PacketDate.objects.all()
    username = request.user.username
    ids = UserIncubator.objects.filter(user=User.objects.filter(username=username)[0])

    allowed = []
    for i in ids:
        allowed.append(i.incubator)

#    d = PacketDateSerializer(data)
    lines = [] 
    #line = []
    for d in data:
        if d.idInc in allowed:
            line = []
            line.append(d.idInc)
            line.append(d.idSeq)
            line.append(d.temperature)
            line.append(d.rh)
            line.append(d.rhSensor)
            line.append(d.eggTurned)
            line.append(d.incTime)
            line.append(d.recieved.strftime('%H:%-M:%-S %-d/%B/%Y'))
            lines.append(line)

 
  # idSeq = data[0].idSeq 
    context = {
        'lines' : lines
 #       "temp": data.temperature,
  #      "rh": data.rh


            }



    return render(request, "data.html", context)


@login_required(login_url='/login/')
def chart(request):
    data = PacketDate.objects.all()
    username = request.user.username
    ids = UserIncubator.objects.filter(user=User.objects.filter(username=username)[0])

    allowed = []
    for i in ids:
        allowed.append(i.incubator)

    lines = [] 

    data = requests.get('https://s3.eu-central-1.amazonaws.com/fusion.store/ft/data/area-chart-with-time-axis-data.json').text
    print(data)

    for d in data:
        if d.idInc in allowed:
            line = []
            line.append(d.idInc)
            line.append(d.temperature)
            line.append(d.rh)
            line.append(d.rhSensor)
            line.append(d.eggTurned)
            line.append(d.incTime)
            line.append(d.recieved.strftime('%H:%-M:%-S %-d/%B/%Y'))
            lines.append(line)

    return render(request, "chart.html", context)









