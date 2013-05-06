# Makefile for all system servers.
#

.include <bsd.own.mk>

.if ${MKIMAGEONLY} == "yes"

SUBDIR=	ds init mfs pfs pm rs sched vfs vm semaphore

.else

SUBDIR=	ds ext2 inet init ipc is iso9660fs \
	mfs pfs pm procfs rs sched vfs vm devman semaphore

.if ${MACHINE_ARCH} == "i386"
SUBDIR+= hgfs vbfs
.endif

.endif

.include <bsd.subdir.mk>