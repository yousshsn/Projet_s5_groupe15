main: readelf.c print.o read.o
	gcc -o readelf readelf.c print.o read.o

print.o: print.c print.h
	gcc -c print.c

reader.o: read.c read.h
	gcc -c read.c

clean:
	rm *.o readelf
