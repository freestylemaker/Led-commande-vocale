#include <uTimerLib.h>
#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

WiFiClient wiFiClient;
Adafruit_MQTT_Client mqttClient(&wiFiClient, "192.168.0.102", 1883);

Adafruit_MQTT_Subscribe ledSubscriber(&mqttClient, "/led");

void ledCallback(double x) {
  if(x == 1) {
  Serial.println("allume la lumière");
  digitalWrite(19, HIGH);

} else {
  digitalWrite(19, LOW);

}
 
 
}

void setup() {
  // put your setup code here, to run once:
  pinMode(19, OUTPUT);

  Serial.begin(115200);
  WiFi.begin("createch2019", "createch2019");
delay(5000);
  Serial.print("IP address: ");
Serial.println(WiFi.localIP());

 ledSubscriber.setCallback(ledCallback);
 mqttClient.subscribe(&ledSubscriber);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  if (mqttClient.connected()) {
    mqttClient.processPackets(10000);
    mqttClient.ping();
  } else {
    mqttClient.disconnect();
    mqttClient.connect();
  } 
}
