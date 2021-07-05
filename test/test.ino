#include <NewPing.h>
//int q=0,x;
//int ser=13; 
int trg1=2,trg2=4,trg3=7,trg4=8; 
int ech1=3,ech2=5,ech3=6,ech4=9;
int b1=A0,b2=A1,b3=A2,b4=A3;
long t1,t2,t3,t4;
float d1,d2,d3,d4;
float serva;
bool u1,u2,u3,u4;
NewPing sonar0(2, 3, 300);
NewPing sonar1(4, 5, 300);
NewPing sonar2(6, 7, 300);
NewPing sonar3(8, 9, 300);
//Servo a;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
/*pinMode(trg1,OUTPUT);
pinMode(ech1,INPUT);
//pinMode(trg2,OUTPUT);
pinMode(ech2,INPUT);
//pinMode(trg3,OUTPUT);
pinMode(ech3,INPUT);
//pinMode(trg4,OUTPUT);
pinMode(ech4,INPUT);
pinMode(b1,OUTPUT);
pinMode(b2,OUTPUT);
pinMode(b3,OUTPUT);
pinMode(b4,OUTPUT);
*/
//pinMode(ser, OUTPUT);
//a.attach(ser,0,180);

}

void loop() {
  // put your main code here, to run repeatedly:
//u1= false;u2=false;u3=false;u4=false;



/*digitalWrite(trg1,LOW);
delayMicroseconds(10);
digitalWrite(trg1,HIGH);
delayMicroseconds(15);
digitalWrite(trg1,LOW);


digitalWrite(trg2,LOW);
delayMicroseconds(10);
digitalWrite(trg2,HIGH);
delayMicroseconds(15);
digitalWrite(trg2,LOW);


digitalWrite(trg3,LOW);
delayMicroseconds(10);
digitalWrite(trg3,HIGH);
delayMicroseconds(15);
digitalWrite(trg3,LOW);

digitalWrite(trg4,LOW);
delayMicroseconds(10);
digitalWrite(trg4,HIGH);
delayMicroseconds(15);
digitalWrite(trg4,LOW);


t1= pulseIn(ech1,HIGH);
t2= pulseIn(ech2,HIGH);
t3= pulseIn(ech3,HIGH);

t4= pulseIn(ech4,HIGH);



d1=t1*173./10000.;
d2=t2*173./10000.;
d3=t3*173./10000.;
d4=t4*173./10000.;*/
  d1 = sonar0.ping_cm();
  d2 = sonar1.ping_cm();
  d3 = sonar2.ping_cm();
  d4 = sonar3.ping_cm();

Serial.print(d1);
Serial.print("cm       ");
Serial.print(d2);
Serial.print("cm       ");
Serial.print(d3);
Serial.print("cm     ");
Serial.print(d4);
Serial.println("cm");

/*if (d1<80&&d1>30){
 // u1=true;
digitalWrite(b1,HIGH);
}
else {digitalWrite(b1,LOW);}
if (d2<80&&d2>30){
//  u2=true;
digitalWrite(b2,HIGH);
}else{digitalWrite(b2,LOW);}
if (d3<80&&d3>30){
  //u3=true;
digitalWrite(b3,HIGH);
}else{digitalWrite(b3,LOW);}
if (d4<80&&d4>30){
  //u4=true;
digitalWrite(b4,HIGH);
}else{digitalWrite(b4,LOW);}

*/

//q=q+1;
//x=q%2;
delay(500);
/*if (u1==false && u2==false && u3==false && u4==false && x==1){;
serva=90
;
a.write(serva);}
else  if(u1==false/* && u2==false && u3==false && u4==false && x==0){
serva=15;
a.write(serva);}*/
}
