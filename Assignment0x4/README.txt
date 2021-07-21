part0x01

ia32- 
I used the provided IS_DECODE function to figure out the instruction types and resulting instruction length for each instruction in the fib function.
The length was then used to increment to the next instruction in the fib function.
I printed the opcodes and lengths of each instruction at every address using this process.

arm-
This was simpler because every instruction was of length four.
I extracted the opcodes (bits 20 - 27) and printed them with the lenght of the instruction.


part0x02

ia32- 
I used the IS_DECODE function to figure out whether an instruction was a control flow operation or not.
If it was, I jumped to my patch function which then would patch the instruction with the correct callout.
In my callout functions I unpatched the code
	each callout function emulated what the fib function would actually be doing if the code had gone to it
	after patching, the code would check if there is a valid next instruction and either end execution or continue patching

arm-
I found out whether the opcode of the instruction signalled that it was a control flow instruction
If it was, I jumped to my patch function which then would patch the instruction with the correct callout.
	in the case of bx, I had to jump using b instead of bl, or the registers would be overwritten.
In my callout functions I unpatched the code
	each callout function emulated what the fib function would actually be doing if the code had gone to it
	after patching, the code would check if there is a valid next instruction and either end execution or continue patching



part0x03

ia-32-
I counted the number of instructions in each basic block using the patchNextCFlow function
I created a data structure that had variables that could store addresses and ints
I then stored the starting address and number of instructions for each basic block in the data structure and printed them

arm-
I counted the number of instructions in each basic block using the patchNextCFlow function
I created a data structure that had variables that could store addresses and ints
I then stored the starting address and number of instructions for each basic block in the data structure and printed them