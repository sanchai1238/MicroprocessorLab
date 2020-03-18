#define INT_PIN 3
#define LED_PIN_0 9

int timer1_counter;
int toggle=0;
int one=0;
int time=0;
void setup()
{ Serial.begin(9600);
  pinMode(LED_PIN_0, OUTPUT);
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 65535;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10); // 1024
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
 Serial.println(OCR1A);
}
void loop()
{
  digitalWrite(LED_PIN_0, HIGH);
  delay(time); 
  digitalWrite(LED_PIN_0, LOW);
  delay(time); 
}
ISR (TIMER1_COMPA_vect){
  if(one==0){
  time=1000;
  one++;
  }
  else if(one==1){
  time=2000;
  one++;
  }
  else if(one==2){
  time=3000;
  one=0;
  } 
    Serial.println(time);
}
