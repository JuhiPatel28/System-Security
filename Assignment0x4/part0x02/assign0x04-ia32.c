#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

#include "macros.h"
#include "ia32_context.h"
#include "ia32_disas.h"

/* addresses of asm callout glue code */

extern void *jccCallout;
extern void *jmpCallout;
extern void *callCallout;
extern void *retCallout;

extern uint32_t ia32DecodeTable[]; /* see below */

/* instrumentation target */

extern int user_prog(int);

void StartProfiling(void *func);

void StopProfiling(void);

void ia32Decode(uint8_t *ptr, IA32Instr *instr);

void *callTarget;

void patch(uint8_t *addr, IA32Instr instr);
void unpatch();
int patchNextCFlow(uint8_t *);

//globals
uint8_t *patchedAddr;
uint8_t patchedFourBytes[5]; 
int retflag = 0;
int stopflag = 0;
int count = 0;
typedef struct{
	uint8_t *a;
	int i;
} Data;

Data d[20];
/*********************************************************************
 *
 *  callout handlers
 *
 *   These get called by asm glue routines.
 *
 *********************************************************************/

#define ZF 6
#define SF 7
#define OF 11
 
void
handleJccCallout(SaveRegs regs) {
	unpatch();
	printf("help me pls from jcc\n");
	uint8_t *nextInst = 0;
	IA32Instr instr;

	if(!BIT(regs.eflags, ZF) && (BIT(regs.eflags, SF) == BIT(regs.eflags, OF))) {
		nextInst = patchedAddr + 9;
	}
	else
	{
		ia32Decode(patchedAddr, &instr);
		nextInst = patchedAddr + instr.len;
	}

	regs.pc = nextInst;
	StartProfiling(nextInst);
}

void
handleJmpCallout(SaveRegs regs) {
	unpatch();
	printf("help me pls from jmp\n");
	
	uint8_t *nextInst = 0;
	IA32Instr instr;

	nextInst = patchedAddr + 36;
	regs.pc = nextInst;
	StartProfiling(nextInst);
}

void
handleCallCallout(SaveRegs regs) {
	unpatch();
	printf("help me pls from call\n");

	uint8_t *nextInst = 0;
	nextInst = (uint8_t *)user_prog;
	callTarget = nextInst;
	retflag++;
	StartProfiling(nextInst);
}

void
handleRetCallout(SaveRegs regs) {
	unpatch();
	printf("help me pls from ret\n");
	
	if(retflag != 0)
	{	
		retflag--;
		StartProfiling(regs.retPC);
	}
	else
	{
		stopflag = 1;
	}
}



/*********************************************************************
 *
 *  ia32Decode
 *
 *   Decode an IA32 instruction.
 *
 *********************************************************************/

#define IS_DECODE(_a, _b)   (ia32DecodeTable[ (_a) ]& (_b) )

void
ia32Decode(uint8_t *ptr, IA32Instr *instr) {
   // TODO: part1
   instr->len=0;
   int i = 0;

   //parse prefixes
   while (IS_DECODE(ptr[i], IA32_PREFIX)) {
        instr->len += 1;
	i++;
   }

   //processing opcode size 1 byte or 2 byte case
   if (IS_DECODE(ptr[i],IA32_2BYTE)) {
        instr->len += 2;
        instr->opcode = (uint16_t)ptr[i];
	i += 2;
   }
   else {
            instr->len += 1;
            instr->opcode = (uint16_t)ptr[i];
	    i += 1;
   }

   if (IS_DECODE(instr->opcode, IA32_MODRM)) {
        switch (BITS(ptr[i],6,7)){  // Checking MOD value
            case 0b00:  // 0
                instr->len += 1;
	        i++;
		if(BITS(ptr[i],0,2) == 4){
			instr->len += 1;
	       		i++;
		}
		if(BITS(ptr[i],0,2) == 5){
			instr->len += 1;
	       		i++;
		}
		break;
            case 0b01:     // 1
                instr->len += 2;
	        i += 2;
		if(BITS(ptr[i],0,2) == 4){
			instr->len += 1;
	       		i++;
		}
		break;
            case 0b10:     // 2
                instr->len += 6;
	        i += 6;
		break;
            case 0b11:     // 3
		instr->len += 1;
	        i++;
                break;
        }
    } else {
        instr->len += 0;
    }

    if (IS_DECODE(instr->opcode, IA32_IMM8)) {
        instr->len += 1;
    } else if (IS_DECODE(instr->opcode, IA32_IMM32)){
        instr->len += 4;
   }
   return;
}

/*********************************************************************
 *
 *  StartProfiling, StopProfiling
 *
 *   Profiling hooks. This is your place to inspect and modify the profiled
 *   function.
 *
 *********************************************************************/

void
StartProfiling(void *func) {
	d[count].a = (uint8_t *)func;
	d[count].i = patchNextCFlow(func);
	//printf("Starting Address: %p, Instruction Count: %d \n", d[count].a, d[count].i);
	count++;
}

int patchNextCFlow(uint8_t *addr) {
	IA32Instr instr;
	int cnt = 1;

	while (1) {
		if(stopflag == 1) {
			return cnt;
		}

		ia32Decode(addr, &instr);
		printf("Address: %p, Opcode: %x, Length: %d \n", (addr), instr.opcode, instr.len);
		if (IS_DECODE(instr.opcode, IA32_CFLOW)) {
		    break;
		}
		cnt ++;
		addr += instr.len;
   	}

    	patch(addr, instr);
	return cnt;
}

void patch(uint8_t *addr, IA32Instr ins) {
	patchedAddr = addr;
  	memcpy(patchedFourBytes, addr, 5);
  	void *target = NULL;

	if(IS_DECODE(ins.opcode, IA32_JCC)) {
		target = &jccCallout;
	}
	else if(IS_DECODE(ins.opcode, IA32_JMP)) {
		target = &jmpCallout;
	}
	else if(IS_DECODE(ins.opcode, IA32_CALL)) {
		target = &callCallout;
	}
	else if(IS_DECODE(ins.opcode, IA32_RET)) {
		target = &retCallout;
	}
	
	int32_t offset = (uint32_t)(target) - ((uint32_t)(addr) + 5);
	addr[0] = 0xe8;
	*(int32_t *)(addr + 1) = offset;
}

void unpatch() {
	memcpy(patchedAddr, patchedFourBytes, 5);	
}

void
StopProfiling(void) {
    ;
}

int main(int argc, char *argv[]) {
    int value;
    char *end;

    char buf[16];

    if (argc != 1) {
        fprintf(stderr, "usage: %s\n", argv[0]);
        exit(1);
    }

    printf("input number: ");
    scanf("%15s", buf);

    value = strtol(buf, &end, 10);

    if (((errno == ERANGE)
         && ((value == LONG_MAX) || (value == LONG_MIN)))
        || ((errno != 0) && (value == 0))) {
        perror("strtol");
        exit(1);
    }

    if (end == buf) {
        fprintf(stderr, "error: %s is not an integer\n", buf);
        exit(1);
    }

    if (*end != '\0') {
        fprintf(stderr, "error: junk at end of parameter: %s\n", end);
        exit(1);
    }

    StartProfiling(user_prog);

    value = user_prog(value);

    StopProfiling();

    printf("%d\n", value);
    exit(0);
}



