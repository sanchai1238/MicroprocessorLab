#define DATA_PIN 11
#define CLOCK_PIN 9
#define LATCH_PIN 10
#define BUTTON1 A0
#define BUTTON2 A1
int c;

int map7seg[10] = {
  0x3f, //0
  0x06, //1
  0x5b, //2
  0x4f, //3
  0x66, //4
  0x6d, //5
  0x7d, //6
  0x07, //7
  0x7f, //8
  0x6f, //9
  
};

void setLed( uint8_t _state ){
  digitalWrite(LATCH_PIN,LOW);
  for(int i=0;i<8;i++){
    digitalWrite(DATA_PIN,(_state>>(7-i))&0x01);
    digitalWrite(CLOCK_PIN,HIGH);
    digitalWrite(CLOCK_PIN,LOW);
  }
  digitalWrite(LATCH_PIN,HIGH);
}
void setup()
{
  Serial.begin(9600);
  pinMode(DATA_PIN,OUTPUT);
  pinMode(CLOCK_PIN,OUTPUT);
  pinMode(LATCH_PIN,OUTPUT);  
  pinMode(BUTTON1,INPUT_PULLUP);
  pinMode(BUTTON2,INPUT_PULLUP);
  setLed(map7seg[0]);
}

void loop()
{

  Serial.println(digitalRead(BUTTON1));
  if(digitalRead(BUTTON1) == 0 && c<9){
    c++;
  }
  else if(digitalRead(BUTTON2) == 0 && c>-1){
    c--;
  }
  setLed(map7seg[c]);
  delay(100);
}
