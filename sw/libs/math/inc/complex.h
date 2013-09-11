#ifndef COMPLEX_H
#define COMPLEX_H

#include <stdint.h>

typedef struct {
  float real;
  float img;
} complex;
 
complex addi(complex lhs, int8_t rhs);
complex addc(complex lhs, complex rhs);
complex mul(complex lhs, complex rhs);

#endif // COMPLEX_H
