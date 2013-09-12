#include "sdft.h"

complex coeffs[N] = {
  { 1.0f,                0.0f },
  { 0.923879532511f,     0.382683432365f },
  { 0.707106781187f,     0.707106781187f },
  { 0.382683432365f,     0.923879532511f },
  { 6.12323399574e-17f,  1.0f },
  { -0.382683432365f,    0.923879532511f },
  { -0.707106781187f,    0.707106781187f },
  { -0.923879532511f,    0.382683432365f },
  { -1.0f,               1.22464679915e-16f },
  { -0.923879532511f,    -0.382683432365f },
  { -0.707106781187f,    -0.707106781187f },
  { -0.382683432365f,    -0.923879532511f },
  { -1.83697019872e-16f, -1.0f },
  { 0.382683432365f,     -0.923879532511f },
  { 0.707106781187f,     -0.707106781187f },
  { 0.923879532511f,     -0.382683432365f }
};

/* 
 * Updates the fourier transform of a sample window of N samples.
 * Uses a sample cache to update the frequencies.
 */
void sdft(uint8_t new_sample, complex *freq, complex *coefficients) 
{
  uint8_t old = get_old_sample();
  insert_sample(new_sample);

  int8_t delta = (int8_t)(new_sample - old);
  for (uint8_t i=0; i<N; i++) {
    freq[i] = mul(addi(freq[i], delta), coefficients[i]);
  }

}

/* 
 * Extracts a sample from the frequency domain
 */
uint8_t isdft(complex *freq, complex *coefficients)
{
  complex sum = {0,0};
  
  for (int i=0; i<N; i++) {
    sum = addc(mul(freq[i], coefficients[i]), sum);
  }

  return uint8_t(sum.real / (float)N);
}
