#---------
#
# CppUTest Examples Makefile
#
#----------

#Set this to @ to keep the makefile quiet
ifndef SILENCE
	SILENCE = @
endif

#--- Inputs ----#
COMPONENT_NAME = all
CPPUTEST_HOME = /Users/havard/Documents/programmering/c/libs/CppUTestOLD

CPPUTEST_USE_EXTENSIONS = Y
CPP_PLATFORM = GCC
CPPUTEST_CPPFLAGS = -x c++
CFLAGS += --std=c99

SRC_DIRS = \
  .\
  ../controllers/**/src\
  ../drivers/**/src\
  ../libs/math/src\
  src\


TEST_SRC_DIRS = \
	./**/**\

INCLUDE_DIRS =\
  ../**/**/inc\
  $(CPPUTEST_HOME)/include\

include $(CPPUTEST_HOME)/build/MakefileWorker.mk
