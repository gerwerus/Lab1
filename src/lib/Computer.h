#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MEM_SIZE 100
#define OVERFLOW 0
#define DIVISION_ERR_BY_ZERO 1
#define OUT_OF_MEMORY 2 
#define IGNORING_CLOCK_PULSES 3 
#define INCORRECT_COMMAND 4

#define OVERFLOW_MASK 0b00000001
#define ZERO_MASK 0b00000010
#define OUT_OF_MEMORY_MASK 0b00000100
#define IGNORING_CLOCK_PULSES_MASK 0b00001000
#define INCORRECT_COMMAND_MASK 0b00010000

int sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int* value);
int sc_memorySave (const char* filename); 
int sc_memoryLoad (const char* filename);
int sc_regInit();
int sc_regSet(int reg, int value);
int sc_regGet(int reg, int* value);
int sc_commandEncode(int command, int operand, int* value);
int sc_commandDecode(int value, int* command, int* operand);

