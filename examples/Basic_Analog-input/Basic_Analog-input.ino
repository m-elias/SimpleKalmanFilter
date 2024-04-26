#include "SimpleKalmanFilter.h"

/*
 This sample code demonstrates how to use the SimpleKalmanFilter object. 
 Use a potentiometer in Analog input A0 as a source for the reference real value.
 Some random noise will be generated over this value and used as a measured value.
 The estimated value obtained from SimpleKalmanFilter should match the real
 reference value.

 SimpleKalmanFilter(e_mea, e_est, q);
 e_mea: Measurement Uncertainty (lower number means greater certainty)
 e_est: Estimation Uncertainty 
 q: Process Noise               (higher number reacts quicker, ie. values can change rapidly)
 */
SimpleKalmanFilter simpleKalmanFilter(0.5, 1, 1);
//  0.5, 1, 1 works well for a fast responding analog input

// Serial output refresh time
const long SERIAL_REFRESH_TIME = 100;
uint32_t refresh_time;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
}

void loop() {

  // read a reference value from A0 and map it from 0 to 100
  float real_value = analogRead(A0) / 4096.0;
  
  // add a noise to the reference value and use as the measured value
  //float measured_value = real_value + random(-100,100)/100.0;

  // calculate the estimated value with Kalman Filter
  float estimated_value = simpleKalmanFilter.updateEstimate(real_value);

  // send to Serial output every 100ms
  // use the Serial Ploter for a good visualization
  if (millis() > refresh_time) {
    Serial.print(real_value, 4);
    Serial.print(",");
    //Serial.print(measured_value, 4);
    //Serial.print(",");
    Serial.print(estimated_value, 4);
    Serial.print(",");
    Serial.print(real_value / estimated_value, 4);
    Serial.print(",");
    Serial.print(simpleKalmanFilter.getEstError(), 4);
    Serial.print(",");
    Serial.print(simpleKalmanFilter.getKalmanGain(), 4);
    Serial.println();
    
    refresh_time = millis() + SERIAL_REFRESH_TIME;
  }

}