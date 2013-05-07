PROG=	sema
SRCS=	semaphore.c

DPADD+=	${LIBSYS} ${LIBTIMERS}
LDADD+=	-lsys -ltimers

MAN=

BINDIR?= /usr/sbin

CPPFLAGS.semaphore.c+=	-I${NETBSDSRCDIR}

.include <minix.bootprog.mk>