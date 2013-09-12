#include <stdint.h>
#include <stdio.h>
#include "complex.h"
#include "circular_buffer.h"
#include "sdft.h"

extern complex coeffs[N];

int main() 
{
  const int N_SAMPLES = 32;

  uint8_t samples[] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26 ,27 ,28 ,29, 30, 31
  };

  complex freq[] = { {0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0} };

  for (int i=0; i<N_SAMPLES; i++) {
    sdft(samples[i], freq, coeffs);

    uint8_t out = isdft(freq, coeffs);
    printf("%d \n", out);
  }
}
