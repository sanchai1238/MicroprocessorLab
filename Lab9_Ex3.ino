#include<SPI.h>
#define DATA_PIN 11
#define CLOCK_PIN 13
#define SS_PIN_1 10

int digitArray[10]={
      0b00111111, //0
      0b00000110, //1
      0b01011011, //2
      0b01001111, //3
      0b01100110, //4
      0b01101101, //5
      0b01111101, //6
      0b00000111, //7
      0b01111111, //8
      0b01101111 //9
};

int calculateOCR(double frequency, long prescaler) {
  const long CLOCK_FREQ = 16000000;
  return (CLOCK_FREQ / (frequency * prescaler)) - 1.0;
}

void spi_write_1(unsigned char cData){
  shiftOut(DATA_PIN,CLOCK_PIN,MSBFIRST,cData);
  digitalWrite(SS_PIN_1,HIGH);
  digitalWrite(SS_PIN_1,LOW);
}

int timer1_counter;
int toggle=0;
int one=0;
void setup()
{ Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
 noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = calculateOCR(1, 1024);
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10); // 1024
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}

void loop()
{
  Serial.println(one);
  delay(1000);
}

ISR (TIMER1_COMPA_vect){
    spi_write_1(digitArray[one]);
    one++;
    if(one==10){
    one=0;}
}
