//Lab 4 Exercise 1
#include<SPI.h>
#define DATA_PIN 11
#define CLK_PIN 13
#define SS_PIN_1 10
#define SS_PIN_2 9
int i = 0;
int map7seg[10] ={
  0b00111111, //0
  0b00000110, //1
  0b01011011, //2
  0b01001111, //3
  0b01100110, //4
  0b01101101, //5
  0b01111101, //6
  0b00000111, //7
  0b01111111, //8
  0b01101111}; //9
void spi_write_1(unsigned char cData)
{
  shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, cData);
  digitalWrite(SS_PIN_1, HIGH);
  digitalWrite(SS_PIN_1, LOW);
}
void spi_write_2(unsigned char cData)
{
  shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, cData);
  digitalWrite(SS_PIN_2, HIGH);
  digitalWrite(SS_PIN_2, LOW);
}
void setup()
{
  pinMode(SS_PIN_1, OUTPUT);
  pinMode(SS_PIN_2, OUTPUT);
  pinMode(CLK_PIN , OUTPUT);
  pinMode(DATA_PIN , OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  spi_write_1(map7seg[i]);
  for(int i = 0; i < 10; i++)
  {
    spi_write_2(map7seg[i]);
    delay(500); 
  }
  i++;
  if(i > 9)
  {
    i=0;
  }
}
