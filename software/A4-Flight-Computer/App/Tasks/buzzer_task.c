/**
 * @file buzzer_task.c
 * @brief Buzzer task implementation.
 * @details This file contains the implementation of the buzzer task.
 */

#include "buzzer_task.h"
#include "app_freertos.h"
#include "vehicle_state.h"
#include "a4_flightcomputer_bsp.h"

#define BUZZER_FREQUENCY_HZ 4000U // 4 kHz
#define MORSE_UNIT_MS 80U
#define STATUS_PERIOD_MS 2000U
#define STARTUP_PAUSE_MS 1000U

typedef struct
{
  bool tone;
  uint16_t frequency_hz;
  uint16_t duration_ms;
} buzzer_tone_t;

static void PlayMorseSymbol(char symbol)
{
  uint16_t duration = (symbol == '.') ? MORSE_UNIT_MS : (3 * MORSE_UNIT_MS);
  BSP_Buzzer_Start(BUZZER_FREQUENCY_HZ);
  osDelay(duration);
  BSP_Buzzer_Stop();
  osDelay(MORSE_UNIT_MS); // inter-symbol gap
}

static void PlayMorseCode(const char *code)
{
  while (*code)
  {
    if (*code == '.' || *code == '-')
    {
      PlayMorseSymbol(*code);
    }
    code++;
  }
  osDelay(2U * MORSE_UNIT_MS); // inter-character gap
}

static void PlayBatteryVoltage(uint16_t voltage_mV)
{
  // Convert voltage to a string representation in morse code
  // For example, 3700 mV -> "3.7"
  uint8_t whole_volts = voltage_mV / 1000;
  uint8_t tenths_volts = (voltage_mV % 1000) / 100;

  static const char *morse_digits[] = {
      "-----", ".----", "..---", "...--", "....-",
      ".....", "-....", "--...", "---..", "----.",
      ".-.-.-" // decimal point
  };

  for (uint8_t divisor = 100U; divisor > 0; divisor /= 10)
  {
    if (whole_volts >= divisor)
    {
      uint8_t digit = whole_volts / divisor;
      PlayMorseCode(morse_digits[digit]);
      whole_volts %= divisor;
    }
  }

  PlayMorseCode(morse_digits[10]); // decimal point

  PlayMorseCode(morse_digits[tenths_volts]);
}

/**
 * @brief Function implementing the buzzerTask thread.
 * @param argument: Not used
 * @retval None
 */
void StartBuzzerTask(void *argument)
{
  vehicle_state_t vehicle_state;
  bool voltage_played = false;
  TickType_t next_status_time;

  // set a fake psu state for testing
  psu_state_t test_psu_state = {
      .channel_states = 0xFF,
      .temp_psu = 25,
      .temp_cell_1 = 25,
      .temp_cell_2 = 25,
      .v_bat_mV = 7200,
  };
  VehicleState_SetPSUState(&test_psu_state);

  BSP_Buzzer_On();

  BSP_LED_2_ON();

  // play the startup tune here

  osDelay(STARTUP_PAUSE_MS);

  next_status_time = osKernelGetTickCount() + STATUS_PERIOD_MS;

  for (;;)
  {
    if (!VehicleState_GetCurrentState(&vehicle_state))
    {
      osDelay(50U);
      continue;
    }

    if (vehicle_state.psu_state_valid && !voltage_played)
    {
      // play voltage morse code here
      PlayBatteryVoltage(vehicle_state.psu_state.v_bat_mV);
      next_status_time = osKernelGetTickCount() + STATUS_PERIOD_MS;
      voltage_played = true;
    }

    if (osKernelGetTickCount() >= next_status_time)
    {
      // play status code here if the current flight state is one that should have the buzzer on.
      BSP_Buzzer_Start(BUZZER_FREQUENCY_HZ);
      osDelay(100U);
      BSP_Buzzer_Stop();

      BSP_LED_1_TOGGLE();
      BSP_LED_2_TOGGLE();

      next_status_time = osKernelGetTickCount() + STATUS_PERIOD_MS;
    }

    osDelay(50U);
  }
}
