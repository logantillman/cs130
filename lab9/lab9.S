// Lab9
// COSC130
// Logan Tillman
// This lab will take a 64-bit virtual address and dissect it into its component parts
// 3-27-19

.section .rodata
usage: .asciz "Usage ./lab9 <64-bit virtual address>\n"
hex_scan: .asciz "%lx\n"
po: .asciz "PO       = %x\n"
vpn: .asciz "VPN[%03d] = %d    (%4d)\n"
list: .asciz "  Level   Index  Byte Offset\n"

.section .text
.global main
main:
		//				a0			a1
		// int main(int argc, char *argv[])
		addi	sp, sp, -24
		sd		ra, 0(sp)

		// Check command line arguments
		li		t0, 2
		blt		a0, t0, usage_message
		bgt		a0, t0, usage_message

		// Storing saved registers to the stack
		sd		s0, 8(sp)	// long num;
		sd		s1,	16(sp)	// int po;
		sd		s2, 20(sp)	// int i; (My iterator for the VPN loop)

		// sscanf(argv[1], "%lx", &num)
		ld		a0, 8(a1)
		la		a1,	hex_scan
		addi	a2, sp, 8	// s0 = &num
		call sscanf@plt

		// Gets the value of PO
		ld		s0, 8(sp)
		li		t0, 0xfff
		and		s1, s0, t0	// po = num & 0xfff
		srai	s0, s0, 12

		// Prints the Level Index and Byte Offset column headings
		la		a0, list
		call	printf@plt

		// For loop for calculating the VPN values
		li		s2, 2	// int i = 2
1:
		li		t1, 0		// i >= 0
		li		t3, 0x1ff	// And value
		li		a5, 9		// Using this 9 to get my shift value
		mul		t6, s2, a5	// t6 = i * 9 (gets my shift value)
		sra		a6, s0, t6	// Shifts left by t6
		li		t4, 8		// 8 to calculate byte offset

		blt		s2, t1, 1f	// for (int i = 2; i >= 0; i--)
		and		t2, a6, t3	// t2 = VPN[i]
		mul		t5,	t2, t4	// t5 = byte offset (index * 8)
		la		a0, vpn		// Loading output message
		mv		a1, s2		// t0 = i
		mv		a2, t2		// t2 = VPN[i]
		mv		a3, t5		// t5 = byte offset
		call	printf@plt
		addi	s2, s2, -1	// i--
		j		1b
1:

		// Prints the message for PO
		la		a0, po
		mv		a1,	s1
		call	printf@plt
		j		exit
		
usage_message:	// Executes if argc is invalid
		la		a0, usage
		call	printf@plt
		j		exit

exit:	// Exits the program *CHECK TO SEE IF LD ALL VARIABLES*
		ld		ra, 0(sp)
		ld		s0, 8(sp)
		lw		s1, 16(sp)
		lw		s2, 20(sp)
		addi	sp, sp, 24
		ret
