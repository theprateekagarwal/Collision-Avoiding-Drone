#include<Servo.h>

int v,w,x,y;

long p,q;
int a1=3,a2=5;
int b1=A0,b2=A1,b3=A2,b4=A3,c1=9,c2=11;


Servo s1,s2;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(a1,INPUT);
pinMode(a2,INPUT);
pinMode(b1,INPUT);
pinMode(b2,INPUT);
pinMode(b3,INPUT);
pinMode(b4,INPUT);
//pinMode(b5,INPUT);
//pinMode(c1,OUTPUT);
//pinMode(c2,OUTPUT);
s1.attach(c1,1000,2000);
s2.attach(c2,1000,2000);


}

void loop() {
  // put your main code here, to run repeatedly:
v= digitalRead(b1);
w= digitalRead(b2);
x= digitalRead(b3);
y= digitalRead(b4);
p=pulseIn(a1,HIGH);
q=pulseIn(a2,HIGH);
//p=map(p,1000,2000,0,180);
//q=map(q,1000,2000,0,180);
//Serial.print(p);Serial.print("    ");Serial.println(q);


if (v==1 && w==0 && x==0 &&y==0){
s1.writeMicroseconds(1600);
s2.writeMicroseconds(q);
}  
else if(w==1 && v==0 && x==0 &&y==0){
  s1.writeMicroseconds(1400);
  s2.writeMicroseconds(q);
  
  }
else if(x==1 && v==0 && w==0 &&y==0){
  s1.writeMicroseconds(p);
  s2.writeMicroseconds(1600);
  
  }
else if(y==1 && v==0 && x==0 &&w==0){
  s1.writeMicroseconds(p);
  s2.writeMicroseconds(1400);
  
  }
else if(w==1 && v==1 && x==0 &&y==0){
  s1.writeMicroseconds(1500);
  s2.writeMicroseconds(1600);
  
  }
else if(x==1 && y==1 && v==0 &&w==0){
  s1.writeMicroseconds(1600);
  s2.writeMicroseconds(1500);
  
  }
  else if(v==1 && x==1 && w==0 &&y==0){
  s1.writeMicroseconds(1600);
  s2.writeMicroseconds(1600);
  
  }
else if(w==1 && y==1 && x==0 &&v==0){
  s1.writeMicroseconds(1400);
  s2.writeMicroseconds(1400);
  
  }


else{
 s1.write(p);
 s2.write(q);
  
  }
//delay(50);
Serial.print(v);
Serial.print(" ");
Serial.print(w);
Serial.print(" ");
Serial.print(x);
Serial.print(" ");
Serial.println(y);

}
//void loop(){Serial.print("s);"}
