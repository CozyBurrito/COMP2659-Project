	xdef	_phys


ADDR	equ	8


_phys:	link	a6,#0
	movem.l	d0-1/a0-1,-(sp)
		
	clr.l 	d0
	clr.l 	d1
		
	movem.l	(sp)+,d0-1/a0-1
	unlk	a6
	rts
