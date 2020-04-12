#include<Servo.h>
#include<math.h>
int k=0;
int LED = 13;      // pin 13 is given variable LED
String data;     
int data3;         // Variable to store data
int data4;
int xcom=744;
int initial;
Servo myservo2;
Servo myservo;
Servo myservo1;
Servo myservo3;
Servo myservo4;
Servo myservo5;
void setup()
{
  
Serial.begin(9600);              //setting baud rate for communication

  
  myservo.attach(11); 
  myservo1.attach(9);
  myservo2.attach(10); 
  myservo3.attach(6); 
  myservo4.attach(3);//left
  myservo5.attach(5);//right

  myservo4.write(150);
  myservo5.write(10);
  myservo2.write(90);
   myservo1.write(50);
  myservo3.write(70);
   myservo.write(20);
}
double m,m1,m5,m6,m7;
int mx,my;
int t=0;

int g=0;
void loop()
{

 
 while(Serial.available())         //check if data is available
{
  k=0;
 data = Serial.readString(); 
 int i=0;
 String data1 ;
 String data2;
 int l=data.length();
 while(data[i]!=' ')
 {
  data1=data1+data[i];
  i=i+1;
 }
 i=i+1;
 while(data[i]!=' ')
 {
  data2=data2+data[i];
  i=i+1;
 }
 data3=data1.toInt();//while data is available read the data
 data4=data2.toInt();
mx=data3;
 my=sqrt (pow((1045-data4),2)+pow((744-data3),2));
 g=0;
}
if(g==1)
{
loop();
}

  m5=(1045-my);
  m6=(744-mx);
  m7=(m5/m6);

Serial.println(m7);
double angle =(atan(abs(m7)) );
Serial.println(angle);
Serial.println(angle*57.32);
delay(1000);
int b;
if(mx>xcom)
{
  b =(angle*57.32);
myservo2.write(b);
Serial.println(b);
Serial.println("HOLLO");

}
else if(mx<xcom)
{
  b = (180- ((angle)*57.32));
 Serial.println(b);
myservo2.write(b); 
Serial.println("HOL5LO");

}

double target =my*0.0532;
if(target>0 && target <=36)
{
  Serial.println(target,"bye");

  double arm1 = 22;
  double arm2 = 15.5;
  double u ;
  double h;
  for (double i = 0; i <= 180;)
  {
    double d = arm1 * arm1;
    double a = arm2 * arm2;
    double s = cos(i) * cos(i);
    Serial.println(cos(i));

    double t = sqrt(d - a * (1 - s));
    double q = arm2 * cos(i);
    if (t + q >= target - 1 && t + q <= target + 1)
    {
      break;
    }
    u = cos(i);
    Serial.println(t + q);
    
    i = i + 0.1;
    h = i * (57.32);
  }
  Serial.println(u);

  double v = target - (arm2 * u);
  double r = v / arm1;

  double x = asin(r);
  Serial.println(h);
  Serial.println(x * (57.32));
  double w = 100 - h + (x * (57.32));
  double f =  50+ (x * (57.32));
    Serial.println(w);
      Serial.println(f);

//--------------------------------------------
    if(w>20)
    {
      for(int d=20;d<=w;d++)
      {
       myservo.write(d);
       delay(100);
     }
    }
    else
    {
      for(int d=w;d>=20;d--)
      {
       myservo.write(d);
       delay(100);
     }
    }

//--------------------------------------------

    for(int d=70;d<=70+h+10;d++)
      {
       myservo3.write(d);
       delay(50);
     }
//-------------------------------------------
     for(int d=150;d>=20;d--)
      {
       myservo4.write(d);
      
     }
      for(int d=10;d<=140;d++)
      {
       myservo5.write(d);
     
     }
 //------------------------------------------ 
     delay(500);
  for(int d=50;d<=f;d++)
      {
       myservo1.write(d);
       delay(100);
     }
//--------------------------------------------
   delay(500);
    for(int d=20;d<=150;d++)
      {
       myservo4.write(d);
       delay(50);
     }
    for(int d=140;d>=10;d--)
      {
       myservo5.write(d);
       delay(50);
     }
  

g=1;
  
//------------------------------------------------
//still right angle

for(int d=f;d>=50;d--)
      {
       myservo1.write(d);
       delay(50);
     }
for(int d=w;d<=100;d++)
      {
       myservo.write(d);
       delay(100);
     }
        delay(500);
    
   for(int d=70+h+10;d>=70+10;d--)
  {
   myservo3.write(d);
   delay(50);
 }
  for(int d=b;d>=10;d--)
  {
   myservo2.write(d);
   delay(50);
 }
 
    
//-------------------------------------------------
//gripper
   for(int d=150;d>=20;d--)
      {
       myservo4.write(d);
      
     }
      for(int d=10;d<=140;d++)
      {
       myservo5.write(d);
       
     }

 
     delay(500);
    for(int d=20;d<=150;d++)
      {
       myservo4.write(d);
       
     }
    for(int d=140;d>=10;d--)
      {
       myservo5.write(d);
      
     }
//---------------------------------------------------
//back to position
 
      for(int d=90;d>=20;d--)
      {
       myservo.write(d);
       delay(50);
     }
  

 for(int d=10;d<=90;d++)
  {
   myservo2.write(d);
   delay(50);
 }

  loop();   
  
}
 
}
  
