            global    _main
            extern    _printf
            extern    _gets
            extern    _strtoul
            default    rel
        
            section    .data
test_message:    db    "1: %u, 2: %u", 0x0A, 0x00
first_message:   db    "Please supply the first of the two numbers: ", 0x00
second_message:  db    "Please supply the second of the two numbers: ", 0x00
error_message:   db    "I'm afraid %u wasn't a number. ", 0x00
over_message:    db    "I can't work with that many arguments...", 0x0A, 0x00
gcd_message:     db    "The GCD of %u and %u is %u!", 0x0A, 0x00
gcd_message_0:   db    "The GCD of %u and %u is %u (but not really)!", 0x0A, 0x00
            section    .bss
argv:       resd       1
get_buffer: resb       100
num_1:      resd       1
num_2:      resd       1
            section    .text
_main:
            push    ebp             ; standard function start thing
            mov     ebp, esp
            
            mov     eax, [ebp+8]    ; load in argc and argv from stack
            mov     ebx, [ebp+12]    
            cmp     eax, 3
            jl      get_first
            je      args_to_nums
            jg      too_many_args
get_first:
            push    first_message
            call    _printf
            add     esp, 4
            push    get_buffer
            call    _gets
            add     esp, 4
            cmp     eax, 0
            jne     test_first
error_first:
            push    eax
            push    error_message
            call    _printf
            add     esp, 4
            jmp     get_first
test_first:
            push    10
            push    0
            push    eax
            call    _strtoul
            cmp     eax, 0
            je      error_first
            mov     ebx, eax
get_second:
            push    second_message
            call    _printf
            add     esp, 4
            push    get_buffer
            call    _gets
            add     esp, 4
            cmp     eax, 0
            jne     test_second
error_second:
            push    eax
            push    error_message
            call    _printf
            add     esp, 4
            jmp     get_second
test_second:
            push    10
            push    0
            push    eax
            call    _strtoul
            cmp     eax, 0
            je      error_second
            jmp     findGCD
args_to_nums:
            push    10
            push    0
            push    dword [ebx + 4]
            call    _strtoul
            add     esp, 4
            push    10
            push    0
            push    dword [ebx + 8]
            mov     ebx, eax
            call    _strtoul
            add     esp, 4
            push    ebx
            push    eax
            jmp     findGCD
too_many_args:
            push    over_message
            call    _printf
            add     esp, 4
            mov     eax, 1
            jmp     done
            
findGCD:
            mov     [num_1], ebx
            mov     [num_2], eax
zero_check:
            mov     ecx, eax        ; neither number should be zero
            mul     ebx             ; if x * y = 0, x and/or y must be zero
            cmp     eax, 0            
            je      zero_handle     ; do error handling things
            mov     eax, ecx        ; restore eax's state
            
            cmp     eax, ebx        ; ebx must be less than eax for the algorithm
            jg      set_bound       ; swap the register's contents otherwise
swap_regs:    
            mov     ecx, eax
            mov     eax, ebx
            mov     ebx, ecx
set_bound:
            mov     ecx, ebx        ; ebx will be getting decremented, so we need another register to store the actual number
is_div:
            xor     edx, edx        ; div puts the remainder in edx, but doesn't use the entire set of bits
                                    ; if we don't clear this, we may end up with garbage data in the upper word
            push    eax             ; eax is getting divided, so we'll store its state to restore it later
            div     ebx             ; divide eax by ebx
            pop     eax             ; restore eax's pre-divided state            
            cmp     edx, 0          ; if the remainder is 0, ebx is a factor of eax - this is a good sign
            je      cmp_second      ; compare with the next number if this happens
continue:
            dec     ebx             ; try a lower number for ebx
            cmp     ebx, 1          ; the lowest gcd a number can have is 1
            jg      is_div
cmp_second:
            push    eax             ; same eax state-storing as before
            mov     eax, ecx        ; div only works on eax, so we'll set it to the second number
                                    ; eax's origin state is already on the stack, so there's no need to swap registers
            xor     edx, edx        ; second verse same as the first
            div     ebx    
            pop     eax
            cmp     edx, 0
            je      div_found       ; finish the function is the second number is also divisible by the candidate
            jmp     continue        ; keep trying otherwise
div_found:
            mov     eax, ebx
            mov     ebx, gcd_message
            jmp     printGCD
zero_handle:
            mov     eax, 0          ; set the return value to an error state
            mov     ebx, gcd_message_0
            jmp     done

printGCD:    
            push    eax
            push    dword [num_2]
            push    dword [num_1]
            push    ebx
            call    _printf
            add     esp, 16
            jmp     done
done:
            pop     ebp
            ret
