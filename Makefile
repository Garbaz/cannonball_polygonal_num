progname=cannonball_polygonal_num
builddir=build
srcdir=src

.PHONY: build clean

default: build

build:
	if [ ! -e ${builddir} ];then mkdir ${builddir};fi
	gcc -O3 -o ${builddir}/${progname} ${srcdir}/${progname}.c
clean:
	rm build/*
