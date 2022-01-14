;;=============================================================
;; CS 2110 - Fall 2020
;; Homework 5 - Palindrome
;;=============================================================
;; Name:
;;=============================================================

;; Pseudocode (see PDF for explanation):
;;
;; string = "racecar";
;; len = 0;
;;
;; // to find the length of the string
;; while (string[len] != '\0') {
;;   len = len + 1;
;; }
;;
;; // to check whether the string is a palindrome
;; result = 1;
;; i = 0;
;; while (i < length) {
;;   if (string[i] != string[length - i - 1]) {
;;     result = 0;
;;     break;
;;   }
;;   i = i + 1;
;; }

.orig x3000

;; put your code here

HALT

ANSWER .blkw 1
STRING .fill x4000
.end

.orig x4000
.stringz "racecar"
.end
