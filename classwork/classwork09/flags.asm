			global	_main	
			extern	_printf
		
			section .data
flagdisp:	db		"Flags register state: %04x", 0x0A, 0x00
carry:		db 		"Carry flag set!", 0x0A, 0x00
overflow:	db 		"Overflow flag set!", 0x0A, 0x00
carverflow:	db 		"Carry and overflow flag set!", 0x0A, 0x00
fail:		db		"SAD!", 0x0A, 0x00
bootlgednl: db		0x0A, 0x00
value:		dd		0x201901
			
			section .bss
flagstate:	resd	1
			
			section .text
_main:
			push 	ebx
addndisp:
			mov		eax, [value]		; load value into register!
			add		eax, 0x420420		; add the value to itself!
			mov		[value], eax		; store the value so printf doesn't destroy it!
			pushf						; get the flags state!
			pop		ebx					; stick flags into a register!
			mov		[flagstate], ebx	; store the state!
			push	ebx					; set up the printf call! (printf will eat this register but its alright since were reloading the variable each time!)
			push	flagdisp			; keep setting up!
			call	_printf
			add		esp, 8				; restore the stack pointer!
			mov		ebx, [flagstate]	; stick flags into a register (again!!!)!!!
			mov		ecx, ebx			; move flags into a temporary register so we can mess with it!
			mov		[flagstate], ebx
			and		ecx, 0x0001			; isolate the carry flag!
			cmp		ecx, 0
			jne		printcarry
testoverflow:
			mov		ecx, ebx			; move flags into a temporary register so we can mess with it (again!)!
			mov		[flagstate], ebx	; move flags into a memory address so printf doesn't eat it!
			and		ecx, 0x0800			; isolate the overflow flag!
			cmp		ecx, 0	
			jne		printoverflow
			jmp		addndisp
			
printcarry:
			push	carry
			call	_printf
			add		esp, 4
			mov		ebx, [flagstate]
			jmp		testoverflow
			
printoverflow:
			mov		[flagstate], ebx
			push	overflow
			call	_printf
			add		esp, 4
			pop		ebx	
			ret