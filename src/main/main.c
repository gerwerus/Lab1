#include "lib/Computer.h"

//using namespace std;

int main() {
	int value;

    sc_regInit();
    sc_memoryInit();

    sc_memorySet(0, 5);
    sc_memorySet(1, 4);
    sc_memorySet(2, 3);
    for (int i = 0; i < 3; i++) {
        sc_memoryGet(i, &value);
        printf("MEMORY[%d] = %d\n", i, value);
    }
    printf("----------------\n");
    sc_memorySave("test.bin");
    
    sc_memorySet(0, 777);
    sc_memoryGet(0, &value);
    printf("SET MEMORY[0] = %d\nLOAD FROM FILE...\n\n", value);

    sc_memoryLoad("test.bin");

    for (int i = 0; i < 3; i++) {
        sc_memoryGet(i, &value);
        printf("MEMORY[%d] = %d\n", i, value);
    }

    printf("----------------\n");
    
    
    sc_regSet(OVERFLOW, 1);
    sc_regSet(DIVISION_ERR_BY_ZERO, 0);
    sc_regSet(OUT_OF_MEMORY, 1);
    sc_regSet(IGNORING_CLOCK_PULSES, 0);
    sc_regSet(INCORRECT_COMMAND, 1);

    sc_regGet(OVERFLOW, &value);
    printf("OVERFLOW %d\n", value);
    sc_regGet(DIVISION_ERR_BY_ZERO, &value);
    printf("DIVISION_ERR_BY_ZERO %d\n", value);
    sc_regGet(OUT_OF_MEMORY, &value);
    printf("OUT_OF_MEMORY %d\n", value);
    sc_regGet(IGNORING_CLOCK_PULSES, &value);
    printf("IGNORING_CLOCK_PULSES %d\n", value);
    sc_regGet(INCORRECT_COMMAND, &value);
    printf("INCORRECT_COMMAND %d\n", value);

    printf("----------------\n");
    
    int f = 0, com = 0, op = 0;
    sc_commandEncode(0x33, 0x59, &f);
    sc_commandDecode(f, &com, &op);
    printf("com = 0x%.2X; op = 0x%.2X ", com, op);
}
