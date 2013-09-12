#include "circular_buffer.h"

uint8_t index = 0;
uint8_t sample_cache[N] = { 0 };

void insert_sample(uint8_t sample) 
{
  sample_cache[index] = sample;
  index = (index+1) % N;
}

uint8_t get_old_sample(void) {
  return sample_cache[index];
}
