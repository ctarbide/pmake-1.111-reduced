#!/bin/sh
set -eux
#make=${MAKE:-bmake}
make=${MAKE:-../pmake-1.45-16/pmake-1.45/bmake}
unset MAKE
${make} -r -f Makefile.boot
