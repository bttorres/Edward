#include <functions.h>

// Initialize sensors with corresponding GPIOs
#define right_IR 23
#define left_IR 39
#define left_cliff 34
#define right_cliff 22
// Initialize needed, static variables

#define front 30          /* Max distance from ultrasonic sensor before \
                              robot decides to turn away from obstacle */
#define speed_one 1.3     // Selected speed for right wheel to go forward
#define speed_two 1.7     // Selected speed for left wheel to go forward
#define speed_stopped 1.5 // Speed for wheels to be stopped
#define look_right 0.5    // Value for neck servo to look 90 deg to the right
#define look_left 2.5     // Value for neck servo to look 90 deg to the left
#define look_forward 1.5  // Value for neck servo to look forward
// Initialize needed, changeable variables
int corner = 0;        // Value to determine if corner is detected
int time_left = 2000;  // Time of last left turn used to detect corner
int time_right = 1000; // Time of last right turn used to detect corner
int time_center = 0;   /* Time that obstacle was last detected within
                           "front" boundary of ultrasonic sensor */
int right_distance;    /* Distance measured by ultrasonic sensor
                           when looking right */
int left_distance;     /* Distance measured by ultrasonic sensor
                           when looking right */

// Main function
void app_main()
{
  // Call needed functions to start up Eddie
  gpio_init();                // Initializes GPIO pins
  uart_init();                // Initializes UART communication
  ultrasonic_timer_init();    // Initializes ultrasonic timer interrupt
  neck_init();                // Initializes PWM for neck servo
  right_init();               // Initializes PWM for right wheel
  left_init();                // Initializes PWM for left wheel
  neck_servo(look_forward);   // Defaults neck position to face forward
  right_servo(speed_stopped); // Defaults right wheel to stopped
  left_servo(speed_stopped);  // Defaults left wheel to stopped

  while (1)
  {
    // Variable where UART data is stored
    char *data = (char *)malloc(1025);
    // Read UART data and store data length
    const int rxBytes = uart_read_bytes(UART_NUM_2,
                                        data, 1024,
                                        pdMS_TO_TICKS(50));
    // If data has been read, begin
    if (rxBytes > 0)
    {
      data[rxBytes] = 0; // Mark where the data ends
      /* If first character of received data is c,
      Eddie enters controlled mode */
      if (data[0] == 'c')
      {
        set_neck(data);  /* Converts subscript of data and maps it
          to a usable neck position value */
        set_right(data); /* Converts subscript of data and maps it
         to a usable right wheel value */
        set_left(data);  /* Converts subscript of data and maps it
          to a usable left wheel value */
        // Prints servo values and received UART data (For testing)
        printf("neck: %f  |  right: %f  |  left: %f  |  data: %s",
               neck_position, right_speed, left_speed, data);
        // Assigns values to servos
        neck_servo(neck_position);
        right_servo(right_speed);
        left_servo(left_speed);
      }
      else
      {
        printf("Now in autonomous mode\n"); // For testing
        // If no obstacles near by and ground is detected, go straight
        if (distance >= front &&
            gpio_get_level(right_IR) == 1 &&
            gpio_get_level(left_IR) == 1 &&
            gpio_get_level(right_cliff) == 0 &&
            gpio_get_level(left_cliff) == 0)
        {
          // Eddie goes forward and looks forward
          right_servo(speed_one);
          left_servo(speed_two);
          neck_servo(look_forward);
        }
        // If cliff detected, back up, and then turn around ~180 deg
        else if (gpio_get_level(right_cliff) == 1 ||
                 gpio_get_level(left_cliff) == 1)
        {
          // Eddie goes backward for 500 ms
          right_servo(speed_two);
          left_servo(speed_one);
          vTaskDelay(pdMS_TO_TICKS(500));
          // Eddie turns around (to the right) for 850 ms
          right_servo(speed_two);
          left_servo(speed_two);
          neck_servo(look_right);
          vTaskDelay(pdMS_TO_TICKS(850));
        }
        /* If left obstacle detected, turn right
        until said wall is not detected */
        else if (gpio_get_level(left_IR) == 0)
        {
          // Eddie turns to the right
          right_servo(speed_two);
          left_servo(speed_two);
          /* If time between left and right turns is too small
          (within 500 ms), there is probably a corner.
          Turn ~180 deg */
          time_left = esp_timer_get_time();
          if (abs(time_left - time_right) < 500)
          {
            // Eddie turns around (to the right) for 850 ms
            right_servo(speed_two);
            left_servo(speed_two);
            vTaskDelay(pdMS_TO_TICKS(850));
          }
        }
        /* If right obstacle detected, turn left
        until said wall is not detected */
        else if (gpio_get_level(right_IR) == 0)
        {
          // Eddie turns to the left
          right_servo(speed_one);
          left_servo(speed_one);
          /* If time between left and right turns is too small,
          there is probably a corner. turn ~180 deg */
          time_right = esp_timer_get_time();
          if (abs(time_right - time_left) < 500)
          {
            // Eddie turns around (to the left) for 850 ms
            right_servo(speed_one);
            left_servo(speed_one);
            vTaskDelay(pdMS_TO_TICKS(850));
          }
        }
        /* If obstacle in front detected, look right, then look
        left, determine which way has the furthest obstacle,
        then go that way */
        else if (distance < front)
        {
          /* If time between left and right turns is too small,
          there is probably a corner. turn ~180 deg */
          time_center = esp_timer_get_time();
          if (abs(time_center - time_left) < 500)
          {
            // Eddie turns around (to the left) for 850 ms
            right_servo(speed_one);
            left_servo(speed_one);
            vTaskDelay(pdMS_TO_TICKS(850));
          }
          if (abs(time_center - time_right) < 500)
          {
            // Eddie turns around (to the right) for 850 ms
            right_servo(speed_two);
            left_servo(speed_two);
            vTaskDelay(pdMS_TO_TICKS(850));
          }
          if (abs(time_center - time_left) >= 500 &&
              abs(time_center - time_right) >= 500)
          {
            /* Eddie stops, looks right, takes distance
            measurement, looks left, takes distance
            measurement, and then looks forward */
            right_servo(speed_stopped);
            left_servo(speed_stopped);
            neck_servo(look_right);
            vTaskDelay(pdMS_TO_TICKS(1000));
            right_distance = distance;
            neck_servo(look_left);
            vTaskDelay(pdMS_TO_TICKS(1000));
            left_distance = distance;
            neck_servo(look_forward);
            /* If there's more space to the right, Eddie turns and
            goes to the right. If there's more space to the
            left, Eddie turns and goes to the left. */
            if (right_distance >= left_distance)
            {
              // Eddie turns to the right for 500 ms
              right_servo(speed_two);
              left_servo(speed_two);
              vTaskDelay(pdMS_TO_TICKS(500));
            }
            else
            {
              // Eddie turns to the left for 500 ms
              right_servo(speed_one);
              left_servo(speed_one);
              vTaskDelay(pdMS_TO_TICKS(500));
            }
          }
        }
      }
    }
    // Clear UART data so that data can be repeatly read and stored
    free(data);
  }
}
