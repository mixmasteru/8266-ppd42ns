# ppd42ns arduino
Arduino read Dust Particle Sensor - Shinyei PPD42NS

This is a Test for using the NodeMCU with the a dust sensor to track air quality

## install:
```
pio lib install 18 //Adafruit DHT Unified
```

TODO:
* ~~test PPD42NS with Arduino~~
* ~~test PPD42NS with NodeMCU and level converter~~
* send Data to API
* graph data

## Shinyei PPD42NS

from the data sheet:
This sensor is to create Digital (Lo Pulse) output to Particulate Matters(PM). Lo Pulse Occupancy time (LPO
time) is in proportion to PM concentration. The output from “P1” is for PM whose size is around 1 micro meter
or larger.

| Model | PPD 42NS |
|---|---|
| Detectable particle size | approx. 1 μm (minimum.) |
| Detectable  range  of  concentration  | 0~28,000 pcs/liter (0~8,000pcs/0.01 CF=283ml) |
| Supply  Voltage  | DC5V +/-10%    (CN1:Pin1=GND, Pin3=+5V) Ripple Voltage within 30mV |
| Operating Temperature Range  | 0~45 °C |
| Operating  Humidity  Range  | 95%rh or less (without dew condensation) |
| Power  consumption  | 90mA |
| Storage temperature  | -30~60°C |
| Time for stabilization  | 1 minute after power turned on |
| Dimensions | 59(W) × 45(H) × 22(D) [mm] |
| Weight  | 24g (approx.) |
| Output Method | Negative Logic, Digital output,Hi : over 4.0V(Rev.2)    Lo : under 0.7V (As Input impedance : 200kΩ) OP-Amp output, Pull-up resistor: 10kΩ |
