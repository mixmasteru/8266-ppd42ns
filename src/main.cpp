/**
 * ESP8266 Arduino Dust Sensor for Shinyei PPD42NS
 * connect the sensor as follows :
 * pin 1 (green)  -> GND
 * pin 3 (yellow) -> Vin 5V
 * pin 2 (white) -> Pin D1
 * pin 4 (black) -> Pin D2
 * pin 5 (red)   -> unused!
 *
 * Based on: https://github.com/empierre/arduino/blob/master/DustSensor_Shinyei_PPD42NS.ino
 * Datasheet:  https://yadom.fr/downloadable/download/sample/sample_id/41/
*/

#include "Arduino.h"
#include <SPI.h>
#include "DHT.h"

#define DHTTYPE DHT22
#define DHTPIN D3

#define CHILD_ID_DUST_PM10            0
#define CHILD_ID_DUST_PM25            1
#define DUST_SENSOR_DIGITAL_PIN_PM10  D1
#define DUST_SENSOR_DIGITAL_PIN_PM25  D2

DHT dht(DHTPIN, DHTTYPE);
unsigned long sampletime_ms = 30000;
long concentrationPM25 = 0;
long concentrationPM10 = 0;

long getPM(int pin)
{
  unsigned long lowpulseoccupancy = 0;
  unsigned long starttime = millis();
  unsigned long endtime;
  long concentration = 0;
  float ratio = 0;

  while (true) {
    //lowpulseoccupancy represents the Lo Pulse Occupancy Time(LPO Time)
    lowpulseoccupancy += pulseIn(pin, LOW);
	  endtime = millis();

	  if ((endtime-starttime) > sampletime_ms)
	  {
      Serial.print("lowpulseoccupancy: ");
      Serial.println(lowpulseoccupancy);
      //ratio reflects on which level LPO Time takes up the whole sample time
      //ratio = (lowpulseoccupancy-endtime+starttime)/(sampletime_ms*10.0);  // Integer percentage 0=>100
      ratio = lowpulseoccupancy/((endtime-starttime)*10.0);  // Integer percentage 0=>100
      //concentration is a figure that has physical meaning. It's calculated from the characteristic graph below by using the LPO time.
      concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
      return concentration;
    }
  }
}

void setup()
{
  pinMode(DUST_SENSOR_DIGITAL_PIN_PM10,INPUT);
  pinMode(DUST_SENSOR_DIGITAL_PIN_PM25,INPUT);
  delay(1000);
  Serial.begin(115200);
  Serial.println("start");
}

float calcPPMV(long concentration, float temp)
{
  //ppmv=mg/m3 * (0.08205*Tmp)/Molecular_mass
  //0.08205   = Universal gas constant in atm·m3/(kmol·K)
  float ppmv = (concentration*0.0283168/100/1000) *  (0.08205*temp)/0.01;
  ppmv*=1000;//to µg/m³
  return ppmv;
}

void loop()
{
  float temp = dht.readTemperature();
  float hume = dht.readHumidity();
  Serial.print("temp: ");
  Serial.println(temp);
  Serial.print("hume: ");
  Serial.println(hume);

  //get PM 2.5 density of particles over 2.5 μm.
  concentrationPM25 = getPM(DUST_SENSOR_DIGITAL_PIN_PM25);
  float ppmv = calcPPMV(concentrationPM25,temp);
  Serial.print("PM25: ");
  Serial.println(concentrationPM25);
  Serial.println(ppmv);

  //get PM 1.0 - density of particles over 1 μm.
  concentrationPM10 = getPM(DUST_SENSOR_DIGITAL_PIN_PM10);
  ppmv= calcPPMV(concentrationPM10,temp);
  Serial.print("PM10: ");
  Serial.println(concentrationPM10);
  Serial.println(ppmv);
  Serial.print("\n");

}
