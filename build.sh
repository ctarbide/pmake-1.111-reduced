#!/bin/sh

set -eu

CC=gcc

CFLAGS="-Wall -O -g -Wmissing-prototypes -Wmissing-declarations -Wdeclaration-after-statement"
CFLAGS="${CFLAGS} -DHAVE_STRERROR"
CFLAGS="${CFLAGS} -DHAVE_STRDUP"
CFLAGS="${CFLAGS} -DMAKE_NATIVE"

set -x

# compile
${CC} ${CFLAGS} -c lst.c -o lst.o
${CC} ${CFLAGS} -c pmake.c -o pmake.o

# load/link
${CC} ${CFLAGS} lst.o pmake.o -o pmake
