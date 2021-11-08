INT09: ;Reserved
	CLI
	PUSH AX
	PUSH BX
	PUSH DS
	MOV AX, 0XB800
	MOV DS, AX
	MOV BX, 138
	MOV BYTE [BX], 'I'
	ADD BX, 2
	MOV BYTE [BX], '0'
	ADD BX, 2
	MOV BYTE [BX], '9' 
	ADD BX, 4
	INC BYTE [BX] 
	POP DS
	POP BX
	POP AX
	STI
	IRET			;RETURN FROM INTERRUPT	






.CHARACTER_CODES_UPPERCASE:
DB 0X00, 0X1B, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', 0X08, 0X09 ;0X00-0X0F
DB 'Q','W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', 0X0D, 0x00, 'A', 'S'    ;0X10-0X1F
DB 'D','F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0x00, '|', 'Z', 'X', 'C', 'V'     ;0X20-0X2F
.CHARACTER_CODES_LOWERCASE:
DB 0X00, 0X1B, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0X08, 0X09 ;0X00-0X0F
DB 'q','w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0X0D, 0x00, 'a', 's'    ;0X10-0X1F
DB 'd','f', 'g', 'h', 'j', 'k', 'l', ';', 0x27, '`', 0x00, 0X5C, 'z', 'x', 'c', 'v'   ;0X20-0X2F
.CHARACTER_CODES_CTRL:
