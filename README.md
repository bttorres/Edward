# Edward

## This... is Edward (a.k.a Eddie)

Eddie is an ESP32 powered robot that can switch back and forth between an autonomous and controlled mode. The code in this repository is the code that he uses to function.

## His parts and their functions:

* 1 ESP32-CAM board
  * Creates its own Wifi, generates a web app on its IP, acts as an access point (for the user to connect to the Wifi and access the web app), recieves data from the web app, and sends the needed data to the ESP32-WROOM-32D dev board through UART communication
* 1 ESP32-WROOM-32D dev board
  * Recieves data from the ESP32-CAM board and controls the sensors and servos
* 4 IR sensors
  * Detects nearby obstacles and cliffs
* 1 ultrasonic sensor
  * Measures the distance from nearby obstacles
* 1 regular 180 degree servo motor
  * Used as a neck to pan the ultrasonic sensor and the camera of the ESP32-CAM board
* 2 continuous servo motors
  * Used as Eddie's wheels
* 1 ball caster
  * Assists with movement
* 4 buck converters
  * Step down the voltages from the batteries to power the servos, ESP32-WROOM-32D dev board
* 1 boost converter
  * Boosts the voltage from the ESP32-WROOM-32D dev board (3.3V) to 5V to power the ultrasonic sensor
* 2 2000mAh 11.1V Li-ion batteries!


# Eddie's Web App

[webapp](https://user-images.githubusercontent.com/55719532/191055793-7356e9bd-6d7e-492b-b6b2-d5128efd728e.jpeg)

* The web app

## His controlled mode

In controlled mode, the user can drive Eddie. They can have hime turn left, right, go forward, and backward.
