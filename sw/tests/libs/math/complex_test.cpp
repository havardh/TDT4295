#include "CppUTest/CommandLineTestRunner.h"
#include "complex.h"

TEST_GROUP(complex) {
	void setup() {}
	void teardown() {}
};

TEST(complex, defineRealAndImaginaryComponents) {
  
  complex c1;

  c1.real = 1.0;
  c1.img = 2.0;

  CHECK_EQUAL(1.0, c1.real);
  CHECK_EQUAL(2.0, c1.img);
  
}
