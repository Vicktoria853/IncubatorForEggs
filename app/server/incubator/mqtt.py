import paho.mqtt.client as mqtt
import sqlite3
from django.utils import timezone
#from .models import PacketDate

DATABASE_FILE = 'db.sqlite3'


def on_connect(client, userdata, rc, properties=None):
    client.subscribe("Incubator")


def on_message(client, username, msg):
    msgParts = str(msg.payload.decode("utf-8")).split(' ')
    #sql = 'SELECT * FROM incubator_packetdate WHERE(incTime == ?)'
    #db_conn = sqlite3.connect(DATABASE_FILE)
    #cursor = db_conn.cursor()
    #cursor.execute(sql,  msgParts[6]+ " " + msgParts[7])
    #print(cursor)
    #print(" " + sql + "\n")
    #cursor.close()
    print("==begin==")
    print(msg)
    print("message recieved ", str(msg.payload.decode("utf-8")))
    print("message topic=",  msg.topic)
    db_conn = sqlite3.connect(DATABASE_FILE) 
    #msgParts = str(msg.payload.decode("utf-8")).split(' ')
    sql = 'INSERT INTO incubator_packetdate (idInc, idSeq, temperature, rh, rhSensor, eggTurned, incTime, recieved) VALUES(?, ?, ?, ?, ?, ?, ?, ?)' 
    cursor = db_conn.cursor()
    cursor.execute(sql, (int(msgParts[0]), int(msgParts[1]), round(float(msgParts[2]), 2), round(float(msgParts[3]), 2), round(float(msgParts[4]), 2), int(msgParts[5]), msgParts[6]+ " " + msgParts[7] , timezone.now()))
    db_conn.commit()
    cursor.close()

   # p = PacketDate(idInc=int(msgParts[0]), idSeq=int(msgParts[1]), temperature=float(msgParts[2]), rh=float(msgParts[3]), rhSensor=float(msgParts[4]), eggTurned=int(msgParts[5]), incTime=msgParts[6])
    #p.save()
 #   print("message qos=", msg.qos)
   # print("message retain flag=", msg.retain)
    print("==end==\n")


ok = 1
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

db_conn = sqlite3.connect(DATABASE_FILE)


client.connect("localhost", 1883, 30)
