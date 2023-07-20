gatorgit: main.c gatorgit.c gatorgit.h util.h
	gcc -ggdb -std=c99 main.c gatorgit.c -o gatorgit

clean:
	rm -rf gatorgit autotest test

check::
	python2.7 tester.pyc gatorgit.c