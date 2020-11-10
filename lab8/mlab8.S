// mlab8
// COSC130
// This mini lab is a for loop that loops through an array and adds the terms
// Logan Tillman
// 2/29/19

.section .rodata
.section .text
.global get_sum
get_sum:
		li		t0, 0	// int i 
		mv		t1, a1	// int size
		li		t2, 0	// int sum
1:	
		bge		t0, t1, 1f	// for loop condition
		// Loop body
		ld		t3, 0(a0)	// t3 = array[i]
		add		t2, t2, t3	// sum = sum + array[i]
		addi	t0, t0, 1	// i++
		addi	a0, a0, 4	// array[i] + 4
		j		1b
1:
		ret

