; TO BUILD (ON WINDOWS)
; nasm -fwin32 paritygen.asm

            global  _paritygen
            default rel
            
            section .data
            section .text
_paritygen:        
            push    ebp
            mov     ebp, esp

            xor     ebx, ebx
            mov     ebx, [ebp+8]
            xor     eax, eax            ; stores the number of 1s; start by 0ing it out
parity_loop:
            cmp     ebx, 0              ; we're done counting if all remaining bits are 0
            je      done    
            
            mov     ecx, ebx
            and     ecx, 0x1            ; mask out all but the last bit
            add     eax, ecx            ; add the end bit
            shr     ebx, 1              ; ...then move on to the next one
            jmp     parity_loop
            
done:
            neg     eax                 ; the parity bit is the opposite of the bit count's MSB
            and     eax, 0x1            ; isolate the bit!
            pop     ebp
            ret
