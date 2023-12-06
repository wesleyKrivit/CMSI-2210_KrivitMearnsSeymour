; TO BUILD (ON WINDOWS)
; to assemble: nasm -fwin32 gcdFinder.asm
; to link: gcc gcdFinder.obj gcdFinder.c -std=c99 -o gcdFinder.exe
;to run: gcdFinder.exe

            global  _gcdFinder
            default rel
        
            section .text
_gcdFinder:
            push    ebp             ; standard function start thing
            mov     ebp, esp
            
            mov     eax, [ebp+8]    ; load in both numbers from stack
            mov     ebx, [ebp+12]
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
            je      div_found       ; finish the function if the second number is also divisible by the candidate
            jmp     continue        ; keep trying otherwise
div_found:
            mov     eax, ebx
            jmp     done
            
zero_handle:
            mov     eax, 0          ; set the return value to an error state
done:
            pop     ebp             ; standard function end thing
            ret                     ; get outta here
