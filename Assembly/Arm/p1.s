
.global _start
_start:
	
/*	3) int i=0;
int sum=0;
for(i=0;i<10;i++){
      sum += i;
}    */
	MOV R0,#0
	MOV R1,#0
	LOOP: ADD R1,R1,R0
	 ADD R0,R0,#1
	 CMP R0,#10
	 BNE LOOP
	 STR R1,RESULT
RESULT: .WORD 0
