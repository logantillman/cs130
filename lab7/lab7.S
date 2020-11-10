// Lab 7 
// COSC130
// This lab is a calculator in riscv
// Logan Tillman
// 2-28-19

.section .rodata
output: .asciz "%d %c %d = %d\n"
integer_scan: .asciz "%d"
char_scan: .asciz "%c"
not_enuff: .asciz "Not enough arguments.\n"
too_many: .asciz "Too many arguments.\n"
invalid_operator: .asciz "Unknown operator '%c'\n"

.section .text
add:
		lw		a0, 32(sp)	// a0 = left
		lw	 	a1, 37(sp)	// a1 = right
		add		s3, a0, a1	// s3 = result
		j		print

subtract:
		lw		a0, 32(sp)
		lw		a1,	37(sp)
		sub		s3, a0, a1
		j		print

multiply:
		lw		a0, 32(sp)
		lw		a1, 37(sp)
		mul		s3, a0, a1
		j		print

divide:
		lw		a0, 32(sp)
		lw		a1, 37(sp)
		li		t0, 0
		beq		a1, t0, 1f	// Checks if right = 0
		div		s3, a0, a1
		j		print
1:
		li		s3, -1	// If right = 0, returns -1
		j		print
modulo:
		lw		a0, 32(sp)
		lw		a1, 37(sp)
		li		t0, 0
		beq		a1, t0, 1f	// Checks if right = 0
		rem		s3, a0, a1
		j		print
1:
		li		s3, 0	// Returns 0 if right = 0
		j		print

.global main
main:
		addi	sp, sp, -45
		sd		ra, 0(sp)

		// Check the command line arguments
		li		t0, 4
		blt		a0, t0, not_enough_arguments
		bgt		a0, t0, too_many_arguments

		// We are going to use the saved registers
		// to preserve information across function
		// calls. So, we need to save them before
		// using them
		sd		s0, 8(sp)
		sd		s1, 16(sp)
		sd		s2, 24(sp)
		sd		s3,	41(sp)

		// If we get here, we have the exact amount of
		// arguments that we need.
		ld		s0, 8(a1)	// s0 = argv[1]
		ld		s1, 16(a1)	// s1 = argv[2]
		ld		s2, 24(a1)	// s2 = argv[3]

		// Now use sscanf to convert command line arguments into
		// integers and characters.
		// sscanf(argv[1], "%d", &left)
		mv		a0, s0
		la		a1, integer_scan
		addi	a2, sp, 32	// &left is sp + 32	
		call	sscanf@plt

		// We should check return value, but it isnt' required
		// sscanf(argv[2], "%c", &op)
		mv		a0, s1
		la		a1, char_scan
		addi	a2, sp, 36	// &op is sp + 36
		call	sscanf@plt

		// sscanf(argv[3], "%d", &right)
		mv		a0, s2
		la		a1, integer_scan
		addi	a2, sp, 37	// &right is sp + 37
		call sscanf@plt

		// Add
		li		t0, '+'
		lb		t1, 36(sp)	// t1 = operator
		beq		t1, t0, add	// Compares '+' to the operator

		// Subtract
		li		t0, '-'
		beq		t1, t0, subtract	// Compares '-' to the operator

		// Multiply
		li		t0, 'x'
		beq		t1, t0, multiply	// Compares 'x' to the operator

		// Divide
		li		t0, '/'
		beq		t1, t0, divide	// Compares '/' to the operator

		// Modulo
		li		t0, '%'
		beq		t1, t0, modulo	// Compares '%' to the operator
		
		// Error
		la		a0, invalid_operator	// If none of the above execute
		lb		a1, 36(sp)				// this calls printf and prints
		call	printf@plt				// the error statement
		j		exit

print:
		// Prints the results
		la		a0, output
		lw		a1, 32(sp)	// left
		lb		a2, 36(sp)	// op
		lw		a3, 37(sp)	// right
		mv		a4, s3		// result
		call printf@plt

		// Reload the saved registers from the stack
		// before we exit.
		ld		s0, 8(sp)
		ld		s1, 16(sp)
		ld		s2, 24(sp)
		lw		s3, 41(sp)

		j		exit

not_enough_arguments:	// Executes if there aren't enough arguments
		la		a0, not_enuff
		call	printf@plt
		j		exit
	
too_many_arguments:		// Executes if there are too many arguments
		la		a0, too_many
		call	printf@plt

exit:	// Exits the program and re-adds to the stack
		ld		ra, 0(sp)
		addi	sp, sp, 45
		ret
