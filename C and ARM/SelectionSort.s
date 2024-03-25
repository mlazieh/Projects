.text

.global _start
.extern printf


_start:
    ldr x9, =inpdata            //pointer towards array
    ldr x10, =inplen            
    ldr x10, [x10]              //length of list n
    mov x11, #0                 //sets x11 (i) to 0
    mov x12, #0                 //sets x12 (j) to 0

    Loop:
        cmp x11, x10
        b.eq exit               //exits once i = n and the array is sorted
        mov x13, x11            //sets x13 (min_index) to i

        addi x14, x11, #1       //i + 1
        sub x15, x10, x14       //n - (i + 1)
        Inner_Loop:
            cmp x12, x15
            b.eq Second_if                   //goes to outer loop if statement if j = n - (i + 1)
            
            ldr x16, [x9, x12, lsl #3]      //loads 8 byte sized element at array[j] into x16
            ldr x17, [x9, x13, lsl #3]      //loads 8 byte sized element at array[min_index] into x17

            cmp x16, x17        
            b.ge Continue_inner     //if array[j] < array[min_index], set min_index = j
            mov x13, x12
            
            Continue_inner:
                addi x12, x12, #1       //j++
                b Inner_Loop

        Second_if:
            cmp x13, x11
            b.eq Inc           //if min_index != i, swap array[min_index] and array[j]

            str x17, [x9, x13, lsl #3]      //store array[j] in array[min_index]
            str x16, [x9, x12, lsl #3]      //store array[min_index] in array[j]


            Inc:
                addi x11, x11, #1       //i++
                b Loop

exit:
    mov x0, #0 /* status := 0 */
    mov w8, #93 /* exit is syscall #1 */
    svc #0 