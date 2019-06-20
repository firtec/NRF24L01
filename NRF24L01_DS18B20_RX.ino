/**********************************************************************
** Descripción  : Recibe el valor de temperatura leído desde un sensor            
**                DS18B20 usando un transponder de 2.4 Ghz NRF24L01
**                
**  Target       : Arduino UNO
**  ToolChain    : Arduino IDE 1.8.9 bajo Linux Debian
**  www.firtec.com.ar 
**********************************************************************/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
 
//Declaremos los pines CE y el CSN para NRF24L01
#define CE_PIN 9
#define CSN_PIN 10
 
byte direccion[6] ={"1Nodo"};  // Nodo a contactar
RF24 radio(CE_PIN, CSN_PIN);  // Creael objeto radio (NRF24L01)
char datos[10];   // Buffer para los datos recibidos

void setup(){
  radio.begin();   //inicializamos el NRF24L01 
//---------------------------------------------------------------------------------------  
    // Posibles ajustes de ptencia.
    // RF24_PA_MIN = -18dBm, RF24_PA_LOW = -12dBm, RF24_PA_HIGH = -6dBm, RF24_PA_MAX = 0dBm
//---------------------------------------------------------------------------------------  
  radio.setPALevel(RF24_PA_MAX); // Potencia máxima (irrelevante en modo escucha)
  Serial.begin(9600); 
  radio.setChannel(100); // 125 canales posibles
  radio.openReadingPipe(1, direccion);  // Modo escucha siempre llamar antes que radio.startListening()
  radio.startListening();   // Modo escucha activo
}
 
void loop() {
  if ( radio.available())   // Datos disponibles?
 {    
     radio.read(datos,sizeof(unsigned long));  // Leer los datos
     Serial.println(datos);     // Mostrar los datos en el puerto serial
}
 delay(1000);
}
