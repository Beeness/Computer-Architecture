#include "cpu.h"
#include <stdlib.h>
#include <stdio.h>

//make helper function to make sure address is in range
unsigned char cpu_ram_read(struct cpu *cpu, unsigned char address)
{
  return cpu->ram[address];
}

void cpu_ram_write(struct cpu *cpu, unsigned char address, unsigned char value)
{
  cpu->ram[address] = value;
}

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu, char *filename)
{

  char line[1024];
  int address = 0;
  // printf("%s\n", filename);
  FILE *fp = fopen(filename, "r");

  while(fgets(line, sizeof line, fp) != NULL) {
    char *endchar;
    unsigned char v = strtoul(line, &endchar, 2);

    if (line == endchar) {
      continue;
    }

    cpu_ram_write(cpu, address++, v);

    // printf("%u\n", v); remove?
  }


  // const int DATA_LEN = 6; remove all?
  // char data[DATA_LEN] = {

  //   // From print8.ls8
  //   0b10000010, // LDI R0,8
  //   0b00000000,
  //   0b00001000,
  //   0b01000111, // PRN R0
  //   0b00000000,
  //   0b00000001  // HLT
  };

  // int address = 0;

  // for (int i = 0; i < DATA_LEN; i++) {
  //   cpu->ram[address++] = data[i];
  // }

  // TODO: Replace this with something less hard-coded
// }

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op) {
    case ALU_MUL:
      cpu->reg[regA] *= cpu->reg[regB];
      break;

    case ALU_ADD:
      break;

    // TODO: implement more ALU ops
  }
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction

//POP
unsigned char sp = cpu->reg[7];

  while (running) {
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    // 2. switch() over it to decide on a course of action.
    // 3. Do whatever the instruction should do according to the spec.
    // 4. Move the PC to the next instruction.
    unsigned char IR = cpu_ram_read(cpu, cpu->pc);

    unsigned char operandA = cpu_ram_read(cpu, cpu->pc + 1);
    unsigned char operandB = cpu_ram_read(cpu, cpu->pc + 2);
    

    printf("TRACE: %02x: %02x\n", cpu->pc, IR);

    switch(IR) {

      case LDI:
        cpu->reg[operandA] = operandB;
        cpu->pc += 3;
        break;

        case PRN:
          printf("%d\n", cpu->reg[operandA]);
          cpu->pc += 2;
          break;

        case HLT:
          running = 0;
          break;

        case MUL:
          alu(cpu, ALU_MUL, operandA, operandB);
          cpu->pc += 3;
          break;

        case POP:
          cpu->reg[operandA] = cpu_ram_read(cpu, sp);
          printf("read: %02x\n", cpu_ram_read(cpu, sp));
          sp++; 
          cpu->pc += 2;
          break;

        case PUSH:
          --sp;
          printf("this is an sp: %d\n", sp);
          printf("this is a val: %02x\n", cpu->reg[operandA]);
          cpu_ram_write(cpu, sp, cpu->reg[operandA]);
          cpu->pc += 2;
          break;


      default:
        printf("unknown instruction at %02x: %02x\n", cpu->pc, IR);
        exit(2);
    }

  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
  cpu->pc = 0;
  cpu->reg[7] = 0xF4;
  // TODO: Zero registers and RAM
}
