#include <DHT.h>
#include <SPI.h>
#include <SD.h>
#include <Time.h>

const int sensorDHT=2;
int sensorPin=2;
int sensorValue=0;

int temp = 0, humedad;
int HumS ;//sensor que lee humedad del suelo esta declarado en pines analogos
int rele = 7;
int valvula;
int e;
int t = 1023;

#define SSpin 10
//#define HumS (analogRead(A0))

File archivo;
DHT dht (sensorDHT,DHT11);

void setup() {

  pinMode(rele, OUTPUT);
  Serial.begin(9600); //Comunicacion con la PC a 9600 batios
  dht.begin();//iniciamos nuestro sensor
  pinMode (2,INPUT); 

  Serial.println("Inicializando targeta ...");
  if (!SD.begin(SSpin)){
    Serial.println("Fallo en inicializacion !");
    return;
    }
  Serial.println("inicializacion correcta");
  archivo = SD.open("datos.txt", FILE_WRITE );

  
}

void loop() {

  
      if (archivo) {
    for (int e=1; e < 10; e++);{
      temp = dht.readTemperature();
      humedad = dht.readHumidity();

      archivo.print(HumS);
      archivo.print(",");
      archivo.print(e);
      archivo.print(",");
      archivo.print(temp);
      archivo.print(",");
      archivo.print(humedad);

      Serial.print(HumS);
      Serial.print(",");
      Serial.print(e);
      Serial.print(",");
      Serial.print(temp);
      Serial.print(",");
      Serial.print(humedad);

      delay(1000);
      }
      archivo.close();
      Serial.println("escritura correcta");
    }else{
      Serial.println("error en apertura de datos.txt");
      }      
      
     int HumS = map(analogRead(A0), 0, 1023, 100,0);//map() 
      //convierte el rango de medicion de 0a100 asumiendo 
      //q el suelo es humedo al 100% y de 1023 a 0 asumiendo 0% de humedad
      sensorValue = analogRead(sensorPin);
      humedad= dht.readHumidity(); //Permite leer la humedad incluyendo la libreria 
      temp= dht.readTemperature(); //Permite leer la temperatura "" "" 
      //Imprimir en la pantalla datos leidos.
      Serial.print("Temperatura: ");
      Serial.print(temp);
      Serial.println("°C"); //temperatura: 21°C
      Serial.print("Humedad:");
      Serial.print(humedad);
      Serial.print("%");
      Serial.print("  Humedad de suelo: ");
      Serial.print(HumS);
      Serial.print("%");
      Serial.print(" ");
      Serial.print(" ");      
      //pausa 1 segundo para apreciar los datos   
      delay(1000);      

//condicio para encender la electrovalvula----------------------------------------------------------------------------------------------------------------------------
//      if(HumS<=1023){
//        digitalWrite (rele, HIGH);
//        delay(4000);
//      }else{
//          digitalWrite(rele, LOW);
//          delay(4000);
//         }
      pinMode(rele, OUTPUT);
      float t = analogRead(A0);
  //Serial.println("Temperatura: ");  Se imprimen las variables
 
  //Serial.println(t);  Quitar comentarios si desea imprimir la temperatura
  if (t >= 0){
    digitalWrite (rele,HIGH);
    Serial.println("Encendido");
    delay(1000);
  }
  if(t < 500){
    digitalWrite (rele,LOW);
    Serial.println("Apagado");
    delay(1000);
  }
  delay(3000);
}
