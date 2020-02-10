// Lab 3 Ex 1
int clk_pin = 13; //SHCP 
int latch_pin = 10;  //STCP 
int data_pin = 11;  //DS 
bool toggle; 
int map7seg[10] ={
  0b00111111,
  0b00000110,
  0b01011011,
  0b01001111,
  0b01100110,
  0b01101101,
  0b01111101,
  0b00000111,
  0b01111111,
  0b01101111,
 };
void setup() { 
  pinMode(clk_pin,OUTPUT); 
  pinMode(latch_pin,OUTPUT); 
  pinMode(data_pin,OUTPUT); 
} 
void loop()
{
  for(int k = 0 ; k < 10 ;k++)
  {
    for(int i = 0 ; i < 8 ; i++) 
    { 
      digitalWrite(data_pin,map7seg[k]>>7-i & 0x01); 
      digitalWrite(clk_pin,HIGH); 
      digitalWrite(clk_pin,LOW); 
   }
   digitalWrite(latch_pin,HIGH); 
   delay(1000);
   digitalWrite(latch_pin,LOW); 
   }
} 
