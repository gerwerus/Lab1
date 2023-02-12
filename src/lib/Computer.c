#include "lib/Computer.h"

uint8_t Flags;
int memory[MEM_SIZE];

int sc_memoryInit() {
    for (int i = 0; i < MEM_SIZE; i++)
        memory[i] = 0;
    return 0;
}

int sc_memorySet (int address, int value){
    if (address >= MEM_SIZE || address < 0) {
        return 1;
    }
    memory[address] = value;
    return 0;
}

int sc_memoryGet (int address, int *value){
    if (address >= MEM_SIZE || address < 0) {
        return 1;
    }
    *value = memory[address];
    return 0;
}

int sc_memorySave (const char* filename){
    FILE* f = fopen(filename, "w");
    if (!f) return 1;
    fwrite(memory, sizeof(int), MEM_SIZE, f);
    fclose(f);
    return 0;
}

int sc_memoryLoad (const char* filename){
    FILE* f = fopen(filename, "r");
    if (!f) return 1;
    fread(memory, sizeof(int), MEM_SIZE, f);
    fclose(f);
    return 0;
}

int sc_regInit(){
	Flags = 0b00000000;
	return 0;
}
int sc_regSet (int reg, int value){
    if (value < 0 || value > 1) return 1;
    if (reg == OVERFLOW) {
        Flags |= (OVERFLOW_MASK & (value * 0x7f));
    }
    if (reg == DIVISION_ERR_BY_ZERO) {
        Flags |= (ZERO_MASK & (value * 0x7f));
    }
    if (reg == OUT_OF_MEMORY) {
        Flags |= (OUT_OF_MEMORY_MASK & (value * 0x7f));
    }
    if (reg == IGNORING_CLOCK_PULSES) {
        Flags |= (IGNORING_CLOCK_PULSES_MASK & (value * 0x7f));
    }
    if (reg == INCORRECT_COMMAND) {
        Flags |= (INCORRECT_COMMAND_MASK & (value * 0x7f));
    }
    else {
        return 2;
    }
    return 0;
}

int sc_regGet (int reg, int *value){
    if (reg == OVERFLOW) {
        *value = (Flags & OVERFLOW_MASK) >> OVERFLOW;
    }
    if (reg == DIVISION_ERR_BY_ZERO) {
        *value = (Flags & ZERO_MASK) >> DIVISION_ERR_BY_ZERO;
    }
    if (reg == OUT_OF_MEMORY) {
        *value = (Flags & OUT_OF_MEMORY_MASK) >> OUT_OF_MEMORY;
    }
    if (reg == IGNORING_CLOCK_PULSES) {
        *value = (Flags & IGNORING_CLOCK_PULSES_MASK) >> IGNORING_CLOCK_PULSES;
    }
    if (reg == INCORRECT_COMMAND) {
        *value = (Flags & INCORRECT_COMMAND_MASK) >> INCORRECT_COMMAND;
    }
    else {
        return 1;
    }
    return 0;
}

const int correct_ops[] = { 0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32, 0x33, 0x40,
						   0x41, 0x42, 0x43, 0x58 };
const int ops_num = 13;

int int_cmp(const void* a, const void* b)
{
    if (*(int*)a < *(int*)b)
        return -1;
    else
        if (*(int*)a > *(int*)b)
            return 1;
        else
            return 0;
}


int sc_commandEncode(int command, int operand, int* value)
{
	void* command_ptr;

	command_ptr = bsearch(&command, correct_ops, ops_num, sizeof(int), int_cmp);
	if (command_ptr != NULL)
	{
		*value = (command << 7) | operand;
		return 0;
	}
	else
		return 1;
}



int sc_commandDecode(int value, int* command, int* operand)
{
	void* correct_command;
	int attribute;
	int tmp_command, tmp_operand;

	attribute = (value >> 14) & 1;
	if (attribute == 0)
	{
		tmp_command = (value >> 7) & 0x7F;
		tmp_operand = value & 0x7F;
		correct_command = bsearch(&tmp_command, correct_ops, ops_num, sizeof(int), int_cmp);
		if (correct_command != NULL)
		{
			*command = tmp_command;
			*operand = tmp_operand;
		}
		else
			return 1;
	}
	else
		return 2;
	return 0;
}
