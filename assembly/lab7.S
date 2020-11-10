.section .rodata
output: .asciz "%d %c %d %c %d\n"
integer_scan: .asciz "%d"
char_scan: .asciz "%c"
not_enuff: .asciz "Not enough arguments.\n"
too_many: .asciz "Too many arguments.\n"

.section .text
add:
		ld		a1, 8(sp)
		ld		a2, 16(sp)
		add		a0, a1, a2
		mv		s4, a0
		ret
subtract:
		sub		a0, s0, s2
		mv		s4, a0
		ret
multiply:
		mul		a0, s0, s2
		mv		s4, a0
		ret
divide:
		div		a0, s0, s2
		mv		s4, a0
		ret
remainder:
		rem		a0, s0, s2
		mv		s4, a0
		ret

.global main
main:
		addi	sp, sp, -80
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
		sd		s3, 32(sp)
		sd		s4, 40(sp)

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
		call	sscanf

		// We should check return value, but it isn't required
		// sscanf(argv[2], "%c", &op)
		mv		a0, s1
		la		a1, char_scan
		addi	a2, sp, 40	// &op is sp + 40
		call	sscanf

		// sscanf(argv[3], "%d", &right)
		mv		a0, s2
		la		a1, integer_scan
		addi	a2, sp, 48
		call sscanf

		// Do the operations
		li		s4, '='
	//	mv		s4, a0

		// Now printf the result out
		la		a0, output
		lw		a1, 32(sp)	// left
		lb		a2, 40(sp)	// op
		lw		a3, 48(sp)	// right
		lb		a4,	56(sp)	// equals
	//	lw		a4	64(sp)	// answer
		call printf

		// Reload the saved registers from the stack
		// before we exit.
		ld		s0, 8(sp)
		ld		s1, 16(sp)
		ld		s2, 24(sp)
		ld		s3, 32(sp)
		ld		s4, 40(sp)

		j		exit

not_enough_arguments:
		la		a0, not_enuff
		call	printf
		j		exit

too_many_arguments:
		la		a0, too_many
		call printf
exit:
		ld		ra, 0(sp)
		addi	sp, sp, 80
		ret
