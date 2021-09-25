#!/bin/sh

set -eu

MACHINE=`uname -m`
MACHINE_ARCH=`uname -p`

CC=gcc

CFLAGS="-O -g"
CFLAGS="${CFLAGS} "'-DTARGET_MACHINE="'"${MACHINE}"'"'
CFLAGS="${CFLAGS} "'-DTARGET_MACHINE_ARCH="'"${MACHINE_ARCH}"'"'
CFLAGS="${CFLAGS} "'-DMAKE_MACHINE="'"${MACHINE}"'"'
CFLAGS="${CFLAGS} -D__RCSID(_)="
CFLAGS="${CFLAGS} -D__COPYRIGHT(_)="
CFLAGS="${CFLAGS} -DHAVE_STRERROR"
CFLAGS="${CFLAGS} -DHAVE_STRDUP"
CFLAGS="${CFLAGS} -DMAKE_NATIVE"

set -x

# compile
${CC} ${CFLAGS} -c lst.c -o lst.o
${CC} ${CFLAGS} -c pmake.c -o pmake.o

# load/link
${CC} ${CFLAGS} lst.o pmake.o -o pmake
