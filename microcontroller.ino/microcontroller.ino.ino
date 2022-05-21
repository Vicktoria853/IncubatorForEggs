#include <Wire.h>
#include <RTClib.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string.h>


#define si7021Addr 0x40
#define SCREEN_WIDTH 128 // width
#define SCREEN_HEIGHT 64 // height
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
RTC_DS3231 rtc;

////////////////// pins
uint8_t pinDB = 34;
uint8_t pinWB = 35;
uint8_t pinHeater = 25;
uint8_t pinEggTurner = 26;
uint8_t pinFan = 27;


///////////////
//////////encoder
uint8_t pinEncoder = 14;

uint8_t outputA = 12;
uint8_t outputB  = 13;




// encoder
int counter = 0;
int oldCounter = 0;
int aState;
int aLastState;
int bnt_was_pressed;
unsigned long hold;
unsigned long hold_timer = 1800;
unsigned long time_now;

//uint8_t menu = 0;

///////////////////
////////(uint16_t idSeq, float temp, float rh, float humidSensor, uint8_t eggTurning, string currentTime

 unsigned int data[2];
float temperature;
float humiditySensor;
float RelativeHumidity;
uint16_t idSeq = 0;
uint8_t eggTurning = 0;
char  currentTime[100];
//String currentTime = "20 08:29";
//

float tempMode[22][6] = {
{38.0,  37.9, 38.1, 37.4, 38.2, 38.0},
{37.8,  37.7, 37.9, 37.4, 38.2, 37.8},
{37.8,  37.7, 37.9, 37.4, 38.2, 37.8},
{37.8,  37.7, 37.9, 37.4, 38.2, 37.8},
{37.8,  37.7, 37.9, 37.4, 38.2, 37.8},
{37.8,  37.7, 37.9, 37.4, 38.2, 37.8},
{37.8,  37.7, 37.9, 37.4, 38.2, 37.8},
{37.7,  37.6, 37.8, 37.4, 38.2, 37.7},
{37.7,  37.6, 37.8, 37.0, 38.0, 37.7},
{37.7,  37.6, 37.8, 37.0, 38.0, 37.7},
{37.7,  37.6, 37.8, 37.0, 38.0, 37.7},
{37.7,  37.6, 37.8, 37.0, 38.0, 37.7},
{37.7,  37.6, 37.8, 37.0, 38.0, 37.7},
{37.7,  37.6, 37.8, 37.0, 38.0, 37.7},
{37.6,  37.5, 37.7, 37.0, 38.0, 37.6},
{37.5,  37.4, 37.6, 37.0, 38.0, 37.5},
{37.5,  37.4, 37.6, 37.0, 38.0, 37.5},
{37.5,  37.4, 37.6, 37.0, 38.0, 37.5},
{37.4,  37.3, 37.5, 37.0, 37.8, 37.4},
{37.4,  37.3, 37.5, 36.8, 37.8, 37.4},
{37.4,  37.3, 37.5, 36.8, 37.8, 37.4},
{37.0,  36.9, 37.1, 36.8, 37.8, 37.0}
}; // avg, min, max, alarm- min max current
float humidMode[22][5]; // avg, min, max, alarm- min max
int tempTaken; // every 30 sec 
int humidTempTaken; // every 30 sec 
float humidSensorTaken;


uint8_t stepCircle;
uint8_t i;

unsigned long lastEggTurning;
int period = 20000;///2700000;//45 * 60 * 1000;

unsigned long lastStep;
unsigned long currTime;

unsigned long wifiWaiting;
uint8_t okToSent = 1;



 
 float helper;
 DateTime now;
 //char currentTime[50];

     uint16_t Vo;
     float R1 = 10000; //
     float logR2, R2, T;
     const float K = 273.15; 
     const float c1 = 1.009249522e-03;
     const float c2 = 2.378405444e-04;
     const float c3 = 2.019202697e-07;
//     const float c8 = -5800.2206;// -5.8002206 * 1000
//     const float c9 = 1.3914993;
//     const float c10 = -0.048640239;  // -4.8640239 * (1/100)
//     const float c11 =  0.00041764768;        //4.1764768 * (1/10000);
//     const float c12 = -0.00000001; //-1.4452093 * pow(10, -8);
//     const float c13 = 6.5459673;
     const float e = 2.71828182;

// psychrometer
       float dryTemp;
  float dryTempK;// in Kelvins
  float wetTemp;
  float wetTempK; // in Kelvins

  float Pt = 101000; // 101 kPa, default 
  float PsatTwb; // 
  float PsatTdb;
  float wSatTwb;
  float wSatTdb;
  float w;

  float mu;

////////////////////


    String clientId = "ESP32Client";       
    const char* ssid = "VikiWIFI";//TODO
    const char* password = "viki1234";//TODO

    const char* mqtt_server = "192.168.95.253";//TODO
    const char* topic = "Incubator";
    uint8_t ok = 0;
    
    WiFiClient espClient;
    PubSubClient client(espClient);
    int id = 1;
    int sent = 0;
    long lastMsg = 0;
    char msg[100];
    char received_msg[100];
  
////////////////////

 void printDisplay();
 float getHumidSensor();
 float getTemp(uint8_t pin);
 float calTemp(uint16_t v);
 float calculatePsat(float temp);
 float calculateHumid( );
 void Sent();
 void receivedCallback(char* topic, byte* payload, unsigned int length);
 void mqttconnect();
 void setting();
 int computePID(float input, float setpoint, float kp, float ki, float kd, float dt, int minOut, int maxOut);
 void menu();
 void draw(float a);
 void Step();

void setup(){
  pinMode(pinEncoder, INPUT_PULLUP);
  pinMode(pinDB, INPUT);
  pinMode(pinWB, INPUT);
  pinMode(pinFan, OUTPUT);
  digitalWrite(pinFan, HIGH);
  aLastState = digitalRead(outputA);
  Serial.begin(115200);
      Wire.begin(5, 4);
  Wire.beginTransmission(si7021Addr);
  Wire.endTransmission();
      
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false)) {
    Serial.println(F("SSD1306 allocation failed"));
    
    }
    
    if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
  }


  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }


  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_server, 1883);
  client.setCallback(receivedCallback);
lastEggTurning = millis();
lastStep = millis();

///setting();
//mqttconnect();
  }
void loop() {
  Serial.println("Loop...");
  currTime = millis();
  if(lastStep + 300 < currTime){
    Step();
    }

analogWrite(pinHeater, computePID(dryTemp, tempMode[now.day()][0], 1.0, 2.0, 3.0, 0.02,  tempMode[now.day()][1],  tempMode[now.day()][2]));
if (lastEggTurning + period < millis()){
  digitalWrite(pinEggTurner, HIGH);
  delay(2000);
  digitalWrite(pinEggTurner, LOW);
  }

//  if(bnt_was_pressed == 1){
//    menu();
//    }


printDisplay();

}

  
