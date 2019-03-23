  # labwork.S

  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
 .globl delay
 .globl time2string
 .globl  enable_interrupt

.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #

  #
 .data
 .text

  hexasc:

  	andi $t0, $a0, 0xf

  	slti $t1, $a0, 10
  	bne $t1, $0, numbers

  	slti $t1, $a0, 16
  	bne $t1, $0, alphabet

  	numbers:
  		addi $v0, $t0, 0x30
  		jr $ra
  		nop

  	alphabet:
  		addi $v0, $t0, 0x37
  		jr $ra
  		nop

delay:
	while:
		ble $a0, 0, endloop
		sub $a0, $a0, 1
		li $t0, 0

		for:
			li $t1, 4000
			beq $t0, $t1, while
			nop
			addi $t0, $t0, 1

			j for
			nop

		j while
		nop

	endloop:

		jr $ra
		nop

time2string:
	PUSH $ra
	PUSH $s0
	PUSH $s1

	move $s0, $a0
	move $s1, $a1

	andi $t1, $s1, 0xf000
	srl $a0, $t1,12
	jal hexasc
	nop
	move $t2, $v0
	sb $t2, 0($s0)

	andi $t1, $s1, 0xf00
	srl $a0, $t1, 8
	jal hexasc
	nop
	move $t2, $v0
	sb $t2, 1($s0)

	li $t2, 0x3a
	sb $t2, 2($s0)

	andi $t1, $s1, 0xf0
	srl $a0, $t1, 4
	jal hexasc
	nop
	move $t2, $v0
	sb $t2, 3($s0)

	addi $t3, $0, 9

	andi $t1, $s1, 0xf
	srl $a0, $t1, 0
	bne $a0, $t3,notsurprise

	li $t2, 0x4E
	sb $t2, 4($s0)
	li $t2, 0x49
	sb $t2, 5($s0)
	li $t2, 0x4E
	sb $t2, 6($s0)
	li $t2, 0x45
	sb $t2, 7($s0)
	li $t2,0x0
	sb $t2, 8($s0)

	j ciao


	notsurprise:
	jal hexasc
	nop
	move $t2, $v0
	sb $t2, 4($s0)

	li $t2, 0x0
	sb $t2, 5($s0)

	ciao:

	POP $s1
	POP $s0
	POP $ra

	jr $ra
	nop

enable_interrupt:

  ei
  jr $ra
