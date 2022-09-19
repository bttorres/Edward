#include <functions.h>

// Initialize servos with corresponding GPIOs
#define neck 14  // 0.5 - 2.5
#define right 25 // 1.1 - 1.9
#define left 12  // 1.1 - 1.9

double neck_position = 0.0; // Value to control neck servo position
double right_speed = 0.0;   // Value to control right wheel speed
double left_speed = 0.0;    // Value to control left wheel speed

void neck_init()
{
  // Stops any previously made PWM signals on channel 2
  ledc_stop(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, 0);
  // Initializes and configures PWM
  ledc_timer_config_t ledc_timer = {
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .timer_num = LEDC_TIMER_2,
      .duty_resolution = LEDC_TIMER_13_BIT,
      .freq_hz = 50,
      .clk_cfg = LEDC_AUTO_CLK};
  ledc_timer_config(&ledc_timer);
  ledc_channel_config_t ledc_channel = {
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .channel = LEDC_CHANNEL_2,
      .timer_sel = LEDC_TIMER_2,
      .intr_type = LEDC_INTR_DISABLE,
      .gpio_num = neck,
      .duty = 0,
      .hpoint = 0};
  ledc_channel_config(&ledc_channel);
}

void right_init()
{
  // Stops any previously made PWM signals on channel 0
  ledc_stop(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
  // Initializes and configures PWM
  ledc_timer_config_t ledc_timer = {
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .timer_num = LEDC_TIMER_0,
      .duty_resolution = LEDC_TIMER_13_BIT,
      .freq_hz = 50,
      .clk_cfg = LEDC_AUTO_CLK};
  ledc_timer_config(&ledc_timer);
  ledc_channel_config_t ledc_channel = {
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .channel = LEDC_CHANNEL_0,
      .timer_sel = LEDC_TIMER_0,
      .intr_type = LEDC_INTR_DISABLE,
      .gpio_num = right,
      .duty = 0,
      .hpoint = 0};
  ledc_channel_config(&ledc_channel);
}

void left_init()
{
  // Stops any previously made PWM signals on channel 1
  ledc_stop(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, 0);
  // Initializes and configures PWM
  ledc_timer_config_t ledc_timer = {
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .timer_num = LEDC_TIMER_1,
      .duty_resolution = LEDC_TIMER_13_BIT,
      .freq_hz = 50,
      .clk_cfg = LEDC_AUTO_CLK};
  ledc_timer_config(&ledc_timer);
  ledc_channel_config_t ledc_channel = {
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .channel = LEDC_CHANNEL_1,
      .timer_sel = LEDC_TIMER_1,
      .intr_type = LEDC_INTR_DISABLE,
      .gpio_num = left,
      .duty = 0,
      .hpoint = 0};
  ledc_channel_config(&ledc_channel);
}

void neck_servo(double value)
{
  // Maps value (neck_position) to correct duty cycle
  int duty = (int)(100.0 * (value / 20.0) * 81.91);
  // For testing
  /* printf("%fms, duty = %f%% -> %d\n", position,
            100.0 * (position / 20.0), duty); */
  // Sets duty to PWM channel 2
  ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, duty);
  ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2);
}

void right_servo(double value)
{
  // Maps value (right_speed) to correct duty cycle
  int duty = (int)(100.0 * (value / 20.0) * 81.91);
  // For testing
  /* printf("%fms, duty = %f%% -> %d\n", position,
            100.0 * (position / 20.0), duty); */
  // Sets duty to PWM channel 0
  ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
  ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}

void left_servo(double value)
{
  // Maps value (left_speed) to correct duty cycle
  int duty = (int)(100.0 * (value / 20.0) * 81.91);
  // For testing
  /* printf("%fms, duty = %f%% -> %d\n", position,
            100.0 * (position / 20.0), duty); */
  // Sets duty to PWM channel 0
  ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, duty);
  ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
}

void set_neck(char *input)
{
  /* Takes in UART data as "input" and maps the corresponding
      subscript of the data to neck_position */
  neck_position = 0.0;
  if (input[1] == '1')
  {
    neck_position += 100;
  }
  switch (input[2])
  {
  case '1':
    neck_position += 10;
    break;
  case '2':
    neck_position += 20;
    break;
  case '3':
    neck_position += 30;
    break;
  case '4':
    neck_position += 40;
    break;
  case '5':
    neck_position += 50;
    break;
  case '6':
    neck_position += 60;
    break;
  case '7':
    neck_position += 70;
    break;
  case '8':
    neck_position += 80;
    break;
  case '9':
    neck_position += 90;
    break;
  default:
    neck_position += 0;
  }
  switch (input[3])
  {
  case '1':
    neck_position += 1;
    break;
  case '2':
    neck_position += 2;
    break;
  case '3':
    neck_position += 3;
    break;
  case '4':
    neck_position += 4;
    break;
  case '5':
    neck_position += 5;
    break;
  case '6':
    neck_position += 6;
    break;
  case '7':
    neck_position += 7;
    break;
  case '8':
    neck_position += 8;
    break;
  case '9':
    neck_position += 9;
    break;
  default:
    neck_position += 0;
  }
  /* Neck_position needs to be mapped to a corresponding
      value in between 0.5 and 2.5 */
  neck_position = ((200.0 / 180.0 * neck_position) + 50.0) / 100.0;
}

void set_right(char *input)
{
  /* Takes in UART data as "input" and maps the corresponding
      subscript of the data to right_speed */
  right_speed = 0.0;
  if (input[4] == '1')
  {
    right_speed += 100;
  }
  switch (input[5])
  {
  case '1':
    right_speed += 10;
    break;
  case '2':
    right_speed += 20;
    break;
  case '3':
    right_speed += 30;
    break;
  case '4':
    right_speed += 40;
    break;
  case '5':
    right_speed += 50;
    break;
  case '6':
    right_speed += 60;
    break;
  case '7':
    right_speed += 70;
    break;
  case '8':
    right_speed += 80;
    break;
  case '9':
    right_speed += 90;
    break;
  default:
    right_speed += 0;
  }
  switch (input[6])
  {
  case '1':
    right_speed += 1;
    break;
  case '2':
    right_speed += 2;
    break;
  case '3':
    right_speed += 3;
    break;
  case '4':
    right_speed += 4;
    break;
  case '5':
    right_speed += 5;
    break;
  case '6':
    right_speed += 6;
    break;
  case '7':
    right_speed += 7;
    break;
  case '8':
    right_speed += 8;
    break;
  case '9':
    right_speed += 9;
    break;
  default:
    right_speed += 0;
  }
  /* Right_speed needs to be mapped to a corresponding
      value in between 1.1 and 1.9 */
  right_speed = ((80.0 / 180.0 * right_speed) + 110.0) / 100.0;
}

void set_left(char *input)
{
  /* Takes in UART data as "input" and maps the corresponding
      subscript of the data to left_speed */
  left_speed = 0.0;
  if (input[7] == '1')
  {
    left_speed += 100;
  }
  switch (input[8])
  {
  case '1':
    left_speed += 10;
    break;
  case '2':
    left_speed += 20;
    break;
  case '3':
    left_speed += 30;
    break;
  case '4':
    left_speed += 40;
    break;
  case '5':
    left_speed += 50;
    break;
  case '6':
    left_speed += 60;
    break;
  case '7':
    left_speed += 70;
    break;
  case '8':
    left_speed += 80;
    break;
  case '9':
    left_speed += 90;
    break;
  default:
    left_speed += 0;
  }
  switch (input[9])
  {
  case '1':
    left_speed += 1;
    break;
  case '2':
    left_speed += 2;
    break;
  case '3':
    left_speed += 3;
    break;
  case '4':
    left_speed += 4;
    break;
  case '5':
    left_speed += 5;
    break;
  case '6':
    left_speed += 6;
    break;
  case '7':
    left_speed += 7;
    break;
  case '8':
    left_speed += 8;
    break;
  case '9':
    left_speed += 9;
    break;
  default:
    left_speed += 0;
  }
  /* Left_speed needs to be mapped to a corresponding
      value in between 1.1 and 1.9 */
  left_speed = ((80.0 / 180.0 * left_speed) + 110.0) / 100.0;
}
