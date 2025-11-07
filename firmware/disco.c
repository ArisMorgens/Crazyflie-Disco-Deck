#define DEBUG_MODULE "DiscoDeck"
#include "debug.h"

#include "deck.h"

#include "stm32fxxx.h"
#include "config.h"
#include "console.h"
#include "uart1.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "log.h"
#include "param.h"

#define ONE_SEC 1000

static uint16_t disco_spin = 0;

static void DiscoInit()
{
  DEBUG_PRINT("Initialize the Disco deck!\n");
  pinMode(DECK_GPIO_IO4, OUTPUT); // Set pins to output

  digitalWrite(DECK_GPIO_IO4, LOW);
  vTaskDelay(ONE_SEC);
}

static bool DiscoTest()
{
  DEBUG_PRINT("Disco deck passed the test!\n");
  return true;
}

static void updateDeck(void)
{
  if (disco_spin == 1) {
    digitalWrite(DECK_GPIO_IO4, HIGH);
  } else {
    digitalWrite(DECK_GPIO_IO4, LOW);
  }
}

static const DeckDriver DiscoDriver = {
  .name = "Disco",

  .usedGpio = DECK_USING_IO_4,

  .init = DiscoInit,
  .test = DiscoTest,

};


DECK_DRIVER(DiscoDriver);

PARAM_GROUP_START(colorLedDisco)
PARAM_ADD_WITH_CALLBACK(PARAM_UINT16, disco_spin, &disco_spin, &updateDeck)
PARAM_GROUP_STOP(colorLedDisco)