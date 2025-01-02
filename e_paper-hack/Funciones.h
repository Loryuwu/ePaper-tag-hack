
// Librerias de la pantalla
#include "PDLS_EXT3_Basic_Global.h"
//#include "PDLS_EXT3_Basic_Fast.h"
#include "hV_HAL_Peripherals.h"
#include "hV_Configuration.h"

// Mapa de bits de las imagenes
#include "Bitmaps.h"
#include "Bitmaps417.h"
#include "Ponys.h"

// declaracion de los pines de la pantalla
const pins_t myBoard ={
    .panelBusy = 27, ///<-------- Gris   |verde
    .panelDC = 26, ///<---------- Azul   |azul
    .panelReset = 25, ///<------- Morado |morado
    .flashCS = NOT_CONNECTED,
    .panelCS = 32, ///<---------- Verde  |gris
    .panelCSS = NOT_CONNECTED,// SPI MOSI Naranja   |23
    .flashCSS = NOT_CONNECTED,// SPI SCK  Amarillo  |18
    .touchInt = NOT_CONNECTED,
    .touchReset = NOT_CONNECTED,
    .panelPower = NOT_CONNECTED,
    .cardCS = NOT_CONNECTED,
    .cardDetect = NOT_CONNECTED,
};

// Tamaño en pulgadas según fabricante
#define size 213 //213, 266, 417

//uint8_t orientacion; //orientacion de la pantalla
//uint16_t x, y; // tamaño de pixeles

#if (size == 213)
  // instancia             tipo de pantalla       placa controladora (usar myBoard para personalizar)
  Screen_EPD_EXT3 myScreen(eScreen_EPD_213_JS_0C, boardESP32DevKitC);
  uint8_t orientacion = 1;
  uint16_t x = 212;
  uint16_t y = 104;
#elif (size == 266)
  Screen_EPD_EXT3 myScreen(eScreen_EPD_266_JS_0C, boardESP32DevKitC);
  uint8_t orientacion = 1;
  uint16_t x = 296;
  uint16_t y = 152;
#elif (size == 417)
  Screen_EPD_EXT3 myScreen(eScreen_EPD_417_JS_0D, boardESP32DevKitC);
  uint8_t orientacion = 0;
  uint16_t x = 400;
  uint16_t y = 300;
#endif
/*
void pant213() {
  Screen_EPD_EXT3 myScreen(eScreen_EPD_213_JS_0C, boardESP32DevKitC);
  orientacion = 1; //orientacion de la pantalla
  x = 212; // tamaño de pixeles
  y = 104;
  myScreen.begin();
  myScreen.setOrientation(orientacion);
}
void pant266() {
  Screen_EPD_EXT3 myScreen(eScreen_EPD_266_JS_0C, boardESP32DevKitC);
  orientacion = 1;
  x = 296;
  y = 152;
  myScreen.begin();
  myScreen.setOrientation(orientacion);
}
void pant417() {
  Screen_EPD_EXT3 myScreen(eScreen_EPD_417_JS_0D, boardESP32DevKitC);
  orientacion = 0;
  x = 400;
  y = 300;
  myScreen.begin();
  myScreen.setOrientation(orientacion);
}*/

// variables varias
uint8_t divX = 20;
uint8_t divY = 10;
uint16_t dx = x / divX;
uint16_t dy = y / divY;
uint16_t posX, posY;

uint16_t ancho, alto;
uint16_t i;
uint8_t k, j;
uint8_t line;

// un delay por segundos 
void wait(uint8_t second){
  for ( i = second; i > 0; i--){
    mySerial.print(formatString(" > %i  \r", i));
    delay(1000);
  }
  mySerial.println("         \r");
}

//    myScreen.selectFont(Font_Terminal16x24);
//    String text = (String)char( 241 /*ñ*/ );
//    myScreen.gText(10, y, "abr, gui"+text+"ame el ojo ;)");
//    myScreen.gText(i * x / 17, 0, formatString(".%x", (i - 1)), myColours.red);

/***********************************
 * Funciones
 *  Pantalla
 *
 ***********************************/

void cuadricula(){
  for ( i = 0; i < divX; i++){
  for ( j = 0; j < divY; j++){
  myScreen.point(i*dx, j*dy, myColours.red);
}}}

void LoopWBR() {
    mySerial.println("White... ");
    myScreen.clear();
    myScreen.flush();
    wait(5);
    mySerial.println("Black... ");
    myScreen.clear(myColours.black);
    myScreen.flush();
    wait(5);
    mySerial.println("Red... ");
    myScreen.clear(myColours.red);
    myScreen.flush();
    wait(5);
}

void screenWBR() {
    myScreen.setPenSolid(true);
    myScreen.dRectangle(0, 0, x/3, y, myColours.white);
    myScreen.dRectangle(x/3, 0, 2*x/3, y, myColours.black);
    myScreen.dRectangle(2*x/3, 0, x, y, myColours.red);
}

/***********************************
 * Funciones
 *  imagenes varias
 *
 ***********************************/

//explicado
void Boykisser(){
  //Tamaño de la imagen (generalmente pantalla completa)
  ancho=x;
  alto=y;
  
  //parte negra
    for (i = 0; i < alto; i++) { //....................... Por cada columna de pixeles de la pantalla
      for (k = 0; k < ancho/8 ; k++){ //.................. Cada 8 pixeles de la pantalla
        line = boykisser[ancho/8 * i + k]; //............. Lee 8 pixeles del mapa de bits
        for (j = 0; j < 8; j++) //........................ Por cada pixel
          if (!bitRead(line, j)) {//...................... Si es leido un 0 en el mapa de bit
            myScreen.point(k*8+8-j, i, myColours.black);// se colorea un pixel en la pantalla
          }
      }
    }
  //parte roja (mismo sistema de arriba)
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = boykisserR[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.red);// Se colorea el pixel en rojo
          }
      }
    }
}

void Cinnamon(){
  ancho=x;
  alto=139;
  
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = cinnamon[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.black);
          }
      }
    }
  
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = cinnamonR[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.lightRed);
          }
      }
    }
}

void Snoopy(){
  ancho=x;
  alto=y;
  
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = snoopy[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.black);
          }
      }
    }
  
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = snoopyR[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.red);
          }
      }
    }
}

void Boris(){
  ancho=x;
  alto=y;
  
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = boris[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.black);
          }
      }
    }
  
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = borisR[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.red);
          }
      }
    }
}

void Discord(){
  ancho=x;
  alto=y;
  
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = discordR[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.lightRed);
          }
      }
    }
  
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = discord[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.black);
          }
      }
    }
}

void Undertale(){
  ancho=x;
  alto=y;
  
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = undertale[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.black);
          }
      }
    }
}

void Pochacco(){
  ancho=x;
  alto=y;
  
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = pochacco[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.black);
          }
      }
    }
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = pochaccoR[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.red);
          }
      }
    }
}

void Tiare(){
  ancho=x;
  alto=y;
  
  for (i = 0; i < alto; i++) {
    for (k = 0; k < ancho/8 ; k++){
      line = tiare[ancho/8 * i + k];
      for (j = 0; j < 8; j++)
        if (!bitRead(line, j)) {
          myScreen.point(k*8+8-j, i, myColours.black);
        }
    }
  }

  for (i = 0; i < alto; i++) {
    for (k = 0; k < ancho/8 ; k++){
      line = tiareR[ancho/8 * i + k];
      for (j = 0; j < 8; j++)
        if (!bitRead(line, j)) {
          myScreen.point(k*8+8-j, i, myColours.lightRed);
        }
    }
  }
}

void Girlkisser(){
  ancho=x;
  alto=y;
  
  for (i = 0; i < alto; i++) {
    for (k = 0; k < ancho/8 ; k++){
      line = girlkisser[ancho/8 * i + k];
      for (j = 0; j < 8; j++)
        if (!bitRead(line, j)) {
          myScreen.point(k*8+8-j, i, myColours.black);
        }
    }
  }

  for (i = 0; i < alto; i++) {
    for (k = 0; k < ancho/8 ; k++){
      line = girlkisserR[ancho/8 * i + k];
      for (j = 0; j < 8; j++)
        if (!bitRead(line, j)) {
          myScreen.point(k*8+8-j, i, myColours.red);
        }
    }
  }
}

void Nekoarc(){
  ancho=x;
  alto=y;
  
  for (i = 0; i < alto; i++) {
    for (k = 0; k < ancho/8 ; k++){
      line = nekoarc[ancho/8 * i + k];
      for (j = 0; j < 8; j++)
        if (!bitRead(line, j)) {
          myScreen.point(k*8+8-j, i, myColours.black);
        }
    }
  }

  for (i = 0; i < alto; i++) {
    for (k = 0; k < ancho/8 ; k++){
      line = nekoarcR[ancho/8 * i + k];
      for (j = 0; j < 8; j++)
        if (!bitRead(line, j)) {
          myScreen.point(k*8+8-j, i, myColours.black);
        }
    }
  }
}

void Doom(){
  ancho=x;
  alto=y;
  
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = doom[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.black);
          }
      }
    }
}

void Venus(){
  ancho=x;
  alto=y;
  
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = venus[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.black);
          }
      }
    }
}

void Venus2(){
  ancho=x;
  alto=y;
  
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = venus2[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.black);
          }
      }
    }
}

void CaraDeNada(){
  ancho=x;
  alto=y;
  
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = caraDeNada[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.black);
          }
      }
    }

    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = caraDeNadaR[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.red);
          }
      }
  }
}

void CaraDeNada2(){
  ancho=x;
  alto=y;
  
  for (uint8_t h = 0; h < 5; h++) {
    delay(1000);
    myScreen.clear();
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = caraDeNada[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.black);
          }
      }
    }

    const uint8_t* bitmap = caradenada[h]; 
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = bitmap[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.red);
          }
      }
    }
    myScreen.flush();
  }
}

void Espe(){
  ancho=x;
  alto=y;
  
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = espe[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.black);
          }
      }
    }
}

void Esperanza(){
  ancho=x;
  alto=y;
  
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = esperanza[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.black);
          }
      }
    }
}

void Sayori(){
  ancho=x;
  alto=y;
  
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = sayori[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.black);
          }
      }
    }
}

void Pug(){
  ancho=x;
  alto=y;
  
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = pug[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.black);
          }
      }
    }
}

void Natsuki(){
  ancho=x;
  alto=y;
  
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = natsuki[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.black);
          }
      }
    }
}

void Dokis(){
  ancho=x;
  alto=y;
  
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = dokis[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.black);
          }
      }
    }
}

void Barcode(){
  ancho=x;
  alto=y;
  
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = barcode[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.black);
          }
      }
    }
}

/***********************************
 * Funciones
 *  Imagenes 4.17
 *
 ***********************************/

void Sans(){
  ancho=x;
  alto=y;
  
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = sans[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.black);
          }
      }
    }
  
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = sansR[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.red);
          }
      }
    }
}

void Poto(){
  ancho=x;
  alto=y;
  
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = poto[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.black);
          }
      }
    }
}

void Image1(){
  ancho=x;
  alto=y;
  
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = image1[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.black);
          }
      }
    }
}

/***********************************
 * Funciones
 *  Imagenes Ponys
 *
 ***********************************/

void Loryold(){
  ancho=x;
  alto=y;
  
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = lory_old[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.black);
          }
      }
    }
}

void Lory(){
  ancho=x;
  alto=y;
  
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = lory[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.black);
          }
      }
    }
}

void Fer(){
  ancho=x;
  alto=y;
  
    for (i = 0; i < alto; i++) {
      for (k = 0; k < ancho/8 ; k++){
        line = fer[ancho/8 * i + k];
        for (j = 0; j < 8; j++)
          if (!bitRead(line, j)) {
            myScreen.point(k*8+8-j, i, myColours.black);
          }
      }
    }
}

