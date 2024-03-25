.text
.extern printf
.global _start

_start:
	adr x0, x		//pointer to x points
	adr x1, y		//pointer to y points
	
	adr x2, Great
    ldr d9, [x2]
    fmov d10, d9		//d10 is greatest distance so far

	adr x3, Small
    ldr d11, [x3]
    fmov d12, d11		//d12 is smallest distance so far

	ldr x9, =N
	ldr x9,[x9]		//int length
	
	add x10, xzr, xzr	//int i = 0

	ldr x25, =buffer	//buffer for later 

OuterLoop:
	cmp x10, x9
	b.ge exit		//if i = n, exit loop

	ldr d1, [x0, x10, lsl 3]	//xroot = x[i]
	ldr d2, [x1, x10, lsl 3]	//yroot = y[i]
	add x11, x10, 1				//int j = i + 1

	InnerLoop:
		cmp x11, x9
		b.ge iplus		//if j = n, do i++ and exit loop
		
		ldr d3, [x0, x11, lsl 3]	//xcompare = x[j]. d3 will hold xdistance later
		ldr d4, [x1, x11, lsl 3]	//ycompare = y[j]. d4 will hold ydistance later

	xdistance:
		fsub d3, d1, d3				//xdistance = xroot - xcompare

	ydistance:
		fsub d4, d2, d4				//rdistance = yroot- ycompare

	distance:
		fmul d3, d3, d3		//a^2
		fmul d4, d4, d4		//b^2
		fadd d3, d3, d4		//distance = a^2 + b^2
		
		fcmp d3, d10
		b.le Smallest_check

	Greatest:
		fmov d10, d3			//greatest = distance
		mov x5, x10			//index of first points = i
		mov x6, x11			//index of second points = j

	Smallest_check:
		//if (smallest == 0 or distance < smallest), set smallest to distance
		fcmp d12, 0.0		//if it's equal to 0, overwrite smallest
		b.eq Smallest

		fcmp d3, d12
		b.ge checkInnerLoop

	Smallest:
		fmov d12, d3			//distance = smallest 
		mov x7, x10			//index of first points = i
		mov x8, x11			//index of second points = j

	checkInnerLoop:
		add x11, x11, 1		//j++
		b InnerLoop

	exit:
		ldr d12, [x0, x5, lsl 3]	//greatest x for first point
		ldr d13, [x1, x5, lsl 3]	//greatest y for first point

		ldr d14, [x0, x6, lsl 3]	//greatest x for second point
		ldr d15, [x1, x6, lsl 3]	//greatest y for second point
		
		ldr d16, [x0, x7, lsl 3]	//smallest x for first point
		ldr d17, [x1, x7, lsl 3]	//smallest y for first point

		ldr d18, [x0, x8, lsl 3]	//smallest x for second point
		ldr d19, [x1, x8, lsl 3]	//smallest y for second point
		
		ldr x0, =GPrint
		
		fmov d0, d12
		fmov d1, d13
		fmov d2, d14
		fmov d3, d15
		bl printf

		ldr x0, =SPrint
		fmov d0, d16
		fmov d1, d17
		fmov d2, d18
		fmov d3, d19
		bl printf

		mov x0, #0
    	mov w8, #93 
    	svc #0 

	iplus:
		add x10, x10, 1
		b OuterLoop

	.data
N:
	.dword 8
x:
	.double 0.0, 0.4140, 1.4949, 5.0014, 6.5163, 3.9303, 8.4813, 2.6505
y: 	
	.double 0.0, 3.9862, 6.1488, 1.047, 4.6102, 1.4057, 5.0371, 4.1196
Great:
	.double 0.0
Small: 
	.double 0.0
GPrint:
	.asciz "Greatest distance is between (%lf,%lf) and (%lf,%lf)\n"
SPrint:
	.asciz "Smallest distance is between (%lf,%lf) and (%lf,%lf)\n"

	.bss
buffer:
	.skip 8
