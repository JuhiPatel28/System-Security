
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

#include "macros.h"
#include "arm_context.h"
#include "arm_disas.h"

/* addresses of asm callout glue code */
extern void *blCallout;
extern void *bCallout;
extern void *bxCallout;
extern void *bgtCallout;
void *callTarget;

extern int user_prog(int);

void StartProfiling(void *func);

void StopProfiling(void);

void armDecode(uint8_t *ptr, ARMInstr *instr);

void *callTarget;


/*********************************************************************
 *
 *  callout handlers
 *
 *   These get called by asm glue routines.
 *
 *********************************************************************/
void
handleBlCallout(SaveRegs *regs) {
    NOT_IMPLEMENTED();
}

void
handleBCallout(SaveRegs *regs) {
    NOT_IMPLEMENTED();
}

void
handleBxCallout(SaveRegs *regs) {
    NOT_IMPLEMENTED();
}

void
handleBgtCallout(SaveRegs *regs) {
    NOT_IMPLEMENTED();
}

void
handleRetCallout(SaveRegs *regs) {
    NOT_IMPLEMENTED();
}

/*********************************************************************
 *
 *  arm32Decode
 *
 *   Decode an IA32 instruction.
 *
 *********************************************************************/

void
armDecode(uint8_t *ptr, ARMInstr *instr) {
    // TODO: part1
    int32_t inst = *((uint32_t *) ptr);
    instr->opcode = (uint8_t) BITS(inst, 20, 27);
    instr->len = 4;	
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
    	int i = 0;
	while(1){
		ARMInstr *ins = malloc(sizeof(ARMInstr));
		armDecode((func + i), ins);
		printf("Address: %p, Opcode: %x, Length: %d \n", (func+i), ins->opcode, ins->len);				
		uint32_t help = *(uint32_t *)(func + i);
		if(help == 0xe12fff1e){
			break;
		}
		i += ins->len;
	}
}

void
StopProfiling(void) {
    /*
     * TODO: Add your instrumentation code here.
     */
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



