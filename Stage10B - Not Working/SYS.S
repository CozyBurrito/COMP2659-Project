;   Name: Don Hagen, Mohammad Hameed
;   Course: COMP 2659
;   Due Date: 15/04/2016
;   Instructor: ppospisil

	xdef	_get_video_base
	xdef	_set_video_base

ADDR_OFFSET	equ	8

;enter supervisor mode
;needed to access protected memory
super_on:
	move.l	d0,-(sp)
	
	clr.l	-(sp)
	move.w	#$20,-(sp)
	trap	#1
	addq.l	#6,sp
	
	move.l d0,old_ssp
	move.l	(sp)+,d0
	rts

;leave supervisor mode 
;can no longer access protected memory	
super_off:
	move.l	d0,-(sp)
	
	move.l	(old_ssp),-(sp)
	move.w	#$20,-(a7)
	trap	#1
	addq.l	#6,sp
	
	move.l	(sp)+,d0
	rts
	
;get the video base from memory,
;puts the address into d0 	
_get_video_base:
	move.l	a0,-(sp)
	
	clr.l	d0
	
	jsr	super_on
	
	lea	$FFFF8201,a0
	movep.w	(a0),d0
	lsl.l	#$8,d0
	
	jsr	super_off
	
	move.l	(sp)+,a0
	rts

;set up stack pointer
;save registers
;enter supervisor mode 
;move value at offset location of a6 to d0 
_set_video_base:
	link	a6,#0
	movem.l	d0-2/a0-2,-(sp)
	
	jsr super_on
	
	move.l	ADDR_OFFSET(a6),d0
	lsr.l	#8,d0
	lea	$FFFF8201,a0	
	movep.w	d0,0(a0)
	
	jsr	super_off
	
	movem.l	(sp)+,d0-2/a0-2
	unlk a6
	rts
	
	
old_ssp:	ds.l	1