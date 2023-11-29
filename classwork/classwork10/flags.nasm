; ----------------------------------------------------------------------------------------
; This is a Win32 console program that displays the contents of the flags register on
;     the display.  In addition, if the carry flag is set, it outputs a message to that
;     effect, and if the overflow flag gets set, it outputs that message as well.
;
;  to assemble:   nasm -fwin32 flagsPC.nasm
;  to link:       gcc -m32 flagsPC.obj -o flagsPC.exe
;  to run:        flagsPC
; ----------------------------------------------------------------------------------------

            global      _main
            extern      _printf
            default     rel

            section     .text
_main:
            push        EBX               ; save this one

begin:      pushf                         ; push the value of the flags onto the stack
            pop         EDX               ; pop flags and load into EDX
            mov         EBX,  0x97401271  ; load big number into EBX
            mov         [number], EBX    ; save EBX's value into variable
            mov         [flags],   EDX    ; save flags values into variable
            push        EDX               ; display the starting value of the flags
            push        flagFormat
            call        _printf
            add         esp,  8           ; Line up stack pointer
display1:
            xor         EAX,  EAX         ; clear EAX
            mov         EAX,  [number]   ; load number value variable into EAX
            push        EAX               ; display the starting value of the EAX register
            push        EAXFormat
            call        _printf
            add         esp,  8           

addloop:
            mov         EAX,  [number]   ; load number value variable
            add         EAX,  [addvalue]  ; add the addvalue variable to number
            pushf                         ; put flag values on the stack
            mov         [number], EAX    ; save new value back

carrychk:
            pop         EDX               ; put flag info into EDX
            mov         [flags], EDX      ; save current flag value into variable
            and         EDX,  0x00000001  ; mask off the carry flag [bit zero]
            cmp         EDX,  0x00000001  ; check if the carry flag is set
            je          display2          ; it's set, so output the message
            jmp         ovrflwchk         ; not set yet, go to overflow section

display2:
            push        carryFormat           ; display the carry flag set message
            call        _printf
            add         esp,  4
            mov         EDX,  [flags]     ; get the values of the flags
            push        EDX               ; push flag values to stack 
            push        flagFormat
            call        _printf           ; print flags with formatting
            add         esp,  8           ; pop the stack
            jmp         done

ovrflwchk:
            mov         EDX,  [flags]     ; get the flags value again
            and         EDX,  0x00000800  ; mask off the overflow flag [bit eleven]
            cmp         EDX,  0x00000800  ; check if the overflow flag is set
            je          display3          ; it's set, so output the message
            jmp         addloop           ; time to go again!

display3:  ; display the overflow flag set message
            push        ovflwFormat
            call        _printf
            add         esp,  4

done:                                     ; Terminate program
            pop         EBX               ; restore this one
            ret

            section     .data
flagFormat: db          0x0A, "   Flag Values: 0X%08x", 0x0A, 0
EAXFormat:  db          0x0A, "   EAX: 0X%08x", 0x0A, 0
carryFormat:db          0x0A, "   Carry detected!", 0x0A, 0
ovflwFormat:db          0x0A, "   Overflow detected!", 0x0A, 0
addvalue:   dd          0x6543210

            section     .bss
number:     resb        4                 ; keeps track of number as it is changed
flags:      resb        4                 ; stores flag info 
