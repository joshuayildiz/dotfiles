bin/align: bin/align.o
	9l -o $target $prereq

bin/align.o: bin/align.c
	9c -o $target $prereq

bin/tblfmt: bin/tblfmt.o
	9l -o $target $prereq

bin/tblfmt.o: bin/tblfmt.c
	9c -o $target $prereq
