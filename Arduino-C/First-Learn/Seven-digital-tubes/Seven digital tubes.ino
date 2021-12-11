void setup() 
{
  int i = 0;
  for(i = 2; i < 10; i++)
  {
    pinMode(i,OUTPUT);
  }
}

void loop() 
{
  int i = 0;
  for(i = 0; i < 10; i++)
  {
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);            //初始化所有针脚，默认均变亮
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
    }               //在 七段数码管 上显示 0 - 9 所用的 switch 语句
    delay(1000);
  }
}
