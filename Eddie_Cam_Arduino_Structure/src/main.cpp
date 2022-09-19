#include <functions.h>

// Initialize hardware serial for UART communication
HardwareSerial Sender(1);
// ESP32-Cam creates it's own WiFi and acts as an Access Point
// ESP32-Cam provides IP address to go to for web app control
// IP address: 192.168.4.1
const char *ssid1 = "Eddies WiFi";
const char *password1 = "1234567890";
// Initialize needed variables
String finalData; /* String that data values will be
                      put into to properly send out */

/*/////////////////////////////////////////////////////////////////////////////
   Data structure from ESP32-Cam to ESP32:

   | Controlled/Autonomous |   Neck    | Left Wheel Speed | Right Wheel Speed |
   |-----------------------+-----------+------------------+-------------------|
   |        1 or 2         | 000 - 180 |    000 - 180     |    000 - 180      |

   For example: 1, 90, 135, 45
                1   = Controlled
                090 = Neck looking forward
                135 = Left wheel going forward at half speed
                045 = Right wheel going forward at half speed
*/
/////////////////////////////////////////////////////////////////////////////

void setup()
{
  // Silences brown outs
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  // Set up hardware serial with corresponding pins
  Sender.begin(115200, SERIAL_8N1, 1, 3);
  // Starting WiFi Access Point
  WiFi.softAP(ssid1, password1);
  IPAddress myIP = WiFi.softAPIP();
  // Configures camera pins
  cam_pin_config();
  // Start camera web server
  startCameraServer();
  // Configuring PWM channels for Falsh LED
  ledcSetup(6, 5000, 8); // 5000 hz PWM, 8-bit resolution and range from 0 to 255
  ledcAttachPin(4, 6);
  // Flash the built-in LED to know that everything's ready
  for (int i = 0; i < 3; i++)
  {
    ledcWrite(6, 10);
    delay(100);
    ledcWrite(6, 0);
    delay(100);
  }
}

void loop()
{
  // Convert Controlled/Autonomous from numbers
  // to letters to properly send the data
  if (sendVal[0] == 1) finalData += "c";
  else if (sendVal[0] == 2) finalData += "a";
  // Convert data to string to properly send the data in the correct format
  for (int i = 1; i < 4; i++) {
    if(sendVal[i] < 10) {
      finalData += 0;
      finalData += 0;
    }
    else if (sendVal[i] < 100) {
      finalData += 0;
    }
    finalData += sendVal[i];
  }
  Sender.println(finalData);  // Send data to ESP32
  delay(75);
  finalData = "";
}
