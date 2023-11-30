        global _main
        extern _printf
        default rel
        
        section .data
num_nums:    dd    10
num1:        dd    0
num2:        dd    1
numstr:      db    "%d ", 0
errstr:      db    "Totally bogus iterator value, dude!", 0x0A, 0x00

_main:
        push    ebx                ; yep
        mov     eax, [num1]    
        mov     ebx, [num2]     
        mov     ecx, [num_nums]
fibloop:
        mov     [num1], eax
        mov     [num2], ebx
        mov     [num_nums], ecx
        push    eax
        push    numstr
        call    _printf
        add     esp, 8
        
        mov     eax, [num1]    
        mov     ebx, [num2]     
        mov     ecx, [num_nums]
        
        add     eax, ebx
        mov     edx, eax
        mov     eax, ebx
        mov     ebx, edx
        
        dec     ecx
        cmp     ecx, 0
        jg      fibloop
        jl      fiberror
done:
        pop     ebx
        ret
fiberror:
        push    errstr
        call    _printf
        add     esp, 4
        jmp     done
