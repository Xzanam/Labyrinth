MVI A, 80H ; All ports are O/P
OUT 43H
MVI A, 88H ; Initial control bit pattern
LOOP: OUT 40H
CALL DELAY ; Delay between steps
RRC ; Change RRC to RLC to reverse the direction
JMP LOOP
DELAY subroutine gives an approx. delay of 1.5s.
DELAY: PUSH PSW
LXI D, FFFFH
DLAY1: DCX D
MOV A, D
ORA E
JNZ DLAY1
POP PSW
RET