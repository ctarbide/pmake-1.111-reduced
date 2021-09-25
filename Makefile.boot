#	$NetBSD: Makefile.boot,v 1.17 2004/05/07 00:04:38 ross Exp $
#
# a very simple makefile...
#
# You only want to use this if you aren't running NetBSD.
#
# modify MACHINE and MACHINE_ARCH as appropriate for your target architecture
#

.SUFFIXES: .o .c

CC=gcc -O -g

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

MACHINE=i386
MACHINE_ARCH=i386
# tested on HP-UX 10.20
#MAKE_MACHINE=hp700
#MAKE_MACHINE_ARCH=hppa
CFLAGS= -DTARGET_MACHINE=\"${MACHINE}\" \
	-DTARGET_MACHINE_ARCH=\"${MACHINE_ARCH}\" \
	-DMAKE_MACHINE=\"${MACHINE}\" \
	-DHAVE_STRERROR \
	-DHAVE_STRDUP \
	-DMAKE_NATIVE \
	-D'__RCSID(_)=' \
	-D'__COPYRIGHT(_)='

LIBS=

OBJ=arch.o buf.o compat.o cond.o dir.o for.o hash.o job.o main.o make.o \
    parse.o str.o suff.o targ.o trace.o var.o util.o

LIBOBJ= lst.o

bmake: ${OBJ} ${LIBOBJ}
#	@echo 'make of make and make.0 started.'
	${CC} ${CFLAGS} ${OBJ} ${LIBOBJ} -o bmake ${LIBS}
	@ls -l $@
#	nroff -h -man make.1 > make.0
#	@echo 'make of make and make.0 completed.'

clean:
	rm -f ${OBJ} ${LIBOBJ} ${PORTOBJ} bmake
