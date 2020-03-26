#define PIN_A 2
#define PIN_B 3

int A = 0;
int ENA = 0;
int ENB = 0;

void setup(){
  pinMode(PIN_A, INPUT_PULLUP);
  pinMode(PIN_B, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop(){
  ENA = digitalRead(PIN_A);
  ENB = digitalRead(PIN_B);
  
  if( A == 0 && ENA == 1){
    if(ENB == 1)
      Serial.println("Counter-Clockwise");
    if(ENB == 0)
      Serial.println("Clockwise");
  }
  
  A = ENA;
}
