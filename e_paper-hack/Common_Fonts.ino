//by Lory

//Archivo con importaciones y funciones de las imagenes
#include "Funciones.h"
const int Pin_213 = 4;
const int Pin_266 = 16;
const int Pin_417 = 17;

void setup() {
    mySerial.begin(115200); //consola serial
    delay(3000);//tiempo descanso
    pinMode(Pin_213, INPUT);
    pinMode(Pin_266, INPUT);
    pinMode(Pin_417, INPUT);
    mySerial.println();
    mySerial.println("=== " __DATE__ " " __TIME__);
    mySerial.println("Sketch by Lory");
    mySerial.println();

    // inicio
    mySerial.println("Iniciando programa... ");
    myScreen.begin(); //inicializa la pantalla
    myScreen.setOrientation(orientacion); //establece la irientacion
    mySerial.println(formatString("%s %ix%i", myScreen.WhoAmI().c_str(), myScreen.screenSizeX(), myScreen.screenSizeY())); //Datos de la pantalla en consola
    mySerial.println();

    mySerial.println("=> Dibujando... ");

    myScreen.clear(); //Limpia la pantalla
    screenWBR();      //funcion a dibujar
    myScreen.flush(); //inicia el dibujo
    mySerial.println("===Ok==="); //terminado, imprime esto
}

void loop() {
  delay(1000); //no estoy seguro si esto es realmente necesario
}

/*
void intento() {
//  delay(1000); //no estoy seguro si esto es necesario o no.
//  LoopWBR(); 
  if(digitalRead(Pin_213) == HIGH){
    pant213();
    mySerial.println("=> Dibujando... 2.13''");
    screenWBR();
    myScreen.flush();
    mySerial.println("===Ok===");
    delay(5000);
  }
  else if(digitalRead(Pin_266) == HIGH){
    pant266();
    mySerial.println("=> Dibujando... 2.66''");
    screenWBR();
    myScreen.flush();
    mySerial.println("===Ok===");
    delay(5000);
  }
  else if(digitalRead(Pin_417) == HIGH){
    pant417();
    mySerial.println("=> Dibujando... 4.17''");
    screenWBR();
    myScreen.flush();
    mySerial.println("===Ok===");
    delay(5000);
  }
}*/
