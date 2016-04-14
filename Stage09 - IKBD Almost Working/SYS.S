	xdef	_get_video_base
	xdef	_set_video_base
	xdef	_vbl_isr
	xdef	_ikbd_isr
	xdef	_set_ipl
	
	xref	_do_VBL_ISR
	xref	_do_IKBD_ISR

ADDR_OFFSET	equ	8

super_on:
	move.l	d0,-(sp)
	
	clr.l	-(sp)
	move.w	#$20,-(sp)
	trap	#1
	addq.l	#6,sp
	
	move.l d0,old_ssp
	move.l	(sp)+,d0
	rts
	
super_off:
	move.l	d0,-(sp)
	
	move.l	(old_ssp),-(sp)
	move.w	#$20,-(a7)
	trap	#1
	addq.l	#6,sp
	
	move.l	(sp)+,d0
	rts
	
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
	
	
_vbl_isr:
	movem.l	d0-2/a0-2,-(sp)
	jsr	_do_VBL_ISR
	movem.l	(sp)+,d0-2/a0-2
	rte
	
_ikbd_isr:
	jsr	_do_IKBD_ISR

	lea $FFFFFA11,a0    ; Clear bit #6 of In-Service B Register
	move.b  #$BF,(a0)

	rte
	
	
_set_ipl: 
	move.w	sr,d0
	move.w	d0,-(sp) 
	
	lsr.w	#8,d0 
	and.w	#$0007,d0 
	
	andi.w	#$F8FF,(sp)
	move.w	d1,-(sp)
	move.w	8(sp),d1 
	lsl.w	#8,d1
	and.w	#$0700,d1
	or.w	d1,2(sp) 
	move.w	(sp)+,d1
	
	rte

	
old_ssp:	ds.l	1