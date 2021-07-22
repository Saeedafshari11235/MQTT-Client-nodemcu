#include<ESP8266WiFi.h>
#include<Adafruit_MQTT.h>
#include<Adafruit_MQTT_Client.h>


#define wlan_ssid "Afshari-tcz"
#define wlan_pass "Saeed@#Hesam"
#define aio_server "io.adafruit.com"
#define username "SaeedAfshari11235"
#define port 1883
#define key "aio_kkuw59CCmaeV9sLkLhUvuC6qAsPf"
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client,aio_server,port,username,key);
Adafruit_MQTT_Publish pot = Adafruit_MQTT_Publish(&mqtt,username"/feed/pot");
uint16_t potvalue = 0;

void MQTT_connect();

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(wlan_ssid);
  WiFi.begin(wlan_ssid,wlan_pass);
  while(WiFi.status() != WL_CONNECTED){
    delay(200);
    Serial.print(".");
  }
  Serial.println("\n Wifi connected");
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());
  
}

void loop() {
  MQTT_connect();
  uint16_t value = analogRead(A0);
  potvalue = value;
  Serial.print(F("Sending pot val "));
    Serial.print(potvalue);
    Serial.print("...");
    delay(2000);
    if (! pot.publish(potvalue)) {
      Serial.println(F("Failed"));
    } else {
      Serial.println(F("OK!"));
    }
  
}

void MQTT_connect(){
  if(mqtt.connected()){
    return;
  }
  Serial.println("Connecing to MQTT...");
  while(mqtt.connect() != 0){
    Serial.println(mqtt.connectErrorString(mqtt.connect()));
    Serial.println("Retrying connection in 5 second");
    mqtt.disconnect();
    delay(5000);
    int Time = 0;
    Time++;
    if(Time==3){
      break;
    }
  }
  Serial.println("MQTT Connected!");
}
