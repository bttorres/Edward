#include <functions.h>

// Initialize servos with corresponding GPIOs
#define neck 14
#define right 25
#define left 12
// Initialize sensors with corresponding GPIOs
#define right_IR 23
#define right_IR_power 27
#define left_IR 39
#define left_IR_power 26
#define left_cliff 34
#define left_cliff_power 21
#define right_cliff 22
#define right_cliff_power 19
#define trig 32
#define echo 33
#define ultra_power 18
// Initialize UART pins
#define TX 16
#define RX 17
// Default ESP32 interrupt flag
#define ESP_intr_flag_default 0
// Initialize needed variables
long echo_start = 0; // Beginning of ultrasonic echo signal
long echo_end = 0;   // Ending of ultrasonic echo signal
long duration;       // Ultrasonic echo measurement
int distance;        // Distance measured by ultrasonic sensor

void IRAM_ATTR echo_isr()
{
  /* Ultrasonic reciever outputs signal when ultrasonic sound comes back to
      the sensor. The duration of the signal is timed and used to measure the
          distance from the object in front of the sensor. */
  echo_start = esp_timer_get_time();
  while (gpio_get_level(echo) == 1)
  {
    echo_end = esp_timer_get_time();
  }
  duration = echo_end - echo_start;
  distance = duration * 0.034 / 2;
  echo_end = 0;
  echo_start = 0;
}

void gpio_init()
{
  // Initialize GPIO pins
  gpio_pad_select_gpio(neck);
  gpio_pad_select_gpio(right);
  gpio_pad_select_gpio(left);
  gpio_pad_select_gpio(TX);
  gpio_pad_select_gpio(RX);
  gpio_pad_select_gpio(right_IR);
  gpio_pad_select_gpio(right_IR_power);
  gpio_pad_select_gpio(left_IR);
  gpio_pad_select_gpio(left_IR_power);
  gpio_pad_select_gpio(left_cliff);
  gpio_pad_select_gpio(left_cliff_power);
  gpio_pad_select_gpio(right_cliff);
  gpio_pad_select_gpio(right_cliff_power);
  gpio_pad_select_gpio(trig);
  gpio_pad_select_gpio(echo);
  gpio_pad_select_gpio(ultra_power);

  // Set GPIO pins as input or output
  gpio_set_direction(neck, GPIO_MODE_OUTPUT);
  gpio_set_direction(right, GPIO_MODE_OUTPUT);
  gpio_set_direction(left, GPIO_MODE_OUTPUT);
  gpio_set_direction(TX, GPIO_MODE_OUTPUT);
  gpio_set_direction(RX, GPIO_MODE_INPUT);
  gpio_set_direction(right_IR, GPIO_MODE_INPUT);
  gpio_set_direction(right_IR_power, GPIO_MODE_OUTPUT);
  gpio_set_direction(left_IR, GPIO_MODE_INPUT);
  gpio_set_direction(left_IR_power, GPIO_MODE_OUTPUT);
  gpio_set_direction(left_cliff, GPIO_MODE_INPUT);
  gpio_set_direction(left_cliff_power, GPIO_MODE_OUTPUT);
  gpio_set_direction(right_cliff, GPIO_MODE_INPUT);
  gpio_set_direction(right_cliff_power, GPIO_MODE_OUTPUT);
  gpio_set_direction(trig, GPIO_MODE_OUTPUT);
  gpio_set_direction(echo, GPIO_MODE_INPUT);
  gpio_set_direction(ultra_power, GPIO_MODE_OUTPUT);

  // Turn on sensors
  gpio_set_level(right_IR_power, 1);
  gpio_set_level(left_IR_power, 1);
  gpio_set_level(left_cliff_power, 1);
  gpio_set_level(right_cliff_power, 1);
  gpio_set_level(ultra_power, 1);

  // Enable interrupt on rising edge of echo pin
  gpio_set_intr_type(echo, GPIO_INTR_POSEDGE);
  /* Install GPIO ISR handler service, that allows
      per-pin GPIO interrupt handlers */
  gpio_install_isr_service(ESP_intr_flag_default);
  // Attach the interrupt service routine
  gpio_isr_handler_add(echo, echo_isr, NULL);
}
