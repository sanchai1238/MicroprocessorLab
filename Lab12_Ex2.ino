#define MOTOR_D1_PIN 7 
#define MOTOR_D2_PIN 8 
#define MOTOR_PWM_PIN 6 

int interruptChannel1APin = 2;
int interruptChannel1BPin = 3;
int delay_count = 0;
int setpoint=0;
int fb_speed = 0;

volatile int encoderCount = 0;
volatile int encoderDir = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(MOTOR_D1_PIN,OUTPUT);   
  pinMode(MOTOR_D2_PIN,OUTPUT);   
  pinMode(MOTOR_PWM_PIN,OUTPUT); 
  pinMode(interruptChannel1APin,INPUT_PULLUP);
  pinMode(interruptChannel1BPin,INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(interruptChannel1APin),
                 Channel1A_callback, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptChannel1BPin),
                 Channel1B_callback, RISING);
  Timer1_initialize(300);
} 

void Forward (int speed) 
{
  digitalWrite(MOTOR_D1_PIN,HIGH);
  digitalWrite(MOTOR_D2_PIN,LOW);
  analogWrite(MOTOR_PWM_PIN,speed);
}

void Backward (int speed) 
{
  digitalWrite(MOTOR_D1_PIN,LOW);
  digitalWrite(MOTOR_D2_PIN,HIGH);
  analogWrite(MOTOR_PWM_PIN,speed);
}

void setSpeed (int speed)
{
  if (speed>0)
  {
    if(speed>100)
    {speed=100;}
    Forward(speed);
  }
 else if (speed<0)
 {
   speed=speed*(-1);
   if (speed>100)
   {speed=100;}
   Backward(speed);
 }
 else
 {Forward(1);}
}


void serialEvent() {
  if(Serial.read() != 's') {return;}
  float val = Serial.parseFloat();
  if(Serial.read() != 'n') {return;}
  if(Serial.available()) {
      Serial.read();
  }
  setpoint = constrain(val, -100.0, 100.0);
  Serial.println(setpoint);
}

void Timer1_initialize (int period)
{
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A  = (16000000.0/(256.0*1000.0))*period - 1;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}

int errori = 0;
float kp = 1.0;
float ki = 0.3;

void loop()
{
  int error = setpoint - fb_speed;
  int pid = kp*(float)(error)+ ki*(float)(errori);
  errori += error;
  setSpeed(pid);
  
  Serial.print(setpoint);
  Serial.print(",");
  Serial.println(fb_speed);
  delay(100);
}

void Channel1A_callback()
{
  if (digitalRead(interruptChannel1APin)==1 && 
    digitalRead(interruptChannel1BPin)==0)
    {encoderCount++;}
}

void Channel1B_callback()
{
  if (digitalRead(interruptChannel1APin)==0 && 
    digitalRead(interruptChannel1BPin)==1)
    {encoderCount--;}
}
ISR(TIMER1_COMPA_vect)
{
  fb_speed = encoderCount;
  encoderCount = 0;
}
