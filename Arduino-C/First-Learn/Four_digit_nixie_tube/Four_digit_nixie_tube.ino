/*四位数码管   1 - 4 循环显示*/

int pinsNum[4] = {10,11,12,13,};
int pinsChar[8] = {2,3,4,5,6,7,8,9,};

void LED_DARK()
{
  int i = 0;
  for(i = 0; i < 4; i++)
  {
    digitalWrite(pinsNum[i],LOW);
  }
  for(i = 0; i < 8; i++)
  {
    digitalWrite(pinsChar[i],LOW);
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
  for(i = 0; i < 4; i++)
  {
    pinMode(pinsNum[i],OUTPUT);
  }
  for(i = 0; i < 8; i++)
  {
    pinMode(pinsChar[i],OUTPUT);
  }
}
int i = 0;
void loop()
{
  LED_DARK();
  digitalWrite(pinsNum[i],LOW);
  switch(i)
  {
    case 0:
          digitalWrite(pinsNum[1],HIGH);  
          digitalWrite(pinsNum[2],HIGH); 
          digitalWrite(pinsNum[3],HIGH);   
          break;
    case 1:
          digitalWrite(pinsNum[0],HIGH);  
          digitalWrite(pinsNum[2],HIGH); 
          digitalWrite(pinsNum[3],HIGH); 
          break;
    case 2:
          digitalWrite(pinsNum[1],HIGH);  
          digitalWrite(pinsNum[0],HIGH); 
          digitalWrite(pinsNum[3],HIGH);    
          break;
    case 3:
          digitalWrite(pinsNum[1],HIGH);  
          digitalWrite(pinsNum[2],HIGH); 
          digitalWrite(pinsNum[0],HIGH);  
          break;
  }
  switch(i)
  {
    case 0:
          digitalWrite(3,HIGH);
          digitalWrite(4,HIGH);
          break;
    case 1:
          digitalWrite(2,HIGH);
          digitalWrite(3,HIGH);
          digitalWrite(5,HIGH);
          digitalWrite(6,HIGH);
          digitalWrite(8,HIGH);
          break;
    case 2:
          digitalWrite(2,HIGH);
          digitalWrite(3,HIGH);
          digitalWrite(4,HIGH);
          digitalWrite(5,HIGH);
          digitalWrite(8,HIGH);
          break;
    case 3:
          digitalWrite(3,HIGH);
          digitalWrite(4,HIGH);
          digitalWrite(7,HIGH);
          digitalWrite(8,HIGH);
          break;
  }
  i++;
  if(i == 4)
  {
    i = 0;
  }
  delay(1000);
}
