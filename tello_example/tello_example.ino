#include "Tello.h"

// WiFi network name and password:
const char * networkName = "TELLO-AA0E50";//Replace with your Tello SSID
const char * networkPswd = "";

//Are we currently connected?
boolean connected = false;

Tello tello;

void setup() 
{
  Serial.begin(9600); 
  //Connect to the WiFi network
  connectToWiFi(networkName, networkPswd);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  if(connected )
  {
    tello.takeoff();
    delay(10000);
    tello.forward(300);
    delay(10000);
    tello.back(300);
    delay(10000);
    tello.land();
    //you have 5 seconds to save your tello before it takes off again
    delay(10000);

    //do once and go into a while loop
    while(1)
    {
      delay(5000);
    }
  }
}

void connectToWiFi(const char * ssid, const char * pwd) 
{
  Serial.println("Connecting to WiFi network: " + String(ssid));

  // delete old config
  WiFi.disconnect(true);
  //register event handler
  WiFi.onEvent(WiFiEvent);

  //Initiate connection
  WiFi.begin(ssid, pwd);

  Serial.println("Waiting for WIFI connection...");
}

//wifi event handler
void WiFiEvent(WiFiEvent_t event) 
{
  switch (event) 
  {
    case SYSTEM_EVENT_STA_GOT_IP:
      //When connected set
      Serial.print("WiFi connected! IP address: ");
      Serial.println(WiFi.localIP());
      //initialise Tello after we are connected
      tello.init();
      connected = true;
      break;
      
    case SYSTEM_EVENT_STA_DISCONNECTED:
      Serial.println("WiFi lost connection");
      connected = false;
      break;
  }
}
