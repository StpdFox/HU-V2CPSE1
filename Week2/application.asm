    .cpu cortex-m0
    .global application
    .align 1
    .text

    string:
        .asciz "Hello world!? [@] {`} 12345==67890\n"

application:
	push {lr}
    ldr r0, =string
    bl print_asciz
	pop {pc}