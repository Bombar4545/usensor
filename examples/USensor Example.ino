//########################################################//
//  Written by Ufuk Bombar et al., August 25, 2015        //
//                                                        //
//  Original GitHub page: https://github.com/Bombar4545   //
//  Arduino homepage: https://www.arduino.cc/             //
//                                                        //
//  Arduino USensor Example...                            //
//########################################################//

//* INFO: Include U_SENSOR.h file
#include <U_SENSOR.h>

//* INFO: Global USensor variable. 
//  arg0 for Trigger pin
//  arg1 for Echo pin
USensor sen;

void setup()
{
  // Nothing fancy. Enables the serial connection.
  Serial.begin(9600);
  // Attaches the pins of the sensor.
  sen.setPins(6, 7);
}

void loop()
{
  //* NORMAL MODE: getDis() / getDis(int unit)
  //  Reads the raw value from sensor. then converts it to 
  //  the unit given. Cm for default. Additional param: 
  //  Read Unit.
  //  
  //* CORRECTED MODE: getDisC() / getDis()
  //  Same as the normal mode, if distance gets out of range 
  //  MAX_RANGE_CM ~ MIN_RANGE_CM it automaticly corrects it
  //  Below 3 cm to 0 cm
  //  Further 3 meter to 300 meter
  //  
  //* DEVELOPING MODE: getDisD(int unit, float delay);
  //  Requires two parameters. Read Unit and Delay.
  //  Waits after the wave emited. For microdsecond.
  //  NO_DELAY (0) and DEF_DELAY (10) can use for delay param
  //

  // Example of Corrected mode
  Serial.print(sen.getDisC(IN_CM));
  Serial.println(" cm");
  delay(250);

  //* UNITS: You can convert raw automaticly to fallowings
  //  IN_RAW
  //  IN_MM
  //  IN_CM
  //  IN_DM
  //  IN_M
  //  IN_INCH
  //  IN_FOOT
  //  IN_YARD

  //* OTHER DEFINES:
  //  SOUND_SPEED_CM    Speed of sound cm per microsec * 2
  //  NO_DELAY          0 microsec
  //  DEF_DELAY         10 microsec
  //  MAX_RANGE_CM      300 cm
  //  MIN_RANGE_CM      3 cm
}

