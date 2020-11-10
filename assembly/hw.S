// Assembly
/*
	int main()
	{
		printf("Hello, COSC130!\n");
		return 0;
	}
*/
.section .rodata
hello_world: .asciz "Hello, COSC130!\n"

.section .text
.global main
main:
		addi	sp, sp, -8
		// sp = sp + -8

//		sub		a0, a1, a2
		// a0 = a1 - a2

		sd		ra, 0, sp
		//	*(sp + 0) = ra

		//PRINTF HERE
		//a0, a1, a2
		//printf(string)
		la		a0, hello_world
		//a0 = hello_world
		call	printf

		ld		ra, 0, sp

		addi	sp, sp, 8
		ret
