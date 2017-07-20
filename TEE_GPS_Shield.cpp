#include "TEE_GPS_Shield.h"
int count;
int lastIndex;
String inputString;
String gpgga[13];
byte type;
GPS::GPS()
{
	
}
void GPS::begin(SoftwareSerial *serial)
{
	serial->begin(9600);
	_Serial = serial;
}
void GPS::begin(HardwareSerial *serial)
{
	serial->begin(9600);
	_Serial = serial;

	while (!_Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
	}
}
void GPS::gpsType(byte mode)						// Select GPGGA, GOOGLE
{
	if(mode==1)
	{
		type=1;
	}
}

void GPS::read(byte mode)							// Read data (NMEA) & substring add to variable (NMEA)
{	
	while (_Serial->available()) 
	{
		char inChar = (char)_Serial->read();
		inputString += inChar;
		if (inChar == '\r') 
		{
			if (inputString.indexOf("GGA") != -1)
			{
				Serial.print(inputString);			// Show GPGGA
				
				for (int i = 0; i < inputString.length(); i++)
				{
					if (inputString.substring(i, i + 1) == ",")
					{
						gpgga[count] = inputString.substring(lastIndex, i);
						lastIndex = i + 1;
						count++;
					}
				}
				//Utctime = gpgga[1];
				//Latitude = gpgga[2];
				//Longitude = gpgga[4];
				//Altitude = gpgga[9];
			}
			if(mode==1) 							// Show All Data NMEA
			{
				Serial.print(inputString);			
			}
			inputString = "";
			count = 0;
			lastIndex = 0;
		}
	}
}
String GPS::getUtctime()							// get Time
{
	String Utctime;
	if(gpgga[1]!="")
	{
		Utctime = gpgga[1];
	}
	else
	{
		Utctime = "No fix";
	}
	return Utctime;
}
// 1350.4622,N  -> Latitude  ->  13 degrees 50 minutes and 46.22 seconds
// 10032.5133,E -> Longitude ->  100 degrees 32 minutes and 51.33 seconds
String GPS::getLatitude()							// get Latitude
{
	String Latitude;
	if(gpgga[2]!="")
	{
		Latitude = gpgga[2];
		if(type==1)
		{
			Latitude = latitudeGoogle(Latitude);
		}
	}
	else
	{
		Latitude = "No fix";
	}
	return Latitude;
}
String GPS::getLongitude()							// get Longitude
{
	String Longitude;
	if(gpgga[4]!="")
	{
		Longitude = gpgga[4];
		if(type==1)
		{
			Longitude = longitudeGoogle(Longitude);
		}
	}
	else
	{
		Longitude = "No fix";
	}
	return Longitude;
}
String GPS::getAltitude()							// get Altitude
{
	String Altitude;
	if(gpgga[9]!="")
	{
		Altitude = gpgga[9];
	}
	else
	{
		Altitude = "No fix";
	}
	return Altitude;
}

String GPS::latitudeGoogle(String latitude)			// Convert latitude (NMEA) To GOOGLE
{
	int indexdotlatitude = latitude.indexOf(".");
	float lat = latitude.substring(indexdotlatitude-2).toFloat();	
	if(latitude.length()==8)
	{
	  float degreelat = latitude.substring(0,1).toFloat();
	  lat = degreelat + (lat/60.00);
	}
	else if(latitude.length()==9)
	{
	  float degreelat = latitude.substring(0,2).toFloat();
	  lat = degreelat + (lat/60.00);
	}
	latitude = String(lat,5);
	return latitude;
}
String GPS::longitudeGoogle(String longitude)		// Convert longitude (NMEA) To GOOGLE
{
	int indexdotLongitude = longitude.indexOf(".");
	float lon = longitude.substring(indexdotLongitude-2).toFloat();
	
	if(longitude.length()==9)
	{
	  float degreelon = longitude.substring(0,2).toFloat();
	  lon = degreelon + (lon/60.00);
	}
	else if(longitude.length()==9)
	{
	  float degreelon = longitude.substring(0,2).toFloat();
	  lon = degreelon + (lon/60.00);
	}
	else if(longitude.length()==10)
	{
	  float degreelon = longitude.substring(0,3).toFloat();
	  lon = degreelon + (lon/60.00);
	}
	longitude = String(lon,5);
	return longitude;
}	
