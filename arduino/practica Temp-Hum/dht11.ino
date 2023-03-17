#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebSrv.h>

#include "DHTesp.h"
#define DHTpin 15

const char* ssid = "OPPO";
const char* password = "12345678";
AsyncWebServer server (80);

DHTesp dht;

void setup(){
  
  conectarse();
  Serial.begin(115200);
  Serial.println();
  Serial.println("Estado\tHumedad (%)\tTemperatura (C)\t(F)\tIndiceCalor (C)\t(F)");

dht.setup(DHTpin, DHTesp::DHT11);

  server.on("/h", HTTP_GET, [](AsyncWebServerRequest *request){
    request -> send (200, "text/html", "<H1>Humedad" + humedad() + "</H1>");
  });

  server.on("/t", HTTP_GET, [](AsyncWebServerRequest *request){
    request -> send (200, "text/html", "<H1>Temperatura" + Temperatura() + "</H1>");
  });

  server.on("/tf", HTTP_GET, [](AsyncWebServerRequest *request){
    request -> send (200, "text/html", "<H1>Temperatura F" + TemperaturaF() + "</H1>");
  });

}
void loop(){

  delay(dht.getMinimumSamplingPeriod());

  float humedad =  dht.getHumidity();
  float temperatura = dht.getTemperature();                            
 
  if (isnan(humedad) || isnan(temperatura)) {
    Serial.println("No se pudo leer sensor DHT!");

    return;
  }
  Serial.print( dht.getStatusString() );
  Serial.print("\t");
  Serial.print(humedad, 1);
  Serial.print("\t\t");
  Serial.print(temperatura, 1);
  Serial.print("\t\t");
  Serial.print( dht.toFahrenheit(temperatura), 1);
  Serial.print("\t\t");
  Serial.print( dht.computeHeatIndex(temperatura, humedad, false), 1);
  Serial.print("\t\t");
  Serial.println(dht.computeHeatIndex(dht.toFahrenheit(temperatura), humedad, true), 1);


  delay(2000);
}

String humedad(){
  float hum =  dht.getHumidity();
  String valor = "";
  valor.concat(hum);
  return valor;

}

String Temperatura(){
  float temp =  dht.getTemperature();
  String valor = "";
  valor.concat(temp);
  return valor;

}

String TemperaturaF(){
  float temp =  dht.getTemperature();
  dht.toFahrenheit(temp);
  String valor = "";
  valor.concat(temp);
  return valor;

}

void conectarse(){
    Serial.print("conectando");
    Serial.println(ssid);
    WiFi.begin(ssid,password);

    while(WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");
    }

    Serial.print(WiFi.localIP());
}

