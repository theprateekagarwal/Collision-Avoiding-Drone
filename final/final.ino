#include <NewPing.h>
#include "C:\Users\Dell\Desktop\yu\ultra\mavlink\common\mavlink.h"

NewPing front(2, 3, 300);
NewPing back(6, 7, 300);
NewPing right(4, 5, 300);
NewPing left(8, 9, 300);

 
 
uint16_t Pitch = 0,Roll  = 0,PitchOut = 0, RollOut  = 0, PitchOutTemp = 0, RollOutTemp  = 0;
uint8_t n = 0; unsigned long HeartbeatTime = 0;

#define distancesused 4
#define neardistance 100
#define mindist 50


struct Sensors {
  uint16_t distance[distancesused] = {0};
  uint16_t avgDistance = 0;
  bool near = false;
  bool active = false;
  unsigned long compensationTime = 0;
};

#define sensors 4
Sensors Sensor[sensors];

void measureDistances() {
  Sensor[0].distance[0] = front.ping_cm();
  Sensor[1].distance[0] = right.ping_cm();
  Sensor[2].distance[0] = back.ping_cm();
  Sensor[3].distance[0] = left.ping_cm();

}
void nextdistance() {
  for (uint8_t i = 0; i < sensors; i++) {
    for (uint8_t j = distancesused - 1; j > 0; j--) {
      Sensor[i].distance[j] = Sensor[i].distance[j - 1];
    }
  }
}
void avgDistance() {
  for (uint8_t i = 0; i < sensors; i++) {
    int Total   = 0;
    uint8_t Num = 0;
    for (uint8_t j = 0; j < distancesused; j++) {
      if (Sensor[i].distance[j] != 0  && Sensor[i].distance[j] < 300) {
        Total += Sensor[i].distance[j];
        Num += 1;
      }
    }
    if (Num > 3) {
      Sensor[i].avgDistance = Total / Num;
    } else {
      Sensor[i].avgDistance = 0;
    }
  }
}

void checkdistance() {
  for (uint8_t i = 0; i < sensors; i++) {
    if (Sensor[i].avgDistance != 0 && Sensor[i].avgDistance < neardistance) {
      Sensor[i].near = true;
    } else {
      Sensor[i].near = false;
    }
  }
}

int compensation=800;
void setup() {
  Serial.begin(57600);
}

void loop() {
  if ( (millis() - HeartbeatTime) > 1000 ) {
    HeartbeatTime = millis();
    sendHeartBeat();
  }
 
  nextdistance();
  measureDistances();
  avgDistance();
  checkdistance();
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];
  uint16_t len;
  
  Pitch  = checkPitch(Pitch);
  Roll   = checkRoll(Roll);
  
  Balance();

  if( Pitch != PitchOutTemp || Roll != RollOutTemp ){
    n = 0;
    PitchOutTemp = Pitch;
    RollOutTemp  = Roll;
  }else{
    n += 1;
    if(n == 4){
      RollOut = RollOutTemp;
      PitchOut = PitchOutTemp;
      RCOverride(&msg, len, buf, PitchOut, RollOut);
    }
  }  

}

uint16_t checkPitch(uint16_t Pitch) {
  int16_t Difference = Sensor[0].avgDistance - Sensor[2].avgDistance;
      if( abs(Difference) > mindist ) {
    if( Sensor[0].near == true ) {
      if( Sensor[2].near == true ) {
        if( Sensor[0].avgDistance < Sensor[2].avgDistance ) {
          return( Pitch = ValueMilliseconds( Sensor[0].avgDistance, 1 ) );
        }else{
          return( Pitch = ValueMilliseconds( Sensor[2].avgDistance, 0 ) );
        }
      }else{
        return( Pitch = ValueMilliseconds( Sensor[0].avgDistance, 1 ) );
      }
    }else {
      if( Sensor[2].near == true ) {
        return( Pitch = ValueMilliseconds( Sensor[2].avgDistance, 0 ) );
      }else{
        return( Pitch = 0 );
      }
    }
  }else if( Sensor[0].near == true && Sensor[2].avgDistance == 0 ) {
    return( Pitch = ValueMilliseconds( Sensor[0].avgDistance, 1 ) );
    }else if ( Sensor[0].avgDistance == 0 && Sensor[2].near == true ) {
     return( Pitch = ValueMilliseconds( Sensor[2].avgDistance, 0 ) );
      }else {
        return( Pitch = 0 );
      }
 
}

uint16_t checkRoll(uint16_t Roll) {  
  int16_t Difference = Sensor[1].avgDistance - Sensor[3].avgDistance;
  if( 1>0 ) {
    if( abs(Difference) > mindist ) {
      if( Sensor[1].near == true ) {
        if( Sensor[3].near == true ) {
          if( Sensor[1].avgDistance < Sensor[3].avgDistance ) {
            return( Roll = ValueMilliseconds( Sensor[1].avgDistance, 0 ) );
          }else{
            return( Roll = ValueMilliseconds( Sensor[3].avgDistance, 1 ) );
          }
        }else{
          return( Roll = ValueMilliseconds( Sensor[1].avgDistance, 0 ) );
        }
      }else {
        if( Sensor[3].near == true ) {
          return( Roll = ValueMilliseconds( Sensor[3].avgDistance, 1 ) );
        }else{
          return( Roll = 0 );
        }
      }
    }else if( Sensor[1].near == true && Sensor[3].avgDistance == 0 ) {
      return( Roll = ValueMilliseconds( Sensor[1].avgDistance, 0 ) );
      }else if ( Sensor[1].avgDistance == 0 && Sensor[3].near == true ) {
        return( Roll = ValueMilliseconds( Sensor[3].avgDistance, 1 ) );
        }else {
          return( Roll = 0 );
        }
  }else {
    return( Roll = 0 );
  }
}

uint16_t ValueMilliseconds( uint16_t Distance, bool directionHL ) {
  if( Distance < 30 ) {
    if( directionHL == true ) {
      return( 1700 );
    }else{
      return( 1300 );
    }
  }else if( Distance < 90 ) {
    if( directionHL == true ) {
      return( 1675 );
    }else{
      return( 1325 );
    }
  }else if( Distance < 150 ) {
    if( directionHL == true ) {
      return( 1650 );
    }else{
      return( 1350 );
    }
  }
}
void sendHeartBeat() {
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];
  uint16_t len;
    mavlink_msg_heartbeat_pack(255, 0, &msg, MAV_TYPE_QUADROTOR, MAV_AUTOPILOT_GENERIC, 0, 1, 0);

    len = mavlink_msg_to_send_buffer(buf, &msg);

    Serial.write(buf, len);

}

void RCOverride(mavlink_message_t *msg, uint16_t len, uint8_t *buf, uint16_t PitchOut, uint16_t RollOut) {
  mavlink_msg_rc_channels_override_pack(255, 0 , msg, 1, 0, RollOut, PitchOut, 0, 0, 0, 0, 0, 0);
  len = mavlink_msg_to_send_buffer(buf, msg);
  Serial.write(buf, len);
 }

void Balance(){

  if(PitchOut > 1500 && Sensor[0].active == false && Sensor[2].active == false){
    Sensor[0].active = true;
  }else if(PitchOut < 1500 && PitchOut != 0 && Sensor[2].active == false && Sensor[0].active == false){
    Sensor[2].active = true;
  }else if(PitchOut == 0 && Sensor[0].active == true && Sensor[0].compensationTime == 0){
    Sensor[0].compensationTime = millis();
  }else if(PitchOut == 0 && Sensor[2].active == true && Sensor[2].compensationTime == 0){
    Sensor[2].compensationTime = millis();
  }

  if(RollOut > 1500 && Sensor[3].active == false && Sensor[1].active == false){
    Sensor[3].active = true;
  }else if(RollOut < 1500 && RollOut != 0 && Sensor[1].active == false && Sensor[3].active == false){
    Sensor[1].active = true;
  }else if(RollOut == 0 && Sensor[1].active == true && Sensor[1].compensationTime == 0){
    Sensor[1].compensationTime = millis();
  }else if(RollOut == 0 && Sensor[3].active == true && Sensor[3].compensationTime == 0){
    Sensor[3].compensationTime = millis();
  }

  for(int i = 0; i < 4; i++){
    if(Sensor[i].compensationTime != 0 && (Sensor[i].compensationTime + compensation > millis())){
      switch(i){
        case 0:
          Pitch = 1300;
          break;
        case 1:
          Roll = 1700;
          break;
        case 2:
          Pitch = 1700;
          break;
        case 3:
          Roll = 1300;
          break;
        default:
          break;
      }
    }else if(Sensor[i].compensationTime != 0){
      switch(i){
        case 0:
        case 2:
          PitchOut = 0;
          Sensor[i].active = false;
          Sensor[i].compensationTime = 0;
          break;
        case 1:
        case 3:
          RollOut = 0;
          Sensor[i].active = false;
          Sensor[i].compensationTime = 0;
          break;
        default:
          break;
      }
    }
  }
  
}

/*;
  Serial.print(Sensor[0].avgDistance);
  Serial.print(",");
  Serial.print(Sensor[1].avgDistance);
  Serial.print(",");
  Serial.print(Sensor[2].avgDistance);
  Serial.print(",");
  Serial.print(Sensor[3].avgDistance);
  Serial.print(",");
  Serial.print(Sensor[4].avgDistance);
  Serial.print("cm\n");*/
