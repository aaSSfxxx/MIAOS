; Code running in protected mode (32 bit)
; Manages IRQs

BITS 32

extern ISRDispatcher
extern ClockTick
extern KeyboardHandler

%macro USER_ISR 1  ; define a macro, taking one parameter
  [GLOBAL isr%1]        ; %1 accesses the first parameter.
  isr%1:
    cli
    push byte 0
    push %1
    jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
  [GLOBAL isr%1]
  isr%1:
    cli
    push %1
    jmp isr_common_stub
%endmacro

isr_common_stub:
   pusha                    ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

   mov ax, ds               ; Lower 16-bits of eax = ds.
   push eax                 ; save the data segment descriptor

   mov ax, 0x10  	; load the kernel data segment descriptor
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax
   call ISRDispatcher
   pop eax        ; reload the original data segment descriptor
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   popa                     ; Pops edi,esi,ebp...
   add esp, 8     ; Cleans up the pushed error code and pushed ISR number
   sti
   iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ES


; we don't give a fuck about default ISRs
global default_isr
default_isr:
	mov al,0x20
	out 0x20,al
	iret
	
ISR_ERRCODE 8
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14

;; User-defined interruptions
USER_ISR 0x80

global isr32
isr32:
	call ClockTick
	mov al,0x20
	out 0x20,al
	iret

global isr33
isr33:
	call KeyboardHandler	
	mov al,0x20
	out 0x20,al
	iret
