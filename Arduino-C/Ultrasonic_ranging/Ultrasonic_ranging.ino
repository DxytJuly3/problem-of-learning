#define TRIG 8
#define ECHO 9
#define LED 10
void setup()
{
    pinMode(ECHO, INPUT);
    pinMode(TRIG, OUTPUT);
    //触发端口设置为输出，反馈端口设置为输入
    Serial.begin(9600);
}
//主循环
void loop()
{
    long IntervalTime = 0; //定义一个时间变量
    while (1)
    {
        digitalWrite(TRIG, 1);//置高电平
        delayMicroseconds(15);//延时15us
        digitalWrite(TRIG, 0);//设为低电平
        IntervalTime = pulseIn(ECHO, HIGH); //用自带的函数采样反馈的高电平的宽度，单位us
        float S = IntervalTime / 58.00; //使用浮点计算出距离，单位cm
        digitalWrite(LED, LOW);

        if (S < 20)
        {
            Serial.println("报警");
            digitalWrite(LED, HIGH);
        }
        else
        {
            Serial.print(S);//通过串口输出距离数值
            Serial.println("cm");
        }

        S = 0;
        IntervalTime = 0; //对应的数值清零。
        delay(500);//延时间隔决定采样的频率，根据实际需要变换参数
    }
}
