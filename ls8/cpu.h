#ifndef _CPU_H_
#define _CPU_H_

// Holds all information about the CPU
struct cpu {
  // TODO
  // PC
  unsigned char PC;
  // registers (array)
  unsigned char reg[8];
  // ram (array)
  unsigned char ram[256];
};

// Instructions

// These use binary literals. If these aren't available with your compiler, hex
// literals should be used.

#define LDI  0b10000010 //represents 8-bit value in binary literal
// TODO: more instructions here. These can be used in cpu_run().
#define ADD  0b10100000
#define SUB  0b10100001
#define MUL  0b10100010
#define DIV  0b10100011
#define MOD  0b10100100
#define INC  0b01100101
#define DEC  0b01100110
#define CMP  0b10100111

// Function declarations
extern void cpu_load(struct cpu *cpu);
extern void cpu_init(struct cpu *cpu);
extern void cpu_run(struct cpu *cpu);

#endif
