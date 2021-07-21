CC=gcc
CFLAGS=-g

all: part0 part1 part2 part3 part4 part5

part0: driver0.c memsets.c
	$(CC) $(CFLAGS) -o $@  $<
	@echo "===" $@ "==="
	./$@

part1: driver1.c memsets.c 
	@echo "==========="
	@echo "[TODO]:" $@   
	@echo "(1) Compile into objects files (driver1.o, memsets.o), and (2) link them into an output executable (part1)." 
	@echo "==========="
	@echo ""
	$ gcc -o part1 driver1.c memsets.c 

part2: driver1.c memsets.c
	@echo "==========="
	@echo "[TODO]:" $@ 
	@echo "(1) Compile into objects files, (2) package memsets.o into an archive (libmemsets.a), and"
	@echo "(3) link driver1.o object file into an output executable (part2)."
	@echo "==========="
	@echo ""
	$  gcc -c driver1.c memsets.c 
	$ ar -cvq libmemsets.a memsets.o
	$  gcc -o part2 driver1.o libmemsets.a

part3: driver1.c memsets.c
	@echo "==========="
	@echo "[TODO]" $@ 
	@echo "(1) Compile into objects files, (2) package memsets.o into an shared library (say libmemsets.so),"
	@echo "(3) compile driver1.c into an output executable (part3), and (4) dynamically link shared library to run the program."	
	@echo "==========="
	@echo ""
	$ gcc -c driver1.c memsets.c 
	$ gcc -shared -o libmemsets.so memsets.o
	$ gcc -o part3 driver1.o ./libmemsets.so

part4: driver4.c part3
	@echo "==========="
	@echo "[TODO]" $@ 
	@echo "This assignment is based on part3."
	@echo "Modify driver4.c to dynamically loading necessary functions from libmemsets.so (from part 3)"
	@echo "to replace functions names __replace_me__ and run the program."
	@echo "==========="
	@echo ""
	$ gcc -o part4 driver4.c -ldl

part5: part3
	@echo "==========="
	@echo "[TODO]" $@ 
	@echo "This assignment is based on part3."
	@echo "While you run the output executable from part3, you will intercept library loading (LD_PRELOAD)"
	@echo "to replace memset() from libc library to something else (e.g., memset1)."
	@echo "==========="
	@echo ""
	$ LD_PRELOAD=/mnt/c/Users/Juhi/Desktop/a1/libmemsets.so ./part3

clean:
	rm -f part? *.a *.o *.so

