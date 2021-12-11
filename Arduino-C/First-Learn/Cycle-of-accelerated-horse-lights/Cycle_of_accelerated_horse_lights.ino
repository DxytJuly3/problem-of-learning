/*加速闪烁的跑马灯*/
//红 3 6 9 12
//黄 4 7 10 13
//绿 2 5 8 11

const int LEDcount = 12;
int LEDpin[]={2,3,4,5,6,7,8,9,10,11,12,13};      //LED灯 在Arduino 开发板上 所接针脚号

void setup() 
{
  int thisLED = 0;
  for(thisLED = 0; thisLED < LEDcount; thisLED++ )
  {
    pinMode(LEDpin[thisLED],OUTPUT);
  }             //循环将LED灯所接针脚号 均设置为信号输出

}
int count = 0;
void loop() 
{
  if(count <= 75)                             //单个 LED 跑马灯
    count ++;
  int num = 0;
  for(num = 0; num < 12; num++)
  {
    digitalWrite(LEDpin[num],HIGH);         
  }
  if(count <= 75)
  {
    for(num = 0; num < 12; num++)
    {
      digitalWrite(LEDpin[num],LOW); 
      delay(1500/count);            //每次循环 跑马灯流动时间缩短
      digitalWrite(LEDpin[num],HIGH);
    }           // 将针脚 在 LOW 和 HIGH 之间间断变化可以呈现闪烁效果，因为有差 才会亮 
  }
  if(count == 75)
    {
      count = 0; 
    }
  
  if(count == 0)                        //两个 LED 跑马灯 
  {
    do
    {
      count++;
      for(num = 0; num < 12; num++)
      {
        digitalWrite(LEDpin[num],HIGH);         
      }
      if(count <= 75)
      {
        for(num = 0; num < 11; num += 2)
        {
          digitalWrite(LEDpin[num],LOW); 
          digitalWrite(LEDpin[num+1],LOW);
          delay(1500/count);            //每次循环 跑马灯流动时间缩短
          digitalWrite(LEDpin[num],HIGH);
          digitalWrite(LEDpin[num+1],HIGH);
        }           // 将针脚 在 LOW 和 HIGH 之间间断变化可以呈现闪烁效果，因为有差 才会亮  
      }
    }while(count < 76);
    count = 100;
 }

 if(count == 100)         //同色 LED 跑马灯
 {
    count = 0;
    do
    {
      count++;
      for(num = 0; num < 12; num++)
      {
        digitalWrite(LEDpin[num],HIGH);         
      }
      if(count <= 75)
      {
        for(num = 0; num < 6; num += 3)
        {
          digitalWrite(LEDpin[num],LOW);
          digitalWrite(LEDpin[num+3],LOW);
          digitalWrite(LEDpin[num+6],LOW);
          delay(1500/count);            //每次循环 跑马灯流动时间缩短
          digitalWrite(LEDpin[num],HIGH);
          digitalWrite(LEDpin[num+3],HIGH);
          digitalWrite(LEDpin[num+6],HIGH);
        }           // 将针脚 在 LOW 和 HIGH 之间间断变化可以呈现闪烁效果，因为有差 才会亮  
        for(num = 1; num < 7; num += 3)
        {
          digitalWrite(LEDpin[num],LOW);
          digitalWrite(LEDpin[num+3],LOW);
          digitalWrite(LEDpin[num+6],LOW);
          delay(1500/count);            //每次循环 跑马灯流动时间缩短
          digitalWrite(LEDpin[num],HIGH);
          digitalWrite(LEDpin[num+3],HIGH);
          digitalWrite(LEDpin[num+6],HIGH);
        }
        for(num = 2; num < 8; num += 3)
        {
          digitalWrite(LEDpin[num],LOW);
          digitalWrite(LEDpin[num+3],LOW);
          digitalWrite(LEDpin[num+6],LOW);
          delay(1500/count);            //每次循环 跑马灯流动时间缩短
          digitalWrite(LEDpin[num],HIGH);
          digitalWrite(LEDpin[num+3],HIGH);
          digitalWrite(LEDpin[num+6],HIGH);
        }
      }
    }while(count < 76);
    count = 200;
  }
 
 if(count == 200)         //一半一半  LED 跑马灯
  {
    count = 0;
    do
    {
      count++;
      for(num = 0; num < 12; num++)
      {
        digitalWrite(LEDpin[num],HIGH);         
      }
      if(count <= 75)
      {
        for(num = 0; num < 12; num += 6)
        {
          digitalWrite(LEDpin[num],LOW);
          digitalWrite(LEDpin[num+1],LOW);
          digitalWrite(LEDpin[num+2],LOW);
          digitalWrite(LEDpin[num+3],LOW);
          digitalWrite(LEDpin[num+4],LOW);
          digitalWrite(LEDpin[num+5],LOW);
          delay(1500/count);            //每次循环 跑马灯流动时间缩短
          digitalWrite(LEDpin[num],HIGH);
          digitalWrite(LEDpin[num+1],HIGH);
          digitalWrite(LEDpin[num+2],HIGH);
          digitalWrite(LEDpin[num+3],HIGH);
          digitalWrite(LEDpin[num+4],HIGH);
          digitalWrite(LEDpin[num+5],HIGH);
        }           // 将针脚 在 LOW 和 HIGH 之间间断变化可以呈现闪烁效果，因为有差 才会亮  
      }
    }while(count < 76);
    count = 0;
  }
}