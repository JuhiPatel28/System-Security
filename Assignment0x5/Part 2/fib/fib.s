	.syntax unified
	.eabi_attribute	6, 1
	.eabi_attribute	8, 1
	.eabi_attribute	20, 1
	.eabi_attribute	21, 1
	.eabi_attribute	23, 3
	.eabi_attribute	24, 1
	.eabi_attribute	25, 1
	.file	"fib.bc"
	.section	.debug_info,"",%progbits
.Lsection_info:
	.section	.debug_abbrev,"",%progbits
.Lsection_abbrev:
	.section	.debug_aranges,"",%progbits
	.section	.debug_macinfo,"",%progbits
	.section	.debug_line,"",%progbits
.Lsection_line:
	.section	.debug_loc,"",%progbits
	.section	.debug_pubnames,"",%progbits
	.section	.debug_pubtypes,"",%progbits
	.section	.debug_str,"MS",%progbits,1
.Linfo_string:
	.section	.debug_ranges,"",%progbits
.Ldebug_range:
	.section	.debug_loc,"",%progbits
.Lsection_debug_loc:
	.text
.Ltext_begin:
	.data
	.file	1 "fib.c"
	.text
	.globl	fib
	.align	2
	.type	fib,%function
fib:                                    @ @fib
.Lfunc_begin0:
	.loc	1 20 0                  @ fib.c:20:0
@ BB#0:                                 @ %entry
	push	{r4, r11, lr}
	add	r11, sp, #4
	sub	sp, sp, #8
	str	r0, [sp]
	.loc	1 21 0 prologue_end     @ fib.c:21:0
.Ltmp0:
	cmp	r0, #1
	bgt	.LBB0_2
.Ltmp1:
@ BB#1:                                 @ %if.then
	mov	r0, #1
	b	.LBB0_3
.LBB0_2:                                @ %if.end
	.loc	1 24 0                  @ fib.c:24:0
	ldr	r0, [sp]
	mov	r1, #1
	sub	r0, r0, #1
	bl	fib_logger
	.loc	1 25 0                  @ fib.c:25:0
	ldr	r0, [sp]
	sub	r0, r0, #1
	bl	fib
	mov	r4, r0
	ldr	r0, [sp]
	sub	r0, r0, #2
	bl	fib
	add	r0, r4, r0
.LBB0_3:                                @ %return
	str	r0, [sp, #4]
	.loc	1 26 0                  @ fib.c:26:0
	ldr	r0, [sp, #4]
	sub	sp, r11, #4
	pop	{r4, r11, lr}
	mov	pc, lr
.Ltmp2:
.Ltmp3:
	.size	fib, .Ltmp3-fib
.Lfunc_end0:

	.globl	main
	.align	2
	.type	main,%function
main:                                   @ @main
.Lfunc_begin1:
	.loc	1 29 0                  @ fib.c:29:0
@ BB#0:                                 @ %entry
	push	{r11, lr}
	mov	r11, sp
	sub	sp, sp, #20
	mov	r2, #0
	stmdb	r11, {r0, r2}
	str	r1, [sp, #8]
	.loc	1 33 0 prologue_end     @ fib.c:33:0
.Ltmp4:
	ldr	r0, [r11, #-8]
	cmp	r0, #2
	beq	.LBB1_2
@ BB#1:                                 @ %if.then
	.loc	1 34 0                  @ fib.c:34:0
.Ltmp5:
	ldr	r0, [sp, #8]
	ldr	r1, .LCPI1_5
	ldr	r2, [r0]
	ldr	r0, .LCPI1_1
	ldr	r0, [r0]
	b	.LBB1_11
.Ltmp6:
.LBB1_2:                                @ %if.end
	.loc	1 38 0                  @ fib.c:38:0
	ldr	r0, [sp, #8]
	mov	r1, sp
	mov	r2, #10
	ldr	r0, [r0, #4]
	bl	strtol
	str	r0, [sp, #4]
	.loc	1 40 0                  @ fib.c:40:0
.Ltmp7:
	bl	__errno_location
	ldr	r0, [r0]
	cmp	r0, #34
	bne	.LBB1_4
@ BB#3:                                 @ %land.lhs.true
	ldr	r0, [sp, #4]
	cmn	r0, #-2147483647
	ldrne	r0, [sp, #4]
	cmpne	r0, #-2147483648
	beq	.LBB1_6
.LBB1_4:                                @ %lor.lhs.false7
	.loc	1 42 0                  @ fib.c:42:0
	bl	__errno_location
	ldr	r0, [r0]
	cmp	r0, #0
	beq	.LBB1_7
@ BB#5:                                 @ %land.lhs.true10
	ldr	r0, [sp, #4]
	cmp	r0, #0
	bne	.LBB1_7
.LBB1_6:                                @ %if.then12
	.loc	1 43 0                  @ fib.c:43:0
.Ltmp8:
	ldr	r0, .LCPI1_4
	bl	perror
	mov	r0, #1
	.loc	1 44 0                  @ fib.c:44:0
	bl	exit
.Ltmp9:
.LBB1_7:                                @ %if.end13
	.loc	1 47 0                  @ fib.c:47:0
	ldr	r0, [sp, #8]
	ldr	r1, [sp]
	ldr	r0, [r0, #4]
	cmp	r1, r0
	bne	.LBB1_9
@ BB#8:                                 @ %if.then16
	.loc	1 48 0                  @ fib.c:48:0
.Ltmp10:
	ldr	r0, [sp, #8]
	ldr	r1, .LCPI1_3
	ldr	r2, [r0, #4]
	ldr	r0, .LCPI1_1
	ldr	r0, [r0]
	b	.LBB1_11
.Ltmp11:
.LBB1_9:                                @ %if.end19
	.loc	1 52 0                  @ fib.c:52:0
	ldr	r0, [sp]
	ldrsb	r0, [r0]
	cmp	r0, #0
	beq	.LBB1_12
@ BB#10:                                @ %if.then22
	.loc	1 53 0                  @ fib.c:53:0
.Ltmp12:
	ldr	r0, .LCPI1_1
	ldr	r2, [sp]
	ldr	r1, .LCPI1_2
	ldr	r0, [r0]
.LBB1_11:                               @ %if.then22
	bl	fprintf
	mov	r0, #1
	.loc	1 54 0                  @ fib.c:54:0
	bl	exit
.Ltmp13:
.LBB1_12:                               @ %if.end24
	.loc	1 57 0                  @ fib.c:57:0
	ldr	r0, [sp, #4]
	bl	fib
	mov	r1, r0
	.loc	1 59 0                  @ fib.c:59:0
	ldr	r0, .LCPI1_0
	.loc	1 57 0                  @ fib.c:57:0
	str	r1, [sp, #4]
	.loc	1 59 0                  @ fib.c:59:0
	bl	printf
	mov	r0, #0
	.loc	1 60 0                  @ fib.c:60:0
	bl	exit
.Ltmp14:
	.align	2
@ BB#13:
.LCPI1_0:
	.long	.L.str4
.LCPI1_1:
	.long	stderr
.LCPI1_2:
	.long	.L.str3
.LCPI1_3:
	.long	.L.str2
.LCPI1_4:
	.long	.L.str1
.LCPI1_5:
	.long	.L.str
.Ltmp15:
	.size	main, .Ltmp15-main
.Lfunc_end1:

	.type	.L.str,%object          @ @.str
	.section	.rodata.str1.1,"aMS",%progbits,1
.L.str:
	.asciz	"usage: %s <value>\n"
	.size	.L.str, 19

	.type	.L.str1,%object         @ @.str1
.L.str1:
	.asciz	"strtol"
	.size	.L.str1, 7

	.type	.L.str2,%object         @ @.str2
.L.str2:
	.asciz	"error: %s is not an integer\n"
	.size	.L.str2, 29

	.type	.L.str3,%object         @ @.str3
.L.str3:
	.asciz	"error: junk at end of parameter: %s\n"
	.size	.L.str3, 37

	.type	.L.str4,%object         @ @.str4
.L.str4:
	.asciz	"%d\n"
	.size	.L.str4, 4

	.text
.Ldebug_end0:
	.section	.debug_str,"MS",%progbits,1
.Linfo_string0:
	.asciz	"clang version 3.4 (tags/RELEASE_34/final)"
.Linfo_string1:
	.asciz	"fib.c"
.Linfo_string2:
	.asciz	"/home/cs6332/Downloads/cs6332.001-f20-assign0x5-master/fib"
.Linfo_string3:
	.asciz	"fib"
.Linfo_string4:
	.asciz	"int"
.Linfo_string5:
	.asciz	"main"
.Linfo_string6:
	.asciz	"i"
.Linfo_string7:
	.asciz	"argc"
.Linfo_string8:
	.asciz	"argv"
.Linfo_string9:
	.asciz	"char"
.Linfo_string10:
	.asciz	"value"
.Linfo_string11:
	.asciz	"end"
	.section	.debug_info,"",%progbits
.L.debug_info_begin0:
	.long	169                     @ Length of Unit
	.short	4                       @ DWARF version number
	.long	.L.debug_abbrev_begin   @ Offset Into Abbrev. Section
	.byte	4                       @ Address Size (in bytes)
	.byte	1                       @ Abbrev [1] 0xb:0xa2 DW_TAG_compile_unit
	.long	.Linfo_string0          @ DW_AT_producer
	.short	12                      @ DW_AT_language
	.long	.Linfo_string1          @ DW_AT_name
	.long	0                       @ DW_AT_low_pc
	.long	.Lsection_line          @ DW_AT_stmt_list
	.long	.Linfo_string2          @ DW_AT_comp_dir
	.byte	2                       @ Abbrev [2] 0x22:0x24 DW_TAG_subprogram
	.long	.Linfo_string3          @ DW_AT_name
	.byte	1                       @ DW_AT_decl_file
	.byte	19                      @ DW_AT_decl_line
                                        @ DW_AT_prototyped
	.long	70                      @ DW_AT_type
                                        @ DW_AT_external
	.long	.Lfunc_begin0           @ DW_AT_low_pc
	.long	.Lfunc_end0             @ DW_AT_high_pc
	.byte	1                       @ DW_AT_frame_base
	.byte	91
	.byte	3                       @ Abbrev [3] 0x37:0xe DW_TAG_formal_parameter
	.long	.Linfo_string6          @ DW_AT_name
	.byte	1                       @ DW_AT_decl_file
	.byte	19                      @ DW_AT_decl_line
	.long	70                      @ DW_AT_type
	.byte	2                       @ DW_AT_location
	.byte	125
	.byte	0
	.byte	0                       @ End Of Children Mark
	.byte	4                       @ Abbrev [4] 0x46:0x7 DW_TAG_base_type
	.long	.Linfo_string4          @ DW_AT_name
	.byte	5                       @ DW_AT_encoding
	.byte	4                       @ DW_AT_byte_size
	.byte	2                       @ Abbrev [2] 0x4d:0x4e DW_TAG_subprogram
	.long	.Linfo_string5          @ DW_AT_name
	.byte	1                       @ DW_AT_decl_file
	.byte	28                      @ DW_AT_decl_line
                                        @ DW_AT_prototyped
	.long	70                      @ DW_AT_type
                                        @ DW_AT_external
	.long	.Lfunc_begin1           @ DW_AT_low_pc
	.long	.Lfunc_end1             @ DW_AT_high_pc
	.byte	1                       @ DW_AT_frame_base
	.byte	91
	.byte	3                       @ Abbrev [3] 0x62:0xe DW_TAG_formal_parameter
	.long	.Linfo_string7          @ DW_AT_name
	.byte	1                       @ DW_AT_decl_file
	.byte	28                      @ DW_AT_decl_line
	.long	70                      @ DW_AT_type
	.byte	2                       @ DW_AT_location
	.byte	145
	.byte	120
	.byte	3                       @ Abbrev [3] 0x70:0xe DW_TAG_formal_parameter
	.long	.Linfo_string8          @ DW_AT_name
	.byte	1                       @ DW_AT_decl_file
	.byte	28                      @ DW_AT_decl_line
	.long	155                     @ DW_AT_type
	.byte	2                       @ DW_AT_location
	.byte	125
	.byte	8
	.byte	5                       @ Abbrev [5] 0x7e:0xe DW_TAG_variable
	.long	.Linfo_string10         @ DW_AT_name
	.byte	1                       @ DW_AT_decl_file
	.byte	30                      @ DW_AT_decl_line
	.long	70                      @ DW_AT_type
	.byte	2                       @ DW_AT_location
	.byte	125
	.byte	4
	.byte	5                       @ Abbrev [5] 0x8c:0xe DW_TAG_variable
	.long	.Linfo_string11         @ DW_AT_name
	.byte	1                       @ DW_AT_decl_file
	.byte	31                      @ DW_AT_decl_line
	.long	160                     @ DW_AT_type
	.byte	2                       @ DW_AT_location
	.byte	125
	.byte	0
	.byte	0                       @ End Of Children Mark
	.byte	6                       @ Abbrev [6] 0x9b:0x5 DW_TAG_pointer_type
	.long	160                     @ DW_AT_type
	.byte	6                       @ Abbrev [6] 0xa0:0x5 DW_TAG_pointer_type
	.long	165                     @ DW_AT_type
	.byte	4                       @ Abbrev [4] 0xa5:0x7 DW_TAG_base_type
	.long	.Linfo_string9          @ DW_AT_name
	.byte	6                       @ DW_AT_encoding
	.byte	1                       @ DW_AT_byte_size
	.byte	0                       @ End Of Children Mark
.L.debug_info_end0:
	.section	.debug_abbrev,"",%progbits
.L.debug_abbrev_begin:
	.byte	1                       @ Abbreviation Code
	.byte	17                      @ DW_TAG_compile_unit
	.byte	1                       @ DW_CHILDREN_yes
	.byte	37                      @ DW_AT_producer
	.byte	14                      @ DW_FORM_strp
	.byte	19                      @ DW_AT_language
	.byte	5                       @ DW_FORM_data2
	.byte	3                       @ DW_AT_name
	.byte	14                      @ DW_FORM_strp
	.byte	17                      @ DW_AT_low_pc
	.byte	1                       @ DW_FORM_addr
	.byte	16                      @ DW_AT_stmt_list
	.byte	23                      @ DW_FORM_sec_offset
	.byte	27                      @ DW_AT_comp_dir
	.byte	14                      @ DW_FORM_strp
	.byte	0                       @ EOM(1)
	.byte	0                       @ EOM(2)
	.byte	2                       @ Abbreviation Code
	.byte	46                      @ DW_TAG_subprogram
	.byte	1                       @ DW_CHILDREN_yes
	.byte	3                       @ DW_AT_name
	.byte	14                      @ DW_FORM_strp
	.byte	58                      @ DW_AT_decl_file
	.byte	11                      @ DW_FORM_data1
	.byte	59                      @ DW_AT_decl_line
	.byte	11                      @ DW_FORM_data1
	.byte	39                      @ DW_AT_prototyped
	.byte	25                      @ DW_FORM_flag_present
	.byte	73                      @ DW_AT_type
	.byte	19                      @ DW_FORM_ref4
	.byte	63                      @ DW_AT_external
	.byte	25                      @ DW_FORM_flag_present
	.byte	17                      @ DW_AT_low_pc
	.byte	1                       @ DW_FORM_addr
	.byte	18                      @ DW_AT_high_pc
	.byte	1                       @ DW_FORM_addr
	.byte	64                      @ DW_AT_frame_base
	.byte	10                      @ DW_FORM_block1
	.byte	0                       @ EOM(1)
	.byte	0                       @ EOM(2)
	.byte	3                       @ Abbreviation Code
	.byte	5                       @ DW_TAG_formal_parameter
	.byte	0                       @ DW_CHILDREN_no
	.byte	3                       @ DW_AT_name
	.byte	14                      @ DW_FORM_strp
	.byte	58                      @ DW_AT_decl_file
	.byte	11                      @ DW_FORM_data1
	.byte	59                      @ DW_AT_decl_line
	.byte	11                      @ DW_FORM_data1
	.byte	73                      @ DW_AT_type
	.byte	19                      @ DW_FORM_ref4
	.byte	2                       @ DW_AT_location
	.byte	10                      @ DW_FORM_block1
	.byte	0                       @ EOM(1)
	.byte	0                       @ EOM(2)
	.byte	4                       @ Abbreviation Code
	.byte	36                      @ DW_TAG_base_type
	.byte	0                       @ DW_CHILDREN_no
	.byte	3                       @ DW_AT_name
	.byte	14                      @ DW_FORM_strp
	.byte	62                      @ DW_AT_encoding
	.byte	11                      @ DW_FORM_data1
	.byte	11                      @ DW_AT_byte_size
	.byte	11                      @ DW_FORM_data1
	.byte	0                       @ EOM(1)
	.byte	0                       @ EOM(2)
	.byte	5                       @ Abbreviation Code
	.byte	52                      @ DW_TAG_variable
	.byte	0                       @ DW_CHILDREN_no
	.byte	3                       @ DW_AT_name
	.byte	14                      @ DW_FORM_strp
	.byte	58                      @ DW_AT_decl_file
	.byte	11                      @ DW_FORM_data1
	.byte	59                      @ DW_AT_decl_line
	.byte	11                      @ DW_FORM_data1
	.byte	73                      @ DW_AT_type
	.byte	19                      @ DW_FORM_ref4
	.byte	2                       @ DW_AT_location
	.byte	10                      @ DW_FORM_block1
	.byte	0                       @ EOM(1)
	.byte	0                       @ EOM(2)
	.byte	6                       @ Abbreviation Code
	.byte	15                      @ DW_TAG_pointer_type
	.byte	0                       @ DW_CHILDREN_no
	.byte	73                      @ DW_AT_type
	.byte	19                      @ DW_FORM_ref4
	.byte	0                       @ EOM(1)
	.byte	0                       @ EOM(2)
	.byte	0                       @ EOM(3)
.L.debug_abbrev_end:
	.section	.debug_aranges,"",%progbits
	.long	28                      @ Length of ARange Set
	.short	2                       @ DWARF Arange version number
	.long	.L.debug_info_begin0    @ Offset Into Debug Info Section
	.byte	4                       @ Address Size (in bytes)
	.byte	0                       @ Segment Size (in bytes)
	.byte	255
	.byte	255
	.byte	255
	.byte	255
	.long	.Lfunc_begin0
.Lset0 = .Ldebug_end0-.Lfunc_begin0
	.long	.Lset0
	.long	0                       @ ARange terminator
	.long	0
	.section	.debug_ranges,"",%progbits
	.section	.debug_macinfo,"",%progbits
	.section	.debug_pubnames,"",%progbits
.Lset1 = .Lpubnames_end0-.Lpubnames_begin0 @ Length of Public Names Info
	.long	.Lset1
.Lpubnames_begin0:
	.short	2                       @ DWARF Version
	.long	.L.debug_info_begin0    @ Offset of Compilation Unit Info
.Lset2 = .L.debug_info_end0-.L.debug_info_begin0 @ Compilation Unit Length
	.long	.Lset2
	.long	34                      @ DIE offset
	.asciz	"fib"                   @ External Name
	.long	77                      @ DIE offset
	.asciz	"main"                  @ External Name
	.long	0                       @ End Mark
.Lpubnames_end0:
	.section	.debug_pubtypes,"",%progbits
.Lset3 = .Lpubtypes_end0-.Lpubtypes_begin0 @ Length of Public Types Info
	.long	.Lset3
.Lpubtypes_begin0:
	.short	2                       @ DWARF Version
	.long	.L.debug_info_begin0    @ Offset of Compilation Unit Info
.Lset4 = .L.debug_info_end0-.L.debug_info_begin0 @ Compilation Unit Length
	.long	.Lset4
	.long	70                      @ DIE offset
	.asciz	"int"                   @ External Name
	.long	165                     @ DIE offset
	.asciz	"char"                  @ External Name
	.long	0                       @ End Mark
.Lpubtypes_end0:

	.ident	"clang version 3.4 (tags/RELEASE_34/final)"
