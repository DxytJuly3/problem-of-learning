void LED_DARK()
{
  for(int i = 2; i < 10; i++)
  {
    digitalWrite(i,LOW);
  }
}
void LED(int i)
{
      switch (i)
    {
       case 0:
          digitalWrite(8,HIGH);
          break;
       case 1:
          digitalWrite(2,HIGH);
          digitalWrite(5,HIGH);
          digitalWrite(6,HIGH);
          digitalWrite(7,HIGH);
          digitalWrite(8,HIGH);
          break;
       case 2:
          digitalWrite(4,HIGH);
          digitalWrite(7,HIGH);
          break;
       case 3:
          digitalWrite(6,HIGH);
          digitalWrite(7,HIGH);
          break;
       case 4:
          digitalWrite(2,HIGH);
          digitalWrite(5,HIGH);
          digitalWrite(6,HIGH);
          break;
       case 5:
          digitalWrite(3,HIGH);
          digitalWrite(6,HIGH);
          break;
       case 6:
          digitalWrite(3,HIGH);
          break;
       case 7:
          digitalWrite(5,HIGH);
          digitalWrite(6,HIGH);
          digitalWrite(7,HIGH);
          digitalWrite(8,HIGH);
          break;
       case 8:
          break;
       case 9:
          digitalWrite(6,HIGH);
          break;
    }
    delay(1000);

}

void setup() 
{
  int i = 0;
  for(i = 2; i < 10; i++)
  {
    pinMode(i,OUTPUT);
  }
}

void loop() {
  int = 0;
  for(i = 0; i < 10; i++)
  {
      LED_DARK();
      LED(i);
      delay(1000);
  }
}
