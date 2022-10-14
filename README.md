# This... is Edward

Edward is an ESP32 powered robot that can switch back and forth between an autonomous and controlled mode. 

## The code

The code in the "src/" folders is the code that he uses to function. It is split into two folders. One is in the Arduino structure (a modified C/C++ language) for the ESP32-CAM board and the other is in the ESP-IDF structure (regular C language). PlatformIO in Visual Studio Code was used for both.

## Edward's Parts and Their Functions:

In this repository is a PDF of the schematic depicting Edward's electronic parts and how they are connected.
* 1 ESP32-CAM board with OV2640 camera
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
  * Used as Edward's wheels
* 1 ball caster
  * Assists with movement
* 4 buck converters
  * Step down the voltages from the batteries to power the servos, ESP32-WROOM-32D dev board
* 1 boost converter
  * Boosts the voltage from the ESP32-WROOM-32D dev board (3.3V) to 5V to power the ultrasonic sensor
* 2 2000mAh 11.1V Li-ion batteries


## Edward's Web App

[Picture of the app](https://user-images.githubusercontent.com/55719532/191055793-7356e9bd-6d7e-492b-b6b2-d5128efd728e.jpeg)

Once the user connects to Edward's Wifi, they can go to the IP address (192.168.4.1) in their web browser. The web app allows the user to control Edward in controlled mode and switch between controlled and autonomous mode.

## Controlled Mode

In controlled mode, the user can drive Edward. They can have Edward go forward, backward, turn left, and turn right. They can also move Edward's "head" around and control his speed.

## Autonomous Mode

In autonomous mode, Edward roams free. He uses his sensors to drive and avoid obstacles/cliffs on his own. The user can use the web app to switch back to controlled mode at any time.


