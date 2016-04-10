//  AirQuality sensor - pin A0
#include "DHT.h"
#include"AirQuality.h"
#include <Wire.h>
AirQuality airqualitysensor;
int current_quality =-1;
int airqualitysensorPin = A0;

//Soil moisture - pin A1
int sensorPin = A1;    // select the input pin for the potentiometer
int moistness = 0;  // variable to store the value coming from the sensor

// DHT humidity/temperature sensor
//#include "DHT.h"
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11 
DHT dht(DHTPIN, DHTTYPE);

byte comm=0b00000000;

void setup() {
  pinMode(13,OUTPUT);
   Serial.begin(9600);  
    //  DHT sensor
    dht.begin();
   //  AirQuality sensor
   airqualitysensor.init(airqualitysensorPin);
  Wire.begin(2); // join i2c bus (address optional for master)
  Wire.onRequest(requestEvent); // register event
}

void loop() {
  delay(100);   // Wait a few seconds between measurements.
  
    // read the value from the DHT sensor:
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
   // Serial.println("Failed to read from DHT sensor!");
     digitalWrite(13,LOW);
    return;
  }
  digitalWrite(13,HIGH);
  
  
  // read the value from the moisture sensor:
  moistness = analogRead(sensorPin);    
//  Serial.print("moistness = " );                       
//  Serial.println(moistness);                   
  
  // read the value from the AirQuality sensor:
  current_quality=airqualitysensor.slope();
   /* if (current_quality >= 0)// if a valid data returned.
    {
        if (current_quality==0)
            Serial.println("High pollution! Force signal active");
        else if (current_quality==1)
            Serial.println("High pollution!");
        else if (current_quality==2)
            Serial.println("Low pollution!");
        else if (current_quality ==3)
            Serial.println("Fresh air");
    }
  */
  Serial.print("A:");  Serial.print(current_quality); Serial.print("\t");
  Serial.print("M: "); Serial.print(moistness);  Serial.print("\t");
  Serial.print("T: "); Serial.print(t);  Serial.print("C\t");
  Serial.print("H: "); Serial.print(h);  Serial.println(" %");

  if (current_quality == 0) {
       bitWrite(comm,0,0);    bitWrite(comm,1,0);
  }
  else if (current_quality == 1) {
        bitWrite(comm,0,0);    bitWrite(comm,1,1);
  }
    else if (current_quality == 2) {
      bitWrite(comm,0,1);    bitWrite(comm,1,0);
  }
    else if (current_quality == 3) {
    bitWrite(comm,0,1);    bitWrite(comm,1,1);
  }
  
   if (moistness < 200) {
       bitWrite(comm,2,0);    bitWrite(comm,3,0);
  }
  else if (moistness >= 200  && moistness <= 400) {
        bitWrite(comm,2,0);    bitWrite(comm,3,1);
  }
      else if (moistness > 400) {
    bitWrite(comm,2,1);    bitWrite(comm,3,0);
  }
  
    if (t < 15.00) {
       bitWrite(comm,4,0);    bitWrite(comm,5,0);
  }
  else if (t >= 15.00  && t <= 30.00) {
        bitWrite(comm,4,0);    bitWrite(comm,5,1);
  }
      else if (t > 30.00) {
    bitWrite(comm,4,1);    bitWrite(comm,5,1);
  }
  
      if (h < 30.00) {
       bitWrite(comm,6,0);    bitWrite(comm,7,0);
  }
  else if (h >= 30.00  && h <= 50.00) {
        bitWrite(comm,6,0);    bitWrite(comm,7,1);
  }
      else if (h > 50.00) {
    bitWrite(comm,6,1);    bitWrite(comm,7,1);
  }
  Serial.println(comm,BIN);
  //Serial.write(0xFF);
  //Serial.write(comm);
  //Serial.write(0xFA);
  /*
  Wire.beginTransmission(8); // transmit to device #8
  //Wire.write("x is ");        // sends five bytes
  Wire.write(comm);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  */
}

void requestEvent() {
  Wire.write(comm); // respond with message of 6 bytes
  // as expected by master
}

ISR(TIMER2_OVF_vect) // Airquality sensor Interrupt routine
{
	if(airqualitysensor.counter==122)//set 2 seconds as a detected duty
	{

			airqualitysensor.last_vol=airqualitysensor.first_vol;
			airqualitysensor.first_vol=analogRead(airqualitysensorPin);
			airqualitysensor.counter=0;
			airqualitysensor.timer_index=1;
			PORTB=PORTB^0x20;
	}
	else
	{
		airqualitysensor.counter++;
	}
}
