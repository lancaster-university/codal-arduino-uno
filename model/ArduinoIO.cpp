/*
The MIT License (MIT)

Copyright (c) 2017 Lancaster University.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

/**
  * Represents a collection of all I/O pins on the device.
  */

#include "CodalConfig.h"
#include "ArduinoIO.h"

using namespace codal;

/**
  * Constructor.
  */
ArduinoIO::ArduinoIO() :
    D0 (16, PIN_CAPABILITY_DIGITAL),            
    D1 (17, PIN_CAPABILITY_DIGITAL),            
    D2 (18, PIN_CAPABILITY_DIGITAL),            
    D3 (19, PIN_CAPABILITY_DIGITAL),            
    D4 (20, PIN_CAPABILITY_DIGITAL),            
    D5 (21, PIN_CAPABILITY_DIGITAL),            
    D6 (22, PIN_CAPABILITY_DIGITAL),            
    D7 (23, PIN_CAPABILITY_DIGITAL),            
    D8 (0, PIN_CAPABILITY_DIGITAL),            
    D9 (1, PIN_CAPABILITY_DIGITAL),            
    D10 (2, PIN_CAPABILITY_DIGITAL),            
    D11 (3, PIN_CAPABILITY_DIGITAL),            
    D12 (4, PIN_CAPABILITY_DIGITAL),            
    D13 (5, PIN_CAPABILITY_DIGITAL),            
    A0 (8, PIN_CAPABILITY_AD),            
    A1 (9, PIN_CAPABILITY_AD),            
    A2 (10, PIN_CAPABILITY_AD),            
    A3 (11, PIN_CAPABILITY_AD),            
    A4 (12, PIN_CAPABILITY_AD),            
    A5 (13, PIN_CAPABILITY_AD)
{
}
