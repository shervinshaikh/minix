.include <bsd.own.mk>

# Makefile for Semaphore
PROG=	semaphore
SRCS=	main.c

DPADD+=	${LIBSYS} ${LIBTIMERS}
LDADD+=	-lsys -ltimers

MAN=

BINDIR?= /usr/sbin

CPPFLAGS.main.c+=	-I${NETBSDSRCDIR}

.include <minix.bootprog.mk>