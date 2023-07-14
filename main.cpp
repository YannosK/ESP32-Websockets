#include <Arduino.h>
#include <WiFi.h>

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
void WifiCredentialsViaSerial(char WiFi_network[], char WiFi_password[]);

int status = WL_IDLE_STATUS;


void setup() {
  Serial.begin(115200);

  char WiFi_ssid[32];
  char WiFi_pswd[32];

  WifiCredentialsViaSerial(WiFi_ssid, WiFi_pswd);

  ConnectToWiFi(WiFi_ssid, WiFi_pswd);
}


void loop() {
  Serial.print("\nIP address: ");
  Serial.println(WiFi.localIP());
  delay(1000);
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

void WifiCredentialsViaSerial(char WiFi_network[], char WiFi_password[]) {
  Serial.print("\nAdd WiFi SSID: ");
  while(!Serial.available()){
    delay(1);
  }
  Serial.readBytes(WiFi_network, 32);
  WiFi_network[31] = '\0';
  String ssidString = WiFi_network;
  ssidString.trim();  
  ssidString.toCharArray(WiFi_network, 32);
  Serial.print("\nWiFi_network: ");
  Serial.println(WiFi_network);

  Serial.print("\nAdd WiFi password: ");
  while(!Serial.available()){
    delay(1);
  }
  Serial.readBytes(WiFi_password, 32);
  WiFi_password[31] = '\0';
  String pswdString = WiFi_password;
  pswdString.trim(); 
  pswdString.toCharArray(WiFi_password, 32);
  Serial.print("\nWiFi_password: ");
  Serial.println(WiFi_password);
}