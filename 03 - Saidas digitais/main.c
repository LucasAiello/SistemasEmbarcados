#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define GREEN_LED GPIO_NUM_15
#define YELLOW_LED GPIO_NUM_16
#define RED_LED GPIO_NUM_17
#define BLUE_LED GPIO_NUM_18

#define DELAY_TIME_MS 500

void setup(void)
{
  uint8_t pins_size = 4;
  gpio_num_t pins[pins_size] = {GREEN_LED, YELLOW_LED, RED_LED, BLUE_LED};
  for(int i = 0; i < pins_size; i++)
  {
    gpio_reset_pin(pins[i]);
    esp_rom_gpio_pad_select_gpio(pins[i]);
    gpio_set_direction(pins[i], GPIO_MODE_OUTPUT);
  }
}

void level1(void)
{
  uint8_t current_state = 0;
  uint8_t max_state = 16;
  for (int i = 0; i < 16; i++)
  {
      gpio_set_level(GREEN_LED, (current_state >> 0) & 1);
      gpio_set_level(YELLOW_LED, (current_state >> 1) & 1);
      gpio_set_level(RED_LED, (current_state >> 2) & 1);
      gpio_set_level(BLUE_LED, (current_state >> 3) & 1);
      current_state = (current_state + 1) % max_state;
      vTaskDelay(pdMS_TO_TICKS(DELAY_TIME_MS));
  }
}

void level2(void)
{
  const int states_size = 9;
  int states[states_size] = {0x1, 0x2, 0x4, 0x8, 0x0, 0x8, 0x4, 0x2, 0x1};
  for(int i = 0; i < states_size; i++)
  {
    const int state = states[i];
    gpio_set_level(GREEN_LED, (state >> 0 & 1));
    gpio_set_level(YELLOW_LED, (state >> 1 & 1));
    gpio_set_level(RED_LED, (state >> 2 & 1));
    gpio_set_level(BLUE_LED, (state >> 3 & 1));
    vTaskDelay(pdMS_TO_TICKS(DELAY_TIME_MS));
  }
}


void loop(void)
{
  level1();
  gpio_set_level(GREEN_LED, 0);
  gpio_set_level(YELLOW_LED, 0);
  gpio_set_level(RED_LED, 0);
  gpio_set_level(BLUE_LED, 0);
  vTaskDelay(pdMS_TO_TICKS(DELAY_TIME_MS));
  level2();
}
