/**
 * @file storage_task.c
 * @brief Storage task implementation.
 * @details This file contains the implementation of the storage task.
 */

#include <stdbool.h>
#include "storage_task.h"
#include "app_freertos.h"
#include "vehicle_state.h"
#include "a4_flightcomputer_bsp.h"

/**
 * @brief Function implementing the storageTask thread.
 * @param argument: Not used
 * @retval None
 */
void StartStorageTask(void *argument)
{
  bool sd_card_intialized = false;

  /* Infinite loop */
  for (;;)
  {
    // always check to initialize the SD card, in case it was removed and reinserted.
    if (!sd_card_intialized)
    {
      if (BSP_SD_Init() != 0)
      {
        // SD card initialization failed, try again in the next loop iteration.
        // set flag in vehicle state to indicate SD card error.
        VehicleState_SetSelfTestBit(SELF_TEST_ERROR_SD_CARD);
        osDelay(1000U); // wait 1 second before trying again
        continue;
      }
      else
      {
        sd_card_intialized = true;
        // clear SD card error flag in vehicle state.
        VehicleState_ClearSelfTestBit(SELF_TEST_ERROR_SD_CARD);
      }
    }

    // File system initialization and mounting should be done here, after the SD card is initialized.

    // create a mission directory and blank log files.

    // SD card is initialized, this is the actual storage task loop. Should only breaks if there is a problem with the SD card (i.e. removed).

    for (;;)
    {
      // wait for pending data to appear in the storage queue, then write it to the SD card.

      // check if the SD card is still present and initialized. If not, break out of this loop to try to reinitialize the SD card,
      // and set the SD card error flag in the vehicle state.
      if (!BSP_SD_Ready())
      {
        VehicleState_SetSelfTestBit(SELF_TEST_ERROR_SD_CARD);
        sd_card_intialized = false;
        break;
      }

      osDelay(100U);
    }
    osDelay(1U);
  }
}
