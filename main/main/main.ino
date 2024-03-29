#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <TimeLib.h>
#include <TimeAlarms.h>
#include "RTClib.h"
#include "LowPower.h"
#include <Dusk2Dawn.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);

// RTC time init
RTC_DS1307 rtc;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting Chicken Coop closer");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(150);
  myMotor->run(FORWARD);
  myMotor->run(RELEASE);

  syncTime();
  setDailyDoorCloseAlarm();
  // Alarm.alarmRepeat(dowSaturday, 8, 30, 0, syncTime);
  // Set the next alarm to close door for tomorrow
  Alarm.alarmRepeat(23, 0, 0, setDailyDoorCloseAlarm);
  // Debug to show that it is working
  // Alarm.timerRepeat(20, closeCoop);
  Serial.flush();
}

void loop() {
  digitalClockDisplay();
  Alarm.delay(1000); // wait one second between clock display
  
  Serial.flush();
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  syncTime();
}

void closeCoop() {  
  Serial.println("Turning on motor");

  myMotor->run(FORWARD);
  // How fast to run the motor
  myMotor->setSpeed(50);
  // How long to close door?
  delay(10000);
  // Turn off motor
  myMotor->run(RELEASE);
}

void syncTime() {
  DateTime now = rtc.now();
  setTime(now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year());
}


void digitalClockDisplay() {
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println();
}

void printDigits(int digits) {
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void setDailyDoorCloseAlarm() {
  int sunset = findSunset(true);
  Serial.println("Chicken door will close at: " + String(sunset + 1));
  // Close the Chicken Coop door daily
  Alarm.alarmOnce(sunset + 1, 0, 0, closeCoop);
}

int findSunset(bool dayLightSavings) {
  // Set Dusk2Dwan location
  Dusk2Dawn locationDusk2Dawn(51.3809, 0.5221, dayLightSavings ? 1 : 0);
  int sunsetMinutes = locationDusk2Dawn.sunset(year(), month(), day(), false);
  int sunsetHours = sunsetMinutes / 60;

  Serial.println("Sunset is at: " + String(sunsetMinutes) + " minutes from midnight");
  Serial.println("Sunset is at: " + String(sunsetHours) + " hours from midnight");
  return sunsetHours;
}

