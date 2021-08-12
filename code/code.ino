/*
 * SENSOR OLFATIVO TIPO NARIZ PARA DETECTAR LA PRESENCIA DE SULFURO DE HIDRÓGENO CERCA DE AGUAS RESIDUALES.
 * Open Source desarrollado por: Diego A. Trujillo, Cristian Agudelo, Juan E. Molina, Miguel Duque y Jary D. Monsalve.
 * Programación en Arduino, ultima modificación al código: 27/05/2020
*/

#include <MQUnifiedsensor.h>    // Librería para sensor MQ
#include <DHT.h>                // Librería para sensor DHT11 tem4 y humedad digital(0)
#include <SoftwareSerial.h>     // Librería para bluetooth
SoftwareSerial mySerial(2, 3);  // Rx,Tx, puertos para transmisión y recepción, (depende de la targeta arduino)
float H2Sm;                     // Datos flotantes con decimales
float sensorValue = A0;         // Leer análogo en puerto A0

// Variables para codificar el filtro pasa bajo
float y = 0.0;
float a = 0.5;
float s = y;

// Variables para codificar el tono del buzer
float sinVal;
int toneVal;
unsigned long tepTimer ;

// Variable para hacer promedio de 1000 datos
float suma;

// DHT11 sensor de temperatura y humedad
int SENSOR = digitalRead(0);    // Sensor digital dht
int tem4, humedad;
DHT dht (SENSOR, DHT11);

void setup() {            // Iniciar comunicación serial con pc
  Serial.begin(9600);

  //Serial Print Para Excel
  char tem4[10];          // Dato en forma de caracter
  char humedad[10];
  char s[10];
  char suma[10];          // Dato como caracter
  Serial.println("CLEARDATA");
  Serial.println("LABEL,FECHA,ppm, ug/m3,humedad,temperatura");
  Serial.println("RESETTIMER");

  // PARTE DE CÓDIGO PARA COMUNICACIÓN EXCEL PLX-DAQ
  mySerial.begin(9600);     // Iniciar comunicación con Bluetooth

  //Tono conexión para el buzer y luz led de alarma
  pinMode(8, OUTPUT);

  // DHT11
  pinMode(0, INPUT);    // DHT
  dht.begin();
}

void loop(){      // Rutina para el ciclo
  suma = 0;
  for (int i = 0; i < 1000; i++) {            // Promedio de 1000 datos
    // read the input on analog pin 0:
    y = (float)analogRead(sensorValue);
    s = (a * (y - 110)) + ((1 - a) * s);      // Ecuación para un filtro pasa bajos (calibracion de Y)
    H2Sm = (s * 34.1 * 0.1 / 24.5) / 100 ;    // Formula para pasar de ppm a ug/m3 (NORMAS CALIDAD DE AIRE DECRETO 948) secretaria de medio ambiente
    suma = H2Sm + suma;                       // Promedio o media de 1000 datos
    delay (1);
  }

  //Tono
  
  if (s > 50){    
    /* 
     * S grados, el zumbador se activa para valores mayores de...,
     * podemos cambiar este valor al rango de sulfuro que se desee."calibrar la alarma segun la concentracion"
    */
      for (int x = 0; x < 180; x++) {
        sinVal = (cos(x * (3.1412 / 180)) * sin(x * (3.1412 / 90)) * tan(x * (3.1412 / 45)) / tan(x + 90));
        toneVal = 10 + (int(sinVal * 3000));  //Con los valores se cambia las frecuencias de los sonidos
        tone(8, toneVal);
        delay(1);
      }
  } else{    // Si H2S está por debajo de 50ppm, el zumbador no suena.
    noTone(8);
  }

  if (millis() - tepTimer > 500) {    // Salida del valor de por 500 ms.
    tepTimer = millis();

    // Ciclo de DHT11
    humedad = dht.readHumidity();     // Sensor digital DHT11 temperatura y humedad
    tem4 = dht.readTemperature();

    /* 
    *  NOTA:
    *  "suma" es el valor del H2S en ug/m3, se calibra restando [suma-3] en el código
    *  "s" es el valor análogo del sensor de H2S, en ppm, y se calibra [(s-20)/2]
    */
    
    // Comunicación por Excel, print específico para excel aplicación de Excel PLX-DAQ, https://www.parallax.com/downloads/plx-daq
    Serial.print("DATA,TIME,");
    Serial.print(s);
    Serial.print(",");
    Serial.print(suma);
    Serial.print(",");
    Serial.print(humedad);
    Serial.print(",");
    Serial.println(tem4);
    delay(1000);

    // Print en el puerto serial y plot del computador
    Serial.println("----------------------");
    Serial.println("NARIZ ELECTRÓNICA");
    Serial.println("Sulfuro de Hidrógeno");
    Serial.print(        (s - 20) / 2);
    Serial.println(" ppm ");
    Serial.println("                     ");
    Serial.println("microgramos por metro cubico");
    Serial.print( suma - 3);
    Serial.println(" ug/m3 ");
    Serial.println("                      ");
    Serial.print(tem4);
    Serial.print("C     %Humedad ");
    Serial.println(humedad);
    Serial.println("----------------------");

    // Print para el dispositivo Android, por Bluetooth
    mySerial.println("----------------------");
    mySerial.print(     y);
    mySerial.println("NARIZ ELECTRÓNICA");
    mySerial.println("Sulfuro de Hidrógeno");
    mySerial.print(        s);
    mySerial.println(" ppm ");
    mySerial.println("                     ");
    mySerial.println("microgramos por metro cubico");
    mySerial.print( suma);
    mySerial.println(" ug/m3 ");
    mySerial.println("                      ");
    mySerial.print(tem4);
    mySerial.print("C     %Humedad ");
    mySerial.println(humedad);
    mySerial.println("----------------------");
    delay(400);
  }
}
