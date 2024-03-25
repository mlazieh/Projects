.text

.global _start

_start:
    sub sp, sp, 16
    str lr, [sp, 8]

    mov x25, 10       //if value is ascii value for 10, then its /n which means it's done
    mov x20, xzr       //sum for loop to mul 10 to
    mov x24, xzr

Loop:

read:
    //read(fd, buffer, size of number). 0, buffer, 1

    mov x0, 0               //fd, make it 0 for read
    adr x1, buffer         //put address of buffer in x1. You'll keep replacing with the ascii value of what you input, but when you adr it here, it just holds nothing so you can keep overwriting it.
    mov x2, 1          //x2 is the bites you want to output. Size of buffer

    
    mov x8, #63             
    svc #0                  //x1 will hold pointer towards ith value of what you type

    ldr x1, =buffer            //this is in case x1 got changed to something else, point to the ascii value in buffer
    ldr x9, [x1]                //this is the value
 

    cmp x9, x25             //if value is /n exit
    b.eq writeset 
    sub x9, x9, 48          //int value of input

    mul x20, x20, x25        //sum * 10 
    add x20, x20, x9        //sum * 10 + newvalue

    b Loop

writeset:
    mul x20, x20, x20       //square. 15 * 15 = 225

writeloop:
    mov x21, 1
    
powerloop:
    cmp x21, x20
    //if x21 < x20, mul x21 by 10. If 1 < 5
    b.gt bitset
    mul x21, x21, x25
    b powerloop

bitset:
    udiv x21, x21, x25             //divide by 10 to back to right power of 10. 1
    udiv x22, x20, x21           //Most sig bit. 5/1 = 2
    mul x10, x22, x21           //5 * 1 = 200

    sub x10, x20, x10           //least sig bit = value - (Most sig bit * 10 to power of position). 5 - 5 = 25.

    add x22, x22, 48            //ascii value of most sig bit. '2'
    mov x20, x10             //move rest of number back to x20 for next loop. 25

write:
    //write(fd, buffer, size of number). 0, least sig bit, 1
    
    mov x0, 1               //fd, make it 1 for write
    adr x1, buffer         //put the pointer to the char into the buffer. Pointer to '2'
    mov x2, 1          //x2 is the bites you want to output. Size of buffer
    
    strb w22, [x1]           //store ascii value of most sig bit in buffer

    mov x8, #64             
    svc #0                  //write what's in the buffer. '5'

    cmp x20, x24        //if least sig is 0, exit
    b.eq exit

    b writeloop
    
exit:

    mov x0, #0 /* status := 0 */
    mov w8, #93 /* exit is syscall #1 */
    svc #0 

.bss
    buffer: .space 1 
