#include <Servo.h>
#include <MeetAndroid.h>

//Values we are gonna get from Amarino App
float orientationValues[3] = {0};

//My Servo names
Servo xServo;
Servo yServo;

//Final position of servos
int posX = 0; //Compass Sensor
int posY = 0;   //Accelerometer


// ERROR FUNCTION: Displays an error exception if occured.
void error(uint8_t flag, uint8_t values){
  Serial.print("ERROR: ");
  Serial.print(flag);
}
MeetAndroid meetAndroid(error);


 void setup() {
  Serial.begin(9600); //Begin serial link @ 9600bps
  //Stablish each event for each sensor
  meetAndroid.registerFunction(orientationSensor, 'A'); //X
  
  //Attach Servos to Pins
  xServo.attach(9); 
  yServo.attach(10);

  Serial.println("REMEMBER TO CONNECT RX AND TX PINS.");
}


void loop(){
  meetAndroid.receive(); // Receive events 
}

/* X AXIS  [-10, 10] -> [0,180] */
/* Y AXIS  [-10, 10] -> [0,180] */
void orientationSensor(byte flag, byte numOfValues){
  
  meetAndroid.getFloatValues(orientationValues);
  
  posX = map(int(orientationValues[2]), -90, 90, 0, 180);
  posY   = map(int(orientationValues[1]), -90, 90, 0, 180);


  xServo.write(posX);
  yServo.write(posY);
}




