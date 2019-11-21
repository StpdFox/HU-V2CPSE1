.cpu cortex-m3
.data

.global decompressed_data
decompressed_data:
.asciz ""
.skip 4096
.text
.align 1

.global decompress

decompress:
    LDR r0, =compressed_data
    LDR r1, =decompressed_data // Buffer

loop:
    LDRB r2, [r0] // Load char in r2

    cmp r2, #0 // End of file
    BEQ done

    CMP r2, #'@' // Start of encoding
    BEQ decode

    strb r2, [r1] // store r1 in the bffer

    PUSH {r0 - r2} // Save before branch
    MOV r0, r2 // move char in r0 (to pass it as the first parameter)
    BL print_char
    POP {r0 - r2} // Restore registers

    ADD r0, #1
    ADD r1, #1
    B loop

decode:
    ADD r0, #1 // Go one forward (the character after @)

    LDRB r3, [r0] // offset
    ADD r3, #1 // Add one to offset
    ADD r0, #1 // The length of the encoded characters
    LDRB r4, [r0] // Get the length character

    ADD r0, #1 // Move past length character
    MOV r5, r1 // Move buffer to r5

    SUB r3, r3, #' ' // Get actual values for offset and length
    SUB r4, r4, #' ' // ^

    SUB r5, r5, r3 // Go back to where the original characters start

decoder:
    CMP r4, #0 // End of decoded move go back to loop
    BEQ loop

    LDRB r2, [r5] // Load current character into r2
    STRB r2, [r1] // Store current character into r1 (buffer)

    PUSH {r0 - r3} // Save before branch
    MOV r0, r2 // move char in r0 (to pass it as the first parameter)
    BL print_char
    POP {r0 - r3} // Restore registers

    ADD r5, #1
    ADD r1, #1
    SUB r4, #1
    B decoder

done:
    MOV pc, lr