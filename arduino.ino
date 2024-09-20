
#include <U8glib.h>

int pinoSensorUV = A3, pinoRef = A2, pinoTemp = A2;
float valorSensorUV, tensaoConvertida, valorSensorRef, temperatura;
String nivelUV = "00";
const float BETA = 3950;

int ledVerdePin = 6;
int ledAmareloPin = 5;
int ledLaranjaPin = 4;
int ledVermelhoPin = 3;
int ledRoxoPin = 2;

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

void setup(void) {
  Serial.begin(9600); 
  pinMode(pinoSensorUV, INPUT);
  pinMode(pinoRef, INPUT);
  pinMode(ledVerdePin, OUTPUT);
  pinMode(ledAmareloPin, OUTPUT);
  pinMode(ledLaranjaPin, OUTPUT);
  pinMode(ledVermelhoPin, OUTPUT);
  pinMode(ledRoxoPin, OUTPUT);

  if ( u8g.getMode() == U8G_MODE_R3G3B2 )       
    u8g.setColorIndex(255);     
  else if (u8g.getMode() == U8G_MODE_GRAY2BIT ) 
    u8g.setColorIndex(3);       
  else if (u8g.getMode() == U8G_MODE_BW )       
    u8g.setColorIndex(1);       
  else if (u8g.getMode() == U8G_MODE_HICOLOR )  
    u8g.setHiColorByRGB(255, 255, 255);
}

void loop(void) {
  Nivel_UV();
  Mostrar_Nivel_UV();
  delay(200);
}

void Nivel_UV() {
  valorSensorUV = analogRead(pinoSensorUV);
  valorSensorRef = analogRead(pinoRef);
  
  float celsius = 1 / (log(1 / (1023. / valorSensorRef - 1)) / BETA + 1.0 / 298.15) - 273.15;
  
  if (celsius >= 0 && celsius <= 19.9) {
    nivelUV = "02";
    digitalWrite(ledVerdePin, HIGH);
    digitalWrite(ledAmareloPin, LOW);
    digitalWrite(ledLaranjaPin, LOW);
    digitalWrite(ledVermelhoPin, LOW);
    digitalWrite(ledRoxoPin, LOW);
  }
  else if (celsius >= 20.0 && celsius <= 24.9) {
    nivelUV = "04";
    digitalWrite(ledVerdePin, LOW);
    digitalWrite(ledAmareloPin, HIGH);
    digitalWrite(ledLaranjaPin, LOW);
    digitalWrite(ledVermelhoPin, LOW);
    digitalWrite(ledRoxoPin, LOW);
  }
  else if (celsius >= 25.0 && celsius <= 34.9) {
    nivelUV = "06";
    digitalWrite(ledVerdePin, LOW);
    digitalWrite(ledAmareloPin, LOW);
    digitalWrite(ledLaranjaPin, HIGH);
    digitalWrite(ledVermelhoPin, LOW);
    digitalWrite(ledRoxoPin, LOW);
  }
  else if (celsius >= 35.0 && celsius <= 40.0) {
    nivelUV = "09";
    digitalWrite(ledVerdePin, LOW);
    digitalWrite(ledAmareloPin, LOW);
    digitalWrite(ledLaranjaPin, LOW);
    digitalWrite(ledVermelhoPin, HIGH);
    digitalWrite(ledRoxoPin, LOW);
  }
  else if (celsius >= 40.0 && celsius <= 80.0){
    nivelUV = "11"; 
    digitalWrite(ledVerdePin, LOW);
    digitalWrite(ledAmareloPin, LOW);
    digitalWrite(ledLaranjaPin, LOW);
    digitalWrite(ledVermelhoPin, LOW);
    digitalWrite(ledRoxoPin, HIGH);
  }
  else {
    nivelUV = ""; 
    digitalWrite(ledVerdePin, LOW);
    digitalWrite(ledAmareloPin, LOW);
    digitalWrite(ledLaranjaPin, LOW);
    digitalWrite(ledVermelhoPin, LOW);
    digitalWrite(ledRoxoPin, LOW);
  }
  Serial.println(celsius);
}

void Mostrar_Nivel_UV() {
  u8g.firstPage();
  do {
    u8g.drawRFrame(0, 16, 67, 48, 4);
    u8g.drawRFrame(67, 16, 61, 48, 4);
    u8g.drawRFrame(0, 0, 128, 16, 4);
    u8g.drawBox(11, 48, 45, 12 );
    u8g.setFont(u8g_font_8x13B);
    u8g.setColorIndex(0);
    u8g.drawStr( 13, 59, "NIVEL");
    u8g.setColorIndex(1);
    
    u8g.drawStr( 24, 13, "Medidor UV");
    u8g.setFont(u8g_font_fur25);
    u8g.drawStr( 10, 45, "UV"); 
    u8g.setPrintPos(78, 52);
    u8g.print(nivelUV);
  } while ( u8g.nextPage() );
}
