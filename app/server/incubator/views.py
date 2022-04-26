from django.shortcuts import render
from django.http import HttpResponse

from django.http.response import JsonResponse
import requests

from django.contrib.auth import authenticate, login
from django.contrib.auth import logout


def index(request):
    return HttpResponse("Hello, world.")


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


