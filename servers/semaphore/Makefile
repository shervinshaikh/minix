.include <bsd.own.mk>

# Makefile for Semaphore
PROG=	semaphore
SRCS=	semaphore.c

DPADD+=	${LIBSYS} ${LIBTIMERS}
LDADD+=	-lsys -ltimers

MAN=

BINDIR?= /usr/sbin

.include <minix.bootprog.mk>