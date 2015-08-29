//###################################################################################//
//  Written by Ufuk Bombar et al., August 25, 2015                                   //
//                                                                                   //
//  Written for Arduino by the purpose of facilitate the use of ultrasonic           //
//  sensor. Program version: v1.7                                                    //
//                                                                                   //
//  Original GitHub page: https://github.com/Bombar4545/usensor                      //
//  Arduino homepage: https://www.arduino.cc/                                        //
//                                                                                   //
//  Copyright (c) 2015 Ufuk Bombar. For more information, contact:                   //
//  ufukbombar@gmail.com                                                             //
//                                                                                   //
//  You may freely modify and share this code, as long as you keep this              //
//  notice intact. Licensed under the Creative Commons BY-SA 3.0 license:            //
//                                                                                   //
//  http://creativecommons.org/licenses/by-sa/3.0/                                   //
//                                                                                   //
//  NOTE:                                                                            //
//  Designed for HC-SRO4 Ultrasonic Sensor. Tested with Arduino Mega 2560            //
//                                                                                   //
//                                                                                   //
//###################################################################################//

#ifndef U_SENSOR_H
#define U_SENSOR_H

//* INCLUDES:
#include <Arduino.h>

//* DEFINES:
// RAW DATA
#define IN_RAW			0
// METRIC SYSTEM
#define IN_MM			1
#define IN_CM			2
#define IN_DM			3
#define IN_M			4
// IMPERIAL SYSTEM
#define IN_INCH			5
#define IN_FEET			6
#define IN_YARD			7
// EXPERIMENTAL
#define SOUND_SPEED_CM	58.31	//*  Constant for speed of sound cm per microsec
#define NO_DELAY		0		//*  Use with getDisD Function delay arg
#define DEF_DELAY		10		//*  Use with getDisD Function delay arg
#define MAX_RANGE_CM	300		//*  Max range for sensor 3 meter for default
#define MIN_RANGE_CM	3		//*  Min range for sensor 3 cm for default

class USensor
{
public:

	//* INFO: Constructor. Setups the default pins. Trigger pin, Echo Pin. Connect the 
	//  Trigger pin to sensors 'Trig' pin. Same for the 'Echo' pin. Connect the Vcc and 
	//  Ground pins to arduino.
	USensor(int pinT, int pinE)
	{
		setPins(pinT, pinE);
	}

	//* INFO: Constructor. Do not sets up the pins.
	USensor()
	{
		_pinT = -1;
		_pinE = -1;
	}

	//* INFO: Mesures the distance then returns it in the format given, IN_CM for default. 
	//  Do not executes delay and min/max correction.
	//  getDis -> Get Distance.
	float getDis(short id = IN_CM)
	{
		digitalWrite(_pinT, LOW);
		digitalWrite(_pinT, HIGH);
		digitalWrite(_pinT, LOW);

		float raw = pulseIn(_pinE, HIGH);

		switch (id)
		{
		case IN_RAW:	return raw; break;
		case IN_MM:		return raw / SOUND_SPEED_CM * 10; break;
		case IN_CM:		return raw / SOUND_SPEED_CM * 1; break;
		case IN_DM:		return raw / SOUND_SPEED_CM * 0.1; break;
		case IN_M:		return raw / SOUND_SPEED_CM * 0.01; break;
		case IN_INCH:	return raw / SOUND_SPEED_CM * 0.254; break;
		case IN_FEET:	return raw / SOUND_SPEED_CM * 0.3048; break;
		case IN_YARD:	return raw / SOUND_SPEED_CM * 0.9144; break;
		default:		return raw / SOUND_SPEED_CM * 1; break;
		}
	}

	//* INFO: Mesures the distance then returns it in the format given, IN_CM for default. 
	//  Do not executes delay but makes min/max correction. Recomended mode.
	//  getDisC -> Get Distance Corrected
	float getDisC(short id = IN_CM)
	{
		digitalWrite(_pinT, LOW);
		digitalWrite(_pinT, HIGH);
		digitalWrite(_pinT, LOW);

		float raw = pulseIn(_pinE, HIGH);

		if (raw / SOUND_SPEED_CM < MIN_RANGE_CM)
			return 0.0f;
		if (raw / SOUND_SPEED_CM > MAX_RANGE_CM)
			switch (id)
			{
			case IN_RAW:	return raw; break;
			case IN_MM:		return MAX_RANGE_CM * 10; break;
			case IN_CM:		return MAX_RANGE_CM * 1; break;
			case IN_DM:		return MAX_RANGE_CM * 0.1; break;
			case IN_M:		return MAX_RANGE_CM * 0.01; break;
			case IN_INCH:	return MAX_RANGE_CM * 0.254; break;
			case IN_FEET:	return MAX_RANGE_CM * 0.3048; break;
			case IN_YARD:	return MAX_RANGE_CM * 0.9144; break;
			default:		return MAX_RANGE_CM * 1; break;
			}

		switch (id)
		{
		case IN_RAW:	return raw; break;
		case IN_MM:		return raw / SOUND_SPEED_CM * 10; break;
		case IN_CM:		return raw / SOUND_SPEED_CM * 1; break;
		case IN_DM:		return raw / SOUND_SPEED_CM * 0.1; break;
		case IN_M:		return raw / SOUND_SPEED_CM * 0.01; break;
		case IN_INCH:	return raw / SOUND_SPEED_CM * 0.254; break;
		case IN_FEET:	return raw / SOUND_SPEED_CM * 0.3048; break;
		case IN_YARD:	return raw / SOUND_SPEED_CM * 0.9144; break;
		default:		return raw / SOUND_SPEED_CM * 1; break;
		}
	}

	//* INFO: Mesures the distance then returns it in the format given, IN_CM for default. 
	//  Executes delay for arg delay but do not makes min/max correction. Use this function
	//  for experimenting. Recomended version is getDisC.
	//  getDisD -> Get Distance in Developing Mode.
	float getDisD(short id, int delay)
	{
		digitalWrite(_pinT, LOW);
		digitalWrite(_pinT, HIGH);
		delayMicroseconds(delay);
		digitalWrite(_pinT, LOW);

		float raw = pulseIn(_pinE, HIGH);

		switch (id)
		{
			case IN_RAW:	return raw; break;
			case IN_MM:		return raw / SOUND_SPEED_CM; break;
			case IN_CM:		return raw / SOUND_SPEED_CM * 10; break;
			case IN_DM:		return raw / SOUND_SPEED_CM * 100; break;
			case IN_M:		return raw / SOUND_SPEED_CM * 1000; break;
			case IN_INCH:	return raw / SOUND_SPEED_CM * 25.4; break;
			case IN_FEET:	return raw / SOUND_SPEED_CM * 304.8; break;
			case IN_YARD:	return raw / SOUND_SPEED_CM * 914.4; break;
			default:		return -1.0f; break;
		}
	}

	//* INFO: Returns the pin number of trigger pin
	int getTrigPin()
	{
		return _pinT;
	}

	//* INFO: Returns the pin number of echo pin
	int getEchoPin()
	{
		return _pinE;
	}

	//* INFO: Sets the trigger and echo pins
	void setPins(int pinT, int pinE)
	{
		_pinT = pinT;
		_pinE = pinE;

		pinMode(_pinT, OUTPUT);
		pinMode(_pinE, INPUT);
	}

	//* INFO: Returns a bool indicates that sensor is enable/operateable.
	bool isEnable()
	{
		return _pinT != -1 && _pinE != -1;
	}

private:
	int _pinT;
	int _pinE;
};

#endif
