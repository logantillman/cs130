.section .rodata
output: .asciz "%s\n"
.section .text
.global main
main:
		//a0		a0			a1
		//int main (int argc, char *argv[])

		//for (int i = 0; i < argc; i++)
		//			printf("%s", argv[i])
		addi	sp, sp, -32
		sd		ra, 0(sp)
		sd		s0, 8(sp)
		sd		s1, 16(sp)
		sd		s2, 24(sp)
		mv		s0, a0
		mv		s1, a1
		//s2 = int i
		li		t0, 0
2:
		blt		t0, a0, 1f
		j		2f
1:
		//Body of the for loop
		//			a0		a1
		la		a0, output
		slli	a1, s2, 3	// a1 = i * 8
		add		a1, a1, s1	// a1 = i*8 + argv
		ld		a1, 0(a1)
		//printf("%s\n", argv[i])
		addi	s2, s2, 1
		j		2b

2:
		//This is the end of the for loop
		ld		ra, 0(sp)
		ld		s0, 8(sp)
		ld		s1, 16(sp)
		ld		s2, 24(sp)
		addi	sp, sp, 12

		ret
