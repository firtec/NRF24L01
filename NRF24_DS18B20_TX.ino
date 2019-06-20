/**********************************************************************
** Descripción  : Envía el valor de temperatura leído desde un sensor            
**                DS18B20 usando un transponder de 2.4 Ghz NRF24L01
**                
**  Target       : Arduino UNO
**  ToolChain    : Arduino IDE 1.8.9 bajo Linux Debian
**  www.firtec.com.ar 
**********************************************************************/
#include <SoftwareSerial.h>
#include <OneWire.h>                
#include <DallasTemperature.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
#define CE_PIN 9        // Pines asignados al hardware NRF24L01
#define CSN_PIN 10

OneWire ourWire(2);                 //Se establece el pin 2  como bus OneWire 
DallasTemperature sensor(&ourWire); //Se declara una variable u objeto para nuestro sensor

byte direccion[6] ={"1Nodo"};   // Dirección del nodo a contactar
RF24 radio(CE_PIN, CSN_PIN);    // Creamos un objeto radio del tipo RF2$
char buffer[10];                // Buffer para el envío de datos


void setup(void){
  Serial.begin(9600);
  radio.begin();                    // Radio iniciado
  radio.setChannel(100);            // Contacto por el canal 100
  radio.openWritingPipe(direccion); // Radio iniciado en modo escritura
  radio.setPALevel(RF24_PA_MAX);    // Potencia ajustada al máximo
  radio.stopListening();            // Solo como transmisor  
  sensor.begin();                   // Se inicia el sensor de temperatura ds18B20
}
void loop(void){
  
  sensor.requestTemperatures();             // Inicia la medición de temperatura
  float temp= sensor.getTempCByIndex(0);    // Se obtiene la temperatura en ºC
   sprintf(buffer, "%d.%01d", (int)temp, abs((int)(temp*10)%10)); // Pasa el dato a ASCII
   //dtostrf(temp, 2, 1, buffer);  // Pasa el dato a ASCII
   bool ok = radio.write(buffer, sizeof(unsigned long));    // Pasa el dato al modulo NRF24L01
if(ok){
     Serial.println(buffer);    // Muestra el dato enviado
  } 
  delay(1000);
}
