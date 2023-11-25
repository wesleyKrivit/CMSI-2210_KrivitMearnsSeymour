			global	_main	
			extern	_printf
			extern	_makeNBO
			default	rel
			
			section	.data
num_bytes:	dd 4			; this would change if you were running on a 64-bit machine!
test_nums:	dd 0x11223344, 0x12345678, 0xDEADBEEF, 0x0, 0x256
num_nums:	dd 5			; I do as Im told
message1:	db "%X in network byte order is ", 0x00
message2:	db "%X!", 0x0A, 0x00
iterator:	dd 0
			
			section .text
_main:
			push	ebp
loop_body:
			mov		eax, test_nums	; print first half of message, with the unswapped bytes
			add		eax, [iterator]
			push	dword [eax] 
			push	message1
			call	_printf
			add		esp, 8
			
			push	dword [num_bytes]		; load number of bytes in value (4, because 32-bit)
			mov		eax, test_nums			; load number to swap
			add		eax, [iterator]
			push	dword eax					
			call	_makeNBO				; perform swap
			add		esp, 8					; oh right I need to do this
			
			mov		eax, test_nums	; print second half of message, with the swapped bytes
			add		eax, [iterator]
			push	dword [eax] 
			push	message2
			call	_printf
			add		esp, 8
			
			mov		eax, [iterator]
			mov		ebx, [num_nums]
			inc		eax
			mov		[iterator], eax
			cmp		eax, ebx
			jle		loop_body
			
			pop ebp
			ret