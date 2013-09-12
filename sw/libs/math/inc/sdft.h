#ifndef SDFT_H
#define SDFT_H

#include "complex.h"
#include "circular_buffer.h"
#include <stdint.h>

void sdft(uint8_t new_sample, complex *freq, complex *coeffs);
uint8_t isdft(complex *freq, complex *coeffs);

#endif // SDFT_H
