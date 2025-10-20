/*
 * File:   millis.h
 * Author: Stian Østhus Lund
 *
 * Created on October 14, 2025, 9:36 PM
 */

#ifndef MILLIS_H
#define MILLIS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

    void millis_init(void);
    uint32_t millis(void);

#ifdef __cplusplus
}
#endif

#endif /* MILLIS_H */

