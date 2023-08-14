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
	pushaq
	cld
	mov rdi, rsp
	push 0 ; stack alignment
	call int_handler
	popaq
	add rsp, 24
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

vector_noerror 48
vector_noerror 49
vector_noerror 50
vector_noerror 51
vector_noerror 52
vector_noerror 53
vector_noerror 54
vector_noerror 55
vector_noerror 56
vector_noerror 57
vector_noerror 58
vector_noerror 59
vector_noerror 60
vector_noerror 61
vector_noerror 62
vector_noerror 63
vector_noerror 64
vector_noerror 65
vector_noerror 66
vector_noerror 67
vector_noerror 68
vector_noerror 69
vector_noerror 70
vector_noerror 71
vector_noerror 72
vector_noerror 73
vector_noerror 74
vector_noerror 75
vector_noerror 76
vector_noerror 77
vector_noerror 78
vector_noerror 79
vector_noerror 80
vector_noerror 81
vector_noerror 82
vector_noerror 83
vector_noerror 84
vector_noerror 85
vector_noerror 86
vector_noerror 87
vector_noerror 88
vector_noerror 89
vector_noerror 90
vector_noerror 91
vector_noerror 92
vector_noerror 93
vector_noerror 94
vector_noerror 95
vector_noerror 96
vector_noerror 97
vector_noerror 98
vector_noerror 99
vector_noerror 100
vector_noerror 101
vector_noerror 102
vector_noerror 103
vector_noerror 104
vector_noerror 105
vector_noerror 106
vector_noerror 107
vector_noerror 108
vector_noerror 109
vector_noerror 110
vector_noerror 111
vector_noerror 112
vector_noerror 113
vector_noerror 114
vector_noerror 115
vector_noerror 116
vector_noerror 117
vector_noerror 118
vector_noerror 119
vector_noerror 120
vector_noerror 121
vector_noerror 122
vector_noerror 123
vector_noerror 124
vector_noerror 125
vector_noerror 126
vector_noerror 127
vector_noerror 128
vector_noerror 129
vector_noerror 130
vector_noerror 131
vector_noerror 132
vector_noerror 133
vector_noerror 134
vector_noerror 135
vector_noerror 136
vector_noerror 137
vector_noerror 138
vector_noerror 139
vector_noerror 140
vector_noerror 141
vector_noerror 142
vector_noerror 143
vector_noerror 144
vector_noerror 145
vector_noerror 146
vector_noerror 147
vector_noerror 148
vector_noerror 149
vector_noerror 150
vector_noerror 151
vector_noerror 152
vector_noerror 153
vector_noerror 154
vector_noerror 155
vector_noerror 156
vector_noerror 157
vector_noerror 158
vector_noerror 159
vector_noerror 160
vector_noerror 161
vector_noerror 162
vector_noerror 163
vector_noerror 164
vector_noerror 165
vector_noerror 166
vector_noerror 167
vector_noerror 168
vector_noerror 169
vector_noerror 170
vector_noerror 171
vector_noerror 172
vector_noerror 173
vector_noerror 174
vector_noerror 175
vector_noerror 176
vector_noerror 177
vector_noerror 178
vector_noerror 179
vector_noerror 180
vector_noerror 181
vector_noerror 182
vector_noerror 183
vector_noerror 184
vector_noerror 185
vector_noerror 186
vector_noerror 187
vector_noerror 188
vector_noerror 189
vector_noerror 190
vector_noerror 191
vector_noerror 192
vector_noerror 193
vector_noerror 194
vector_noerror 195
vector_noerror 196
vector_noerror 197
vector_noerror 198
vector_noerror 199
vector_noerror 200
vector_noerror 201
vector_noerror 202
vector_noerror 203
vector_noerror 204
vector_noerror 205
vector_noerror 206
vector_noerror 207
vector_noerror 208
vector_noerror 209
vector_noerror 210
vector_noerror 211
vector_noerror 212
vector_noerror 213
vector_noerror 214
vector_noerror 215
vector_noerror 216
vector_noerror 217
vector_noerror 218
vector_noerror 219
vector_noerror 220
vector_noerror 221
vector_noerror 222
vector_noerror 223
vector_noerror 224
vector_noerror 225
vector_noerror 226
vector_noerror 227
vector_noerror 228
vector_noerror 229
vector_noerror 230
vector_noerror 231
vector_noerror 232
vector_noerror 233
vector_noerror 234
vector_noerror 235
vector_noerror 236
vector_noerror 237
vector_noerror 238
vector_noerror 239
vector_noerror 240
vector_noerror 241
vector_noerror 242
vector_noerror 243
vector_noerror 244
vector_noerror 245
vector_noerror 246
vector_noerror 247
vector_noerror 248
vector_noerror 249
vector_noerror 250
vector_noerror 251
vector_noerror 252
vector_noerror 253
vector_noerror 254
vector_noerror 255

;;;;;;;;;;;;;;;;;;;;

section .data

global int_vector_table
int_vector_table:
%assign i 0
%rep 256
	dq isr_%+i
%assign i i+1
%endrep