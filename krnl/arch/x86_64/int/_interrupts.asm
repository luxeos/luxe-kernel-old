;
; LuxeOS (c) 2023 by Jozef Nagy
;
; LuxeOS is licensed under a
; Creative Commons Attribution-NoDerivatives 4.0 International License.
;
; You should have received a copy of the license along with this
; work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
;
;

%include "krnl/arch/x86_64/_utils.asm"

extern int_handler

int_stub:
	cld
	pushaq
	mov rdi, rsp
	call int_handler
	mov rsp, rax
	popaq
	add rsp, 16
	iretq

%macro vector_error 1
isr_%+%1:
	push %1
	jmp int_stub
%endmacro

%macro vector_noerror 1
isr_%+%1:
	push 0
	push %1
	jmp int_stub
%endmacro

vector_noerror 0
vector_noerror 1
vector_noerror 2
vector_noerror 3
vector_noerror 4
vector_noerror 5
vector_noerror 6
vector_noerror 7
vector_error 8
vector_noerror 9
vector_error 10
vector_error 11
vector_error 12
vector_error 13
vector_error 14
vector_noerror 15
vector_noerror 16
vector_error 17
vector_noerror 18
vector_noerror 19
vector_noerror 20
vector_noerror 21
vector_noerror 22
vector_noerror 23
vector_noerror 24
vector_noerror 25
vector_noerror 26
vector_noerror 27
vector_noerror 28
vector_noerror 29
vector_error 30
vector_noerror 31

vector_noerror 32
vector_noerror 33
vector_noerror 34
vector_noerror 35
vector_noerror 36
vector_noerror 37
vector_noerror 38
vector_noerror 39
vector_noerror 40
vector_noerror 41
vector_noerror 42
vector_noerror 43
vector_noerror 44
vector_noerror 45
vector_noerror 46
vector_noerror 47

;;;;;;;;;;;;;;;;;;;;

section .data

global int_vector_table
int_vector_table:
%assign i 0
%rep 48
	dq isr_%+i
%assign i i+1
%endrep