#define PIN_A 2
#define PIN_B 3

int count = 0;

void setup(){
  pinMode(PIN_A, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("TestEncoder");
  
  attachInterrupt(digitalPinToInterrupt(PIN_A),
                  ISR_Ext, RISING);
}

void loop(){
  Serial.println(count);
}

void ISR_Ext(){
   count++;
}
