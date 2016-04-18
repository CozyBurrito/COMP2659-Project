	xdef	_vbl_isr
	xdef 	_ikbd_isr
	
	xref	_do_VBL_ISR
	xref 	_do_IKBD_ISR
	
_ikbd_isr:
	movem.l d0-2/a0-2,-(sp)
	jsr _do_IKBD_ISR
	movem.l (sp)+,d0-2/a0-2
	rte
	
_vbl_isr:
	movem.l	d0-2/a0-2,-(sp)
	jsr	_do_VBL_ISR
	movem.l	(sp)+,d0-2/a0-2
	rte