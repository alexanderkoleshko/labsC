TARGET = lab.exe
CC = gcc

.PHONY: edit run clean install uninstall valgrind

edit: $(TARGET)		 
	
PriorBank.o: PriorBank.c PriorBank.h
				$(CC) -c PriorBank.c
PriorSource.o: PriorSource.c PriorSource.h
				$(CC) -c PriorSource.c
List.o: List.c List.h
				$(CC) -c List.c
Check.o: Check.c Check.h
				$(CC) -c Check.c

a.out: PriorBank.c PriorSource.c List.c Check.c PriorBank.h PriorSource.h List.h Check.h
	gcc -g PriorBank.c PriorSource.c List.c Check.c

$(TARGET): PriorBank.o PriorSource.o List.o Check.o
				$(CC) -o $(TARGET) PriorBank.o PriorSource.o List.o Check.o
valgrind: a.out
	valgrind -q ./a.out	
	
splint:
	splint *.c
clean:
			@rm -rf $(TARGET) *.o *.i *.s *.gch *.out *.exe
install: $(TARGET) 
			install $(TARGET) /
run:
			$(TARGET)
uninstall:
			@rm -rf /$(TARGET)