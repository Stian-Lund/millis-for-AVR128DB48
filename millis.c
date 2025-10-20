/*
 * File:   millis.c
 * Author: Stian Østhus Lund
 *
 * Created on October 14, 2025, 9:36 PM
 */

#include "millis.h"
#include <util/atomic.h>

#ifndef F_CPU
#warning "F_CPU not defined! Assuming 4MHz"
#define F_CPU 4000000UL
#endif

#if (F_CPU / 1000UL) > 65535UL
#error "F_CPU too high for DIV1 prescaler, use a higher prescaler"
#endif

volatile uint32_t milliseconds = 0;

void millis_init(void)
{
    // Stop timer
    TCA0.SINGLE.CTRLA = 0;

    // Configure TCA0 for 1ms overflow with F_CPU clock
    TCA0.SINGLE.PER = (F_CPU / 1000UL) - 1; // 1000Hz
    TCA0.SINGLE.CNT = 0;                    // Reset count

    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm; // Clear overflow interrupt flag
    TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;  // Enable overflow interrupt

    TCA0.SINGLE.CTRLA = TCA_SINGLE_ENABLE_bm | TCA_SINGLE_CLKSEL_DIV1_gc; // Enable timer & set CLKSEL to DIV1
}

uint32_t millis(void)
{
    uint32_t ms;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        ms = milliseconds;
    }
    return ms;
}

ISR(TCA0_OVF_vect)
{
    milliseconds++;
    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm; // Clear interrupt flag

}

