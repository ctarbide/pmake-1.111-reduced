#!/bin/sh
set -eux
die(){ ev=$1; shift; for msg in "$@"; do echo "${msg}"; done; exit "${ev}"; }
git diff --quiet || die 1 'error: working tree not in pristine state'
git status --porcelain | perl -lane'exit(1) if m{^\?\? }}{' || die 1 'error: unknown git files are present'
git clean -dxf
rm -fv *.h *.c
nofake -Rextract.sh *.nw | sh
exec ./build.sh
