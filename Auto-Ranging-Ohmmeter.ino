#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);


#define CH0  12
#define CH1  11
#define CH2  10
#define CH3  9
#define CH4  8
 

byte chanel_number;
uint32_t res;
const uint32_t res_table[5] = {100, 1000, 10000, 100000, 2000000};
char _buffer[11];
 
void setup(void) {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);

 
  pinMode(CH0, OUTPUT);
  pinMode(CH1, OUTPUT);
  pinMode(CH2, OUTPUT);
  pinMode(CH3, OUTPUT);
  pinMode(CH4, OUTPUT);
 
  chanel_number = 4;
  chanel_select(chanel_number);
 
}
 
void loop() {
 

  uint16_t V2 = analogRead(A1) + 1;
 
  if(V2 >= 550 && chanel_number < 4) {
    chanel_number++;
    chanel_select(chanel_number);
    delay(50);
    return;
  }
 
  if(V2 <= 90 && chanel_number > 0) {
    chanel_number--;
    chanel_select(chanel_number);
    delay(50);
    return;
  }
 
  if(V2 < 900) {
    float value = (float)V2*res/(1023 - V2);
    if(value < 1000.0)
      sprintf(_buffer, "%03u.%1u Ohm ", (uint16_t)value, (uint16_t)(value*10)%10);
    else if(value < 10000.0)
           sprintf(_buffer, "%1u.%03u kOhm", (uint16_t)(value/1000), (uint16_t)value%1000);
    else if(value < 100000.0)
           sprintf(_buffer, "%02u.%02u kOhm", (uint16_t)(value/1000), (uint16_t)(value/10)%100);
    else if(value < 1000000.0)
           sprintf(_buffer, "%03u.%1u kOhm", (uint16_t)(value/1000), (uint16_t)(value/100)%10);
    else
      sprintf(_buffer, "%1u.%03u MOhm", (uint16_t)(value/1000000), (uint16_t)(value/1000)%1000);
  }
 
  else
    sprintf(_buffer, "Over Load ");
 

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Resistance:");
  display.print(_buffer);
  display.display();

  
  Serial.println(_buffer);
  Serial.println();
 
  delay(500);   
 
}
 
void chanel_select(byte n) {
  switch(n) {
    case 0:
      digitalWrite(CH0, LOW);
      digitalWrite(CH1, HIGH);
      digitalWrite(CH2, HIGH);
      digitalWrite(CH3, HIGH);
      digitalWrite(CH4, HIGH);
      break;
    case 1:
      digitalWrite(CH0, HIGH);
      digitalWrite(CH1, LOW);
      digitalWrite(CH2, HIGH);
      digitalWrite(CH3, HIGH);
      digitalWrite(CH4, HIGH);
      break;
    case 2:
      digitalWrite(CH0, HIGH);
      digitalWrite(CH1, HIGH);
      digitalWrite(CH2, LOW);
      digitalWrite(CH3, HIGH);
      digitalWrite(CH4, HIGH);
      break;
    case 3:
      digitalWrite(CH0, HIGH);
      digitalWrite(CH1, HIGH);
      digitalWrite(CH2, HIGH);
      digitalWrite(CH3, LOW);
      digitalWrite(CH4, HIGH);
      break;
    case 4:
      digitalWrite(CH0, HIGH);
      digitalWrite(CH1, HIGH);
      digitalWrite(CH2, HIGH);
      digitalWrite(CH3, HIGH);
      digitalWrite(CH4, LOW);
  }
  res = res_table[n];

  
}
