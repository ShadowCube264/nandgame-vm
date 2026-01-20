#include <stdint.h>
#include <stdio.h>

// Registers
uint16_t A = 0;
uint16_t D = 0;
uint16_t PC = 0;

// Memory
int16_t MEMORY[UINT16_MAX];

// ROM (for instructions - separate from memory)
uint16_t ROM[UINT16_MAX] = {};

// Checks if a specific bit is present
char bit_check(uint16_t val, char bit) {
    return (val & (1 << bit)) > 0;
}

int main() {
    while (PC < UINT16_MAX) {
        
        uint16_t instruction = ROM[PC];
        if (instruction == 0) { break; }
        
        // ALU instruction
        if (bit_check(instruction, 15)) {
            // inputs taken from registers and/or memory
            int16_t x = D;
            int16_t y;

            if (bit_check(instruction, 12)) {
                y = MEMORY[A];
            }
            else {
                y = A;
            }

            // Flag to swap inputs
            if (bit_check(instruction, 6)) {
                uint16_t tmp = x;
                x = y;
                y = tmp;
            }

            // Flag to zero X
            if (bit_check(instruction, 7)) {
                x = 0;
            }

            int16_t output;

            // Arithmetic
            if (bit_check(instruction, 10)) {

                // X +- 1
                if (bit_check(instruction, 8)) {
                    y = 1;
                }

                if (bit_check(instruction, 9)) {
                    output = x - y;
                }
                else {
                    output = x + y;
                }
            }
            // Logic
            else {
                if (bit_check(instruction, 9)) {
                    if (bit_check(instruction, 8)) {
                        output = ~x;
                    }
                    else {
                        output = x ^ y;
                    }
                }
                else {
                    if (bit_check(instruction, 8)) {
                        output = x | y;
                    }
                    else {
                        output = x & y;
                    }
                }
            }
        
            // Assigning outputs

            // For some reason, *A takes precedence in the site's implementation
            if (bit_check(instruction, 3)) {
                MEMORY[A] = output;
            }
            if (bit_check(instruction, 4)) {
                D = output;
            }
            if (bit_check(instruction, 5)) {
                A = output;
            }

            // Check jump conditions
            if ((bit_check(instruction, 0) && output > 0) || (bit_check(instruction, 1) && output == 0) || (bit_check(instruction, 2) && output < 0)) {
                PC = A;
            }
            else {
                PC++;
            }
        }
        // Data instruction
        else {
            A = instruction;
            PC++;
        }
    }
    printf("D: %d\nA: %d\n", D, A);
}