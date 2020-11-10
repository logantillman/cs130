.section .rodata
output_integer: .asciz "%d\n"
/*enter: .asciz "Enter your name: "
input: .asciz "%s"
output: .asciz "Hello, %s\n"
*/

//	a0 get_random(     a0,     a1)
// int get_random(int min, int max)
// {
//				a1 +			a1-a0-1
//		return min + rand() % (max-min+1);
// }
.section .text

get_random: 
		// a0 = int min
		// a1 = int max
		sub		a1, a1, a0
		// a1 = a1 - a0
		addi	a1, a1, 1
		// a1 = a1 + 1
		// Now, a1 = (max - min) + 1

		// Adding to the stack
		addi	sp, sp, -8
		sw		a0, 0(sp)	//*(sp + 0) = a0
		sw		a1, 4(sp)
		sd		ra, 8(sp)
		call	rand
		//a0 contains a large random number
		lw		t0, 0(sp)	// t0 = min
		lw		t1, 4(sp)	// t1 = max-min+1
		// min + rankd() % (max-min+1)
		//	t0		a0			t1
		rem		a0, a0, t1	// rand() % (max-min+1)
		add		a0, t0, a0	// a0 = min + rand() % (max-min+1)
	
		ld		ra, 8(sp)
		addi	sp, sp, 16
		ret

.global main
main:
		addi	sp, sp, -8
		sd		ra, 0(sp)
		// srand(time(NULL))	// Zero
		mv		a0, zero
		call	time
		//a0
		call srand
		//a0
	
		//	a0					  a0  a1
		//int result = get_random(10, 20)
		li		a0, 10
		// a0 = 10
		li		a1, 20
		// a1 = 20
		call	get_random
		//a0
		mv		a1, a0
		// a1 = a0
		la		a1, output_integer
		call printf

		ld		ra, 0(sp)
		addi	sp, sp, 8
		ret








/*		addi	sp, sp, -264
		sd		ra, 0(sp)
		//char name[256] starts at 8(sp)
		la		a0, enter
		call	printf
		
		//		a0     a1
		//scanf("%s", name)
		la		a0, input
		addi	a1, sp, 8
		call	scanf

		//		   a0            a1
		//printf("Hello, %s\n", name)
		la		a0, output
		addi	a1, sp, 8
		call	printf

		ld		ra, 0(sp)
		addi	sp, sp, 264
		ret
*/
