#include <stdint.h>
#include <stdbool.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "bsp.h"
#include "bsp_trace.h"

volatile uint32_t msTicks;

void Delay( uint32_t ticks );

void SysTick_Handler( void ) {

    msTicks++;

}

void Delay( uint32_t ticks ) {

    uint32_t curTicks;

    curTicks = msTicks;
    while ((msTicks - curTicks) < ticks) ;

}

int main( void ) {

    CHIP_Init();

    if (SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000)) while(1) ;

    BSP_LedsInit();
    BSP_LedSet(0);

    while (1) {
        BSP_LedToggle(0);
        Delay(500);
        BSP_LedToggle(1);
        Delay(500);
    }

}
