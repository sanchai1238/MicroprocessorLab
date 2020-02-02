//Lab 1 Ex 1
int a=0b00000001;

void setup()
{
   DDRD = 0xFF;
   DDRB = 0xFF;
}

void loop()
{
  PORTD = a;
  if(a==0b10000000)
  {
  a=0b00000001;
  delay(200);
  PORTD = a;
   }
  delay(200);
  a=a<<1;
}
