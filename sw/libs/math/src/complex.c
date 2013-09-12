#include "complex.h"

complex addi(complex lhs, int8_t rhs)
{
  lhs.real += rhs;
  return lhs;
}

complex addc(complex lhs, complex rhs)
{
  complex res;

  res.real = lhs.real + rhs.real;  
  res.img = lhs.img + rhs.img;

  return res;
}

complex mul(complex lhs, complex rhs)
{
  complex res;

  res.real = lhs.real * rhs.real - lhs.img * rhs.img;
  res.img = lhs.img * rhs.real + lhs.real * rhs.img;

  return res;
}
