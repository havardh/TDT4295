Software Package
================

Prerequisites
-------------

To build the project the gcc-arm-none-eabi toolchain is needed.

To flash the microcontroller the eACommander tool provided by Energy Micro is needed.It's included in the Simplicity Studio install: http://www.energymicro.com/tools/simplicity-studio
Linux and Mac version is available here: http://forum.energymicro.com/topic/990-simplicity-studio-120-energyaware-tools-osx-linux/

CppUTest must be built.
Run the script in sw/scripts/cpputest to do so.

The rest of the libraries are included in the repository.

Testing
-------

Run `make` from the sw/tests directory.

Building
--------

Run `make` from the sw directory. This should create the file main.bin in the exe folder.

Deploying
------

* Open the eACommander application. 
* Connect to the board. 
* Enter \<root\>/sw/exe/main.bin in the Binary File field on the flash tab.
* Click Flash EFM32.

Folder layout
-------------

<pre>
|---Makefile  # makefile for bin to flash with
|---main.c    # main function for bin file
|---controllers/
|   |---buttons/
|   |   |---Makefile # makefile for button controller demo
|   |   |---inc/
|   |   |   |---ButtonsController.h
|   |   |---src/
|   |   |   |---ButtonsController.c
|   |   |---demo/
|   |   |   |---main.c # button controller demo
|   |---...
|---drivers/
|   |---buttons/
|   |   |---Makefile # makefile for button driver demo
|   |   |---inc/
|   |   |   |---ButtonsDriver.h
|   |   |---src/
|   |   |   |---ButtonsDriver.c
|   |   |---demo/
|   |   |   |---main.c # button driver demo
|   |---...
|---libs/
|   |---CMSIS/  # ARM Cortex library
|   |---Device/ # Device Specific library from EM (efm32gg990f1024.h, ...)
|   |---emlib/  # Energy Micro library
|   |---emdrv/  # Energy Micro library
|   |---kits/   # Kits Specific
|   |---math/   # Our own Math lib (software SDFT, etc.)
|---tests/
|   |---AllTests.cpp # testrunner
|   |---Makefile     # makefile for all tests
|   |---controllers/ 
|   |   |---buttons/
|   |   |   |---ButtonsControllerTest.cpp
|   |---drivers/
|   |   |---buttons/
|   |   |   |---ButtonsDriverTest.cpp
|   |---libs/
|   |   |---math/
|   |   |   |---ComplexTest.cpp
</pre>

