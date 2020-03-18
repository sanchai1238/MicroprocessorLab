#define LED_PIN_0 9
#define INT_PIN 3

int toggle=1;
int count=0;

void setup()
{
  pinMode(LED_PIN_0,OUTPUT);
  pinMode(INT_PIN,INPUT);
  attachInterrupt(digitalPinToInterrupt(INT_PIN),
                  ISR_Callback, RISING);
}

void loop()
{
  // 1 second
  if(count==0){
  digitalWrite(LED_PIN_0,HIGH);
  delay(500);
  digitalWrite(LED_PIN_0,LOW);
  delay(500);
  }
  // 2 second
  if(count==1){
  digitalWrite(LED_PIN_0,HIGH);
  delay(1000);
  digitalWrite(LED_PIN_0,LOW);
  delay(1000);
  }
  // 3 second
  if(count==2){
  digitalWrite(LED_PIN_0,HIGH);
  delay(1500);
  digitalWrite(LED_PIN_0,LOW);
  delay(1500);
  }  
}

void ISR_Callback()
{
  count++;
  if(count>2){
    count=0;
  }
}
