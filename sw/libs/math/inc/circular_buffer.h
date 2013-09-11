#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdint.h>

#define N 16

void insert_sample(uint8_t sample);
uint8_t get_old_sample(void);

#endif // CIRCULAR_BUFFER_H
