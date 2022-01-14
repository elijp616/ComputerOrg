;; Timed Lab 3
;; Student Name:

;; Please read the PDF for full directions.
;; The pseudocode for the program you must implement is listed below; it is also listed in the PDF.
;; If there are any discrepancies between the PDF's pseudocode and the pseudocode below, notify a TA on Piazza quickly.
;; However, in the end, the pseudocode is just an example of a program that would fulfill the requirements specified in the PDF.

;; Pseudocode:
;;
;; ABS(x) {
;;     if (x < 0) {
;;         return -x;
;;     } else {
;;         return x;
;;     }
;; }
;;
;;
;;
;; POW3(x) {
;;     if (x == 0) {
;;         return 1;
;;     } else {
;;         return 3 * POW3(x - 1);
;;     }
;; }
;;
;;
;; MAP(array, length) {
;;     i = 0;
;;     while (i < length) {
;;         element = arr[i];
;;         if (i & 1 == 0) {
;;             result = ABS(element);
;;         } else {
;;             result = POW3(element);
;;         }
;;         arr[i] = result;
;;         i++;
;;     }
;; }

.orig x3000

HALT

STACK .fill xF000

; DO NOT MODIFY ABOVE


; START ABS SUBROUTINE
ABS
ADD R6, R6, -4;
STR R5, R6, 1; Store Old R5
AND R5, R5, 0;
ADD R5, R6, 0; Setting new R5

STR R7, R5, 2; Store old R7

 
ADD R6, R6, -1; Saving Registers
STR R0, R6, 0;
ADD R6, R6, -1;
STR R1, R6, 0;
ADD R6, R6, -1;
STR R2, R6, 0;
ADD R6, R6, -1;
STR R3, R6, 0;
ADD R6, R6, -1;
STR R4, R6, 0;

LDR R0, R5, 4;
BRzp STOP1;
NOT R0, R0;
ADD R0, R0, 1;

STOP1
STR R0, R5, 3;
LDR R4, R6, 0; Recover registers
ADD R6, R6, 1;
LDR R3, R6, 0;
ADD R6, R6, 1;
LDR R2, R6, 0;
ADD R6, R6, 1;
LDR R1, R6, 0;
ADD R6, R6, 1;
LDR R0, R6, 0;
ADD R6, R6, 1;
LDR R7, R5, 2;
ADD R6, R5, 3;
LDR R5, R5, 1;



    ; !!!!! WRITE YOUR CODE HERE !!!!!



RET
; END ABS SUBROUTINE




; START POW3 SUBROUTINE
POW3
ADD R6, R6, -4;
STR R5, R6, 1; Store Old R5
AND R5, R5, 0;
ADD R5, R6, 0; Setting new R5

STR R7, R5, 2; Store old R7

 
ADD R6, R6, -1; Saving Registers
STR R0, R6, 0;
ADD R6, R6, -1;
STR R1, R6, 0;
ADD R6, R6, -1;
STR R2, R6, 0;
ADD R6, R6, -1;
STR R3, R6, 0;
ADD R6, R6, -1;
STR R4, R6, 0;

LDR R0, R5, 4;
BRp RECURSIVE;
ADD R0, R0, 1;
STR R0, R5, 3;
BRnzp STOP2;

RECURSIVE
ADD R6, R6, -1;
ADD R0, R0, -1;
STR R0, R6, 0;
JSR POW3;
LDR R0, R6, 0;
ADD R6, R6, 2;
ADD R1, R0, R0;
ADD R0, R1, R0;
STR R0, R5, 3;
BRnzp STOP2;

STOP2
LDR R4, R6, 0; Recover registers
ADD R6, R6, 1;
LDR R3, R6, 0;
ADD R6, R6, 1;
LDR R2, R6, 0;
ADD R6, R6, 1;
LDR R1, R6, 0;
ADD R6, R6, 1;
LDR R0, R6, 0;
ADD R6, R6, 1;
LDR R7, R5, 2;
ADD R6, R5, 3;
LDR R5, R5, 1;

    ; !!!!! WRITE YOUR CODE HERE !!!!!



RET
; END POW3 SUBROUTINE




; START MAP SUBROUTINE
MAP

ADD R6, R6, -4;
STR R5, R6, 1; Store Old R5
AND R5, R5, 0;
ADD R5, R6, 0; Setting new R5

STR R7, R5, 2; Store old R7

ADD R6, R6, -1; Spare space for element.
ADD R6, R6, -1; Spare space for result
ADD R6, R6, -1; Saving Registers
STR R0, R6, 0;
ADD R6, R6, -1;
STR R1, R6, 0;
ADD R6, R6, -1;
STR R2, R6, 0;
ADD R6, R6, -1;
STR R3, R6, 0;
ADD R6, R6, -1;
STR R4, R6, 0;

AND R0, R0, 0;
STR R0, R5, 0;

LOOP
LDR R0, R5, 0;  i in R0
NOT R0, R0;
ADD R0, R0, 1;
LDR R1, R5, 5;
ADD R1, R1, R0;
BRnz STOP3

LDR R0, R5, 0;
LDR R1, R5, 4;
ADD R1, R1, R0;
LDR R1, R1, 0;  element in R1
STR R1, R5, -1;
AND R2, R2, 0;
ADD R2, R2, 1; create mask
AND R2, R1, R2;
BRp ALTER

ADD R6, R6, -1;
LDR R1, R5, -1;
STR R1, R6, 0;
JSR ABS;
LDR R3, R6, 0;
ADD R6, R6, 2;
STR R3, R5, -2;

BRnzp OUTLOOP

ALTER
ADD R6, R6, -1;
STR R1, R6, 0;
JSR POW3;
LDR R3, R6, 0;
ADD R6, R6, 2;
STR R3, R5, -2;


OUTLOOP
LDR R0, R5, 0;
LDR R3, R5, -2;
LDR R2, R5, 4;
ADD R2, R2, R0;
STR R3, R2, 0;
ADD R0, R0, 1;
STR R0, R5, 0;
BRnzp LOOP


STOP3
LDR R4, R6, 0; Recover registers
ADD R6, R6, 1;
LDR R3, R6, 0;
ADD R6, R6, 1;
LDR R2, R6, 0;
ADD R6, R6, 1;
LDR R1, R6, 0;
ADD R6, R6, 1;
LDR R0, R6, 0;
ADD R6, R6, 1;

LDR R7, R5, 2;
ADD R6, R5, 3;
LDR R5, R5, 1;




    ; !!!!! WRITE YOUR CODE HERE !!!!!



RET
; END MAP SUBROUTINE


; ARRAY FOR TESTING
ARRAY .fill x4000
.end

.orig x4000
.fill -2
.fill 5
.fill 3
.fill 2
.fill -6
.fill 0
.end
