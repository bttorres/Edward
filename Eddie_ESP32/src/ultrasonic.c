#include <functions.h>

// Initialize ultrasonic data pins
#define trig 32
#define echo 33

void ultrasonic_timer_init()
{
  /* Initialize ultrasonic sensor timer interrupt
      to take a measurement every 50ms */
  TimerHandle_t ultrasonic_timer = xTimerCreate("ultrasonic_timer",
                                                pdMS_TO_TICKS(50),
                                                pdTRUE, (void *)1,
                                                ultrasonic_timer_function);
  // Start ultrasonic sensor timer
  xTimerStart(ultrasonic_timer, 0);
  /* Wait 300ms to allow ultrasonic sensor to
      take a meausurement before other code runs */
  vTaskDelay(pdMS_TO_TICKS(300));
}

void ultrasonic_timer_function()
{
  /* Ultrasonic transmitter emits ultrasonic
      sound to measure distance from object */
  gpio_set_level(trig, 0);
  ets_delay_us(2);
  gpio_set_level(trig, 1);
  ets_delay_us(10);
  gpio_set_level(trig, 0);
}
