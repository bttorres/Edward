#include <functions.h>

// Initialize UART pins
#define TX 16
#define RX 17

void uart_init()
{
  // Configure UART communication
  uart_config_t uart_config = {
      .baud_rate = 115200,
      .data_bits = UART_DATA_8_BITS,
      .parity = UART_PARITY_DISABLE,
      .stop_bits = UART_STOP_BITS_1,
      .flow_ctrl = UART_HW_FLOWCTRL_DISABLE};
  uart_driver_install(UART_NUM_2, 2048, 0, 0, NULL, 0);
  uart_param_config(UART_NUM_2, &uart_config);
  uart_set_pin(UART_NUM_2, TX, RX, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}
