
float brightness = 0;
String buff;
int Port=0;

void setup() {
 // put your setup code here, to run once:
 Serial.begin(9600);
 pinMode( 10, OUTPUT);
 pinMode( 11, OUTPUT);
}

void loop() {
 // put your main code here, to run repeatedly:
 if (Serial.available() > 0) {
 char inByte = Serial.read();
      if(inByte == 'L')
      {buff = ' ';}
      if((inByte == '1')&&(inByte != '2'))
      {Port = 10;
      buff = ' ';}
     if((inByte = '2')&&(inByte != '1'))
     {Port =11;
     buff = ' ';}
     if(inByte == 'B')
     {buff = ' ';}
     if(('0'<= inByte) && (inByte <= '9'))
     {buff += inByte;}
     if(inByte == '\n')
     {brightness = buff.toInt();
     Serial.println(brightness);
     analogWrite(Port,int(brightness));
     Serial.println(brightness);
 }
 }
}
