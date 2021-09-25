#!/bin/sh
set -eux
make=../pmake-1.45-16/pmake-1.45/bmake
#make=bmake
${make} -r -f Makefile.boot
