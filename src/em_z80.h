#ifndef _INCLUDE_EM_Z80_H
#define _INCLUDE_EM_Z80_H

#define False 0
#define True  1

#define FAIL_NONE                 0
#define FAIL_ERROR                1
#define FAIL_NOT_IMPLEMENTED      2
#define FAIL_IMPLEMENTATION_ERROR 3

#define CPU_DEFAULT               0
#define CPU_NMOS_ZILOG            1
#define CPU_NMOS_NEC              2
#define CPU_CMOS                  3

// MState/TState definitions

#define C_PREFIX1 0x40000000
#define C_PREFIX2 0x40000000
#define C_PREDIS  0x30000000

#define C_4       0x40000000
#define C_43      0x43000000
#define C_433     0x43300000
#define C_4333    0x43330000
#define C_43333   0x43333000
#define C_434     0x43400000
#define C_43433   0x43433000
#define C_43435   0x43435000
#define C_435     0x43500000
#define C_44      0x44000000
#define C_443     0x44300000
#define C_4433    0x44330000
#define C_443333  0x44333300
#define C_44335   0x44335000
#define C_44343   0x44343000
#define C_443435  0x44343500
#define C_4435    0x44350000
#define C_44353   0x44353000
#define C_44354   0x44354000
#define C_443543  0x44354300
#define C_44355   0x44355000
#define C_444     0x44400000
#define C_4443    0x44430000
#define C_45      0x45000000
#define C_4533    0x45330000
#define C_4543    0x45430000
#define C_45435   0x45435000
#define C_46      0x46000000
#define C_533     0x53300000
#define C_535     0x53500000
#define C_6       0x60000000

typedef enum {
   TYPE_0,   // no params
   TYPE_1,   // {arg_reg}
   TYPE_2,   // {arg_reg} {arg_reg}
   TYPE_3,   // {arg_imm} {arg_reg}
   TYPE_4,   // {arg_reg} {arg_imm}
   TYPE_5,   // {arg_reg} {arg_dis}
   TYPE_6,   // {arg_reg} {arg_dis} {arg_imm}
   TYPE_7,   // {jump}
   TYPE_8    // {arg_dis}
} FormatType;

typedef struct Instr {
   int want_dis;
   int want_imm;
   int want_read;
   int want_write;
   int conditional;
   int t_states;
   FormatType format;
   const char *mnemonic;
   void (*emulate)(struct Instr *);
} InstrType;

extern InstrType z80_interrupt_int;
extern InstrType z80_interrupt_nmi;

InstrType *table_by_prefix(int prefix);
char *reg_by_prefix(int prefix);
char *z80_get_state(int verbosity);
void z80_init(int cpu_type);
void z80_reset();
int z80_get_pc();
void z80_increment_r();
int z80_halted();

#endif
