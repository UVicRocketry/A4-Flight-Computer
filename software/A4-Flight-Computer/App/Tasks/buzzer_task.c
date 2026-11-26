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

static void PlayMorseSymbol(char symbol);
static void PlayMorseCode(const char *code);
static void PlayBatteryVoltage(uint16_t voltage_mV);
static void PlayMML(const char *mml);

// Startup tune defined as a MML (Music Macro Language) string.
char startup_mml[] = "t200o4 l4e  aa>c+c+  <a2ee  e.l8ebag+f+  e2.l4e  aa>c+c+  <a2ea  g+f+8g+8ad+  e2.r"; // Samsung washer
// char startup_mml[] = "t104o5  l16def+4a4f+8ef+e  d2&d8f+4a8  b2>d8c+4<a8  f+4.l16gf+e4.de  f+4a4f+e8.d8.e  d2&d8f+4a8  b2a4f+4  f+2e2  ded1"; // C.H.
//char startup_mml[] = "t160v120a8a8ab+b2>c2d2<a1.ra8a8ab+l2b>ef+a1.r4l8<eeaaa4b2>c4ccl2d<a1.>bgf+l4f+gg2e1.r<a8a8ab+b2>e2f+2d1.r<a8a8ab+l2b>ef+a1.<bl1g&g4b8>c8d<a>ec<b2gf+4g4g&g2."; // RoR
// Smash mouth
//char startup_mml[] = "t120v120l8o4g4>d<bb4agg>c4<bbaagrg>d<bbaagge&e2rggg>d<bbaagg>cc<bbaagg>d4<bba4gga4e4.rgg.d16ggg16g16g16g16ggg.g16gg16g16gg16g16g16g16gb16g.b16b16>dc<b16a16aaa.g16bggd16d16gge16d.b16>d<b16>e<b16>d<b16>e<b16>dc<baag16ag4&g16d16g16g16gg16g16gg4rr16d16b16g16gg16g16ee4r4bg4g16e16gg4g16e16gg4g4b4.bg4g16e16gg4g16e16gg4g4b4.b4>d4c<baag2ggagba4.ag4a4be2";
// He's a pirate
//char startup_mml[] = "t200d4d8d4d8d4d8d8d8d8d4d8d4d8d4d8d8d8d8d4d8d4d8d4d8d8<a8>c8<f4f4f8a8a+4a+4a+8>d8<a4a4a8g8a8a4.a8>c8<f4f4a+8a+8a4a4>c8c8<a4a4a8g8f2a8>c8<f4f4a8a8a+4a+4>d8d8d4d4f8e8f8d4.d8e8<a+4a+4a+4>f8d4.d8f8<a4a4>d8<b8a2>a8>c8<f4f4f8a8a+4a+4a+8>d8<a4a4a8g8a8a4.a8>c8<f4f4a+8a+8a4a4>c8c8c4c4<a8>c8<f2a8>c8<f4f4a8a8a+4a+4>d8d8d4d4f8e8f8d4.d8e8<a+4a+4a+4>f8d4.d8f8<a4a4>d8c+8<a4>";

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

  osDelay(STARTUP_PAUSE_MS);

  // play the startup tune here

  PlayMML(startup_mml);
  BSP_Buzzer_Stop();

  osDelay(STATUS_PERIOD_MS);

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

// --- MML (Music Macro Language) Parser and Player ---

static void PlayMML(const char *mml)
{
  // need to implement a iterator/parser to play MML
  // parsing: case insensitive.
  // track current address.
  // skip whitespace.
  // Looking for a token:
  // T: set tempo. get next character until it's not a number anymore.
  // O: set octave. get next character until not a number anymore (should only be 1 digit).
  // L: set default tone length. get next character until not a number anymore.
  // >: Increment octave by 1.
  // <: Decrement octave by 1.
  // ^: Legato/tie. Don't stop between notes.
  // P/R: Pause. check for a number after it, if not, use default length. If there is a number, use that length.
  //      Check for a '.' after it, if so, increment the length by 1.5x.
  // A-G: Stop previous note and play a new note. Check for a # or + after it, if so, increment the note by 1 semitone. Check for a - after it, if so, decrement the note by 1 semitone.
  //      Check for a number after it, if not, use default length. If there is a number, use that length.

  char *start = (char *)mml;

  uint8_t octave = 4;          // default octave
  uint16_t default_length = 4; // default length (quarter note)
  uint16_t tempo = 120;        // default tempo (beats per minute)
  bool legato = false;         // legato/tie flag

  uint16_t note_length = default_length;
  uint16_t note_frequency_hz = 0;
  uint16_t note_duration_ms = 0;

  while (*mml != '\0')
  {
    // skip whitespace
    if (*mml == ' ' || *mml == '\t' || *mml == '\n' || *mml == '\r')
    {
      mml++;
      continue;
    }

    note_length = default_length;

    switch (*mml)
    {
    case 'T':
    case 't':
      // set tempo
      mml++;
      // parse number
      uint16_t new_tempo = 0;
      while (*mml >= '0' && *mml <= '9')
      {
        new_tempo = new_tempo * 10 + (*mml - '0');
        mml++;
      }

      if (new_tempo > 0)
      {
        tempo = new_tempo;
      }
      break;
    case 'O':
    case 'o':
      // set octave
      mml++;
      if (*mml >= '0' && *mml <= '9')
      {
        octave = *mml - '0';
        mml++;
      }
      break;
    case 'L':
    case 'l':
      // set default length
      mml++;
      uint16_t new_length = 0;
      while (*mml >= '0' && *mml <= '9')
      {
        new_length = new_length * 10 + (*mml - '0');
        mml++;
      }

      if (new_length > 0)
      {
        default_length = new_length;
      }
      break;
    case '>':
      // increment octave
      if (octave < 8)
      {
        octave++;
      }
      mml++;
      break;
    case '<':
      // decrement octave
      if (octave > 0)
      {
        octave--;
      }
      mml++;
      break;
    case '^':
    case '&':
      // legato/tie
      legato = true;
      mml++;
      break;
    case 'P':
    case 'p':
    case 'R':
    case 'r':
      // pause
      mml++;
      if (*mml >= '0' && *mml <= '9')
      {
        note_length = 0;
        while (*mml >= '0' && *mml <= '9')
        {
          note_length = note_length * 10 + (*mml - '0');
          mml++;
        }
      }

      // check for dot
      if (*mml == '.')
      {
        note_length = (note_length * 3) / 2; // increase by 1.5x
        mml++;
      }

      if (note_length == 0)
      {
        note_length = default_length;
      }
      note_duration_ms = (60000U / tempo) * (4U / note_length);

      BSP_Buzzer_Stop();
      osDelay(note_duration_ms);
      break;
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
      // play note
      char note_letter = *mml;
      int16_t accidental = 0;
      int16_t pitch_class;

      mml++;

      if (*mml == '#' || *mml == '+')
      {
        accidental = 1;
        mml++;
      }
      else if (*mml == '-')
      {
        accidental = -1;
        mml++;
      }

      switch (note_letter)
      {
      case 'C':
      case 'c':
        pitch_class = 0;
        break;
      case 'D':
      case 'd':
        pitch_class = 2;
        break;
      case 'E':
      case 'e':
        pitch_class = 4;
        break;
      case 'F':
      case 'f':
        pitch_class = 5;
        break;
      case 'G':
      case 'g':
        pitch_class = 7;
        break;
      case 'A':
      case 'a':
        pitch_class = 9;
        break;
      case 'B':
      case 'b':
        pitch_class = 11;
        break;
      default:
        pitch_class = 0;
        break;
      }

      int16_t semitones_from_c4 = (12 * ((int16_t)octave - 4)) + pitch_class + accidental;
      int16_t octave_offset = semitones_from_c4 / 12;
      int16_t table_index = semitones_from_c4 % 12;

      if (table_index < 0)
      {
        table_index += 12;
        octave_offset--;
      }

      static const uint16_t c4_scale_hz[] = {
          262U, 277U, 294U, 311U, 330U, 349U,
          370U, 392U, 415U, 440U, 466U, 494U};

      note_frequency_hz = c4_scale_hz[table_index];
      if (octave_offset >= 0)
      {
        while (octave_offset-- > 0)
        {
          note_frequency_hz *= 2U;
        }
      }
      else
      {
        while (octave_offset++ < 0)
        {
          note_frequency_hz = (note_frequency_hz + 1U) / 2U;
        }
      }

      if (*mml >= '0' && *mml <= '9')
      {
        note_length = 0;
        while (*mml >= '0' && *mml <= '9')
        {
          note_length = note_length * 10 + (*mml - '0');
          mml++;
        }
      }

      // check for dot
      if (*mml == '.')
      {
        note_length = (note_length * 3) / 2; // increase by 1.5x
        mml++;
      }

      if (note_length == 0)
      {
        note_length = default_length;
      }

      note_duration_ms = (60000U * 4U) / (tempo * note_length);

      if (!legato)
      {
        BSP_Buzzer_Stop();
        osDelay(25U); // short gap between notes
      }

      BSP_Buzzer_Start(note_frequency_hz);

      osDelay(note_duration_ms - 25U); // subtract the gap time from the note duration
      break;
    default:
      // unrecognized character, skip it
      mml++;
      break;
    }

    legato = false; // reset legato flag after each note or pause
  }
}
