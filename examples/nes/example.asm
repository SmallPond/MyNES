
; header
.segment "NES_FILE_HEADER"
.byte "NES", $1A, 2

;code, 实现 4+2的操作
.segment "CODE"
main:
    LDA #$4       ;立即数寻址模式，将1放入到A寄存器中
    ADC #$2

;中断向量
.segment "INTERRUPT_VECTOR"
    .word main, main, main