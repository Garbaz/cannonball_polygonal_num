progname=cannonball_polygonal_num
builddir=build
srcdir=src
libs=-lgmp

.PHONY: build clean

default: build

build:
	if [ ! -e ${builddir} ];then mkdir ${builddir};fi
	gcc ${libs} -O3 -o ${builddir}/${progname} ${srcdir}/${progname}.c
clean:
	rm build/*
