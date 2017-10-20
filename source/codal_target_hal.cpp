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

#include "codal_target_hal.h"
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include "ATMegaSerial.h"

#include "CodalCompat.h"
#include "ATMegaSerial.h"

void target_enable_irq()
{
    sei();
}

void target_disable_irq()
{
    cli();
}

void target_wait_for_event()
{
    target_disable_irq();
    sleep_enable();
    target_enable_irq();
    sleep_cpu();
    sleep_disable();
}

void target_wait(uint32_t milliseconds)
{
    while(milliseconds-- > 0)
        _delay_ms(1);
}

void target_reset()
{
    target_disable_irq();
    wdt_enable(WDTO_15MS);
    while (1) {}
}

void target_panic(int statusCode)
{
    target_disable_irq();
    // the methods we use are actually more or less static
    codal::ATMegaSerial *serial = nullptr;
    for (int i = 0; i < 10; ++i) {
        serial->send(" !!! ");
        serial->send(statusCode);
    }
    while (1) {}
}

struct PROCESSOR_TCB
{
	uint8_t STACK_BASE_LO;
	uint8_t STACK_BASE_HI;

	uint8_t R0;
	uint8_t R1;
	uint8_t R2;
	uint8_t R3;
	uint8_t R4;
	uint8_t R5;
	uint8_t R6;
	uint8_t R7;
	uint8_t R8;
	uint8_t R9;
	uint8_t R10;
	uint8_t R11;
	uint8_t R12;
	uint8_t R13;
	uint8_t R14;
	uint8_t R15;
	uint8_t R16;
	uint8_t R17;
	uint8_t R18;
	uint8_t R19;
	uint8_t R20;
	uint8_t R21;
	uint8_t R22;
	uint8_t R23;
	uint8_t R24;
	uint8_t R25;
	uint8_t R28;
	uint8_t R29;

	uint8_t SPLO;
	uint8_t SPHI;
	uint16_t LR;
};

PROCESSOR_WORD_TYPE fiber_initial_stack_base()
{
    return RAMEND;
}

void* tcb_allocate()
{
    return (void *)malloc(sizeof(PROCESSOR_TCB));
}

/**
  * Configures the link register of the given tcb to have the value function.
  *
  * @param tcb The tcb to modify
  * @param function the function the link register should point to.
  */
void tcb_configure_lr(void* tcb, PROCESSOR_WORD_TYPE function)
{
    PROCESSOR_TCB* tcbPointer = (PROCESSOR_TCB *)tcb;
    tcbPointer->LR = function;
}

/**
  * Configures the link register of the given tcb to have the value function.
  *
  * @param tcb The tcb to modify
  * @param function the function the link register should point to.
  */
void tcb_configure_sp(void* tcb, PROCESSOR_WORD_TYPE sp)
{
    PROCESSOR_TCB* tcbPointer = (PROCESSOR_TCB *)tcb;
    tcbPointer->SPHI = codal::high(sp);
    tcbPointer->SPLO = codal::low(sp);
}

void tcb_configure_stack_base(void* tcb, PROCESSOR_WORD_TYPE stack_base)
{
    PROCESSOR_TCB* tcbPointer = (PROCESSOR_TCB *)tcb;
    tcbPointer->STACK_BASE_HI = codal::high(stack_base);
    tcbPointer->STACK_BASE_LO = codal::low(stack_base);
}

PROCESSOR_WORD_TYPE tcb_get_stack_base(void* tcb)
{
    PROCESSOR_TCB* tcbPointer = (PROCESSOR_TCB *)tcb;
    return tcbPointer->STACK_BASE_HI << 8 | tcbPointer->STACK_BASE_LO;
}

PROCESSOR_WORD_TYPE get_current_sp()
{
    return (SPH << 8 | SPL) + 2;
}

PROCESSOR_WORD_TYPE tcb_get_sp(void* tcb)
{
    PROCESSOR_TCB* tcbPointer = (PROCESSOR_TCB *)tcb;
    return tcbPointer->SPHI << 8 | tcbPointer->SPLO;
}

void tcb_configure_args(void* tcb, PROCESSOR_WORD_TYPE ep, PROCESSOR_WORD_TYPE cp, PROCESSOR_WORD_TYPE pm)
{
    PROCESSOR_TCB* tcbPointer = (PROCESSOR_TCB *)tcb;
    // arg 3
    tcbPointer->R20 = codal::low(pm);
    tcbPointer->R21 = codal::high(pm);
    // arg 2
    tcbPointer->R22 = codal::low(cp);
    tcbPointer->R23 = codal::high(cp);
    // arg 1
    tcbPointer->R24 = codal::low(ep);
    tcbPointer->R25 = codal::high(ep);
}


extern "C" void __cxa_pure_virtual()
{
    target_panic(1000);
}

extern PROCESSOR_WORD_TYPE __heap_start;
PROCESSOR_WORD_TYPE codal_heap_start = (PROCESSOR_WORD_TYPE)&__heap_start - ((PROCESSOR_WORD_TYPE)&__heap_start % (PROCESSOR_WORD_TYPE)sizeof(PROCESSOR_WORD_TYPE)) + (PROCESSOR_WORD_TYPE)sizeof(PROCESSOR_WORD_TYPE);

// define new and delete.
extern "C" void* operator new(size_t objsize) {
    return malloc(objsize);
}

extern "C" void operator delete(void* obj) {
    free(obj);
}
