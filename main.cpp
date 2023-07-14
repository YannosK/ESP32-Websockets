#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

/*
BON STUDIO
"BS_AP_Z_5_3"
"kalosavvatokiriako2023"

"AP_Fiber_Z_5_3"
"BonStud1o2022"

PEDRO
"MyrDyn"
"M90b53M98pj62@"

ARTINA
"ARTINA WIFI"
""
*/

void ConnectToWiFi(const char* WIFI_NETWORK, const char* WIFI_PASSWORD);
void ServerInitialize();

WebServer server(80);
//now we have to split the HTML string in order to add output 
String webpage_pre_output = "<!DOCTYPE html><html><head><title>Page Title</title></head><body style='background-color: #EEEEEE;'><span style='color: #003366;'><h1>Lets generate a random number</h1><p>The random number is:";
String webpage_post_output = " </p></span></body></html>";
String webpage = webpage_pre_output + String(random(100)) + webpage_post_output;

//creating counter-timer variables
int interval = 1000;
unsigned long previousMillis = 0;

int status = WL_IDLE_STATUS;



void setup() {
  Serial.begin(115200);

  char WiFi_ssid[32] = "BS_AP_Z_5_3";
  char WiFi_pswd[32]= "kalosavvatokiriako2023";

  ConnectToWiFi(WiFi_ssid, WiFi_pswd);

  ServerInitialize();
}



void loop() {
  server.handleClient();
  unsigned long now = millis();
  if(now - previousMillis > interval)
  {
    webpage = webpage_pre_output + String(random(100)) + webpage_post_output;
    previousMillis = now;
  }
}



void ConnectToWiFi(const char* WIFI_NETWORK, const char* WIFI_PASSWORD) {
  Serial.print("Connecting to WiFi");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  if (WiFi.status() != WL_CONNECTED){
    Serial.println("Connection failed!");
  }
  else{
    Serial.print("\nConected to WiFi network with local IP address:");
    Serial.println(WiFi.localIP()); 
  }
}



void ServerInitialize()
{
  server.on
  (
    "/", [] () 
    {
      server.send(200, "text/html", webpage);
    }
  );

  server.begin();
}