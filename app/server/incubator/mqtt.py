import paho.mqtt.client as mqtt

def on_connect(client, userdata, rc, properties=None):
    client.subscribe("test")

def on_message(client, username, msg):
    print("==begin==")
    print(msg)
    print("message recieved ", str(msg.payload.decode("utf-8")))
    print("message topic=",  msg.topic)
    #print("message qos=", msg.qos)
   # print("message retain flag=", msg.retain)
    print("==end==\n")

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("localhost", 1883, 60)
