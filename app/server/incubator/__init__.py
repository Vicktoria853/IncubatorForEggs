#import django
#django.setup()

from . import mqtt

mqtt.client.loop_start()
