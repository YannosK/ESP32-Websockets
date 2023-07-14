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

WebServer server(80); //creating a server instance with port 80
//here you need to add a whole HTML code compressed to a string. ALWAYS USE '' NOT "" IN THE HTML CODE
String webpage = "<!DOCTYPE html><html><head><title>Page Title</title></head><body style='background-color: #EEEEEE;'><span style='color: #003366;'><h1>Lets generate a random number</h1><p>The random number is: </p></span></body></html>";

int status = WL_IDLE_STATUS;



void setup() {
  Serial.begin(115200);

  char WiFi_ssid[32] = "BS_AP_Z_5_3";
  char WiFi_pswd[32]= "kalosavvatokiriako2023";

  //WifiCredentialsViaSerial(WiFi_ssid, WiFi_pswd);

  ConnectToWiFi(WiFi_ssid, WiFi_pswd);

  ServerInitialize();
}



void loop() {
  server.handleClient();
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
  //initialization
  server.on
  (
    // "/" defines the root folder
    // with [] and () you will not refer to a function
    "/", [] () 
    {
      // now you tell the server what to do in case someone connects to it
      // 200 is the HTTP response code
      // then sends a string as in indication, via html
      // then you add the actual html as a variable
      server.send(200, "text/html", webpage);
    }
  );

  server.begin();
}