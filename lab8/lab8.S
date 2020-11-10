// Lab8
// COSC 130
// Logan Tillman
// This lab was supposed to loop through some array and find a name and then have a median function to calculate the median but RISCV is stupid
// 3/8/19

.section .text
.global Search
Search:
		// a0 = people[]
		// a1 = num_people
		// a2 = *name
		// a3 = age
		// a4 = gender
		li		t0, 0 // int i = 0
		li		t5, 0 // int k = 0 (keeps track of a0 offset for chars)
start:
		bge		t0, a1, nomatch	// Check if i < num_people
		lb		t1,	0(a0)		// t1 = people[i].name Idk if this will work because it loads double but 52 bytes for name
		lb		t4, 0(a2)		// t4 = the name passed in the function call
		beq		t1, t4, increase	// Compares the names
		beqz	t1, 1f	// Checks for null char in the array
		j		next 
1:
		beqz	t4, name	// Checks for the null char in the name entered
		j		next
increase:
		beqz	t1,	1b	// Also checks for null char in the array because I'm not sure if this one will execute
		addi	a0, a0, 1	// Increments through the name arrays
		addi	a2, a2, 1	// name[a2]
		addi	t5, t5, 1	// k++
//		li		t6, 52
//		beq		t5, t6, name
		j		start 
name:
		sub		a0, a0, t5
		sub		a2, a2, t5
		li		t5, 0
		lw		t2, 52(a0)		// t2 = people[i].age
		beq		t2, a3, age		// Compares the age
		j		next
age:
		lw		t3, 56(a0)		// t3 = people[i].gender
		beq		t3, a4, match	// Compares the gender, if its a match it'll jump to match
		j		next
		
match:
		mv		a0, t1			// a0 = people[i].name
		j		exit 
next:
		sub		a0, a0, t5		// Subtracts the bytes from checking the char arrays
		sub		a2, a2, t5
		addi	a0, a0, 60		// Iterates to the next person in the people[] array
		addi	t0, t0, 1		// i++
		li		t5, 0			// k = 0
		j		start
nomatch:
		li		a0, 0			// loads nullptr
		j		exit
exit:
		ret

.global Median
Median:
		// a0 = array[]
		// a1 = array_size
		// a2 = *buffer
		li		t0, 0	// int i = 0
		addi	t2, a1, -1	// t2 = size - 1
		j		1f
1:
		bge		t0, t2, med
		li		t1, 1	// int j = i+1
//		ld		t3, a1		// t3 = size
		j		2f
2:
		bge		t1, t3, iiter	// while j < size
		li		a6, 4
		mul		t6,	t1, a6	// t6 = j*4
		ld		t4, 0(a0)	// t4 = array[i]	FIXTHISSHIT
		addi	t5, a0, 4	// t5 = array[j]
		bge		t5, t4, jiter	// if array[i] < array[j]
//		ld		a3, t4		// temp = array[i]
		ld		t5, 0(a0)	// array[i] = array[j]
		mv		t4, a3		// array[j] = temp
		j		2b

jiter:
		addi	t1, t1, 1	// j++
		j		2b
iiter:
		addi	t0, t0, 1	// i++
		j		1b
med:
		li		t1, 2
		rem		a5, a1, t1	// a5 = size % 2
		beqz	a5,	even
		div		t5, a1, t1	// t5 = size / 2
		add		a0,	a0, a5	// median = array[a5]
		j		exit2
even:
		div		t2, a1, t1	// t2 = size / 2

exit2:
		ret
