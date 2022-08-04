JerryBoree:MultiValueHashTable.o Jerry.o HashTable.o JerryBoreeMain.o KeyValuePair.o LinkedList.o 
	gcc MultiValueHashTable.o Jerry.o HashTable.o KeyValuePair.o LinkedList.o JerryBoreeMain.o -o JerryBoree
Jerry.o: Jerry.c Jerry.h Defs.h
	gcc -c Jerry.c
HashTable.o: HashTable.c HashTable.h Defs.h LinkedList.h KeyValuePair.h Jerry.h
	gcc -c HashTable.c
KeyValuePair.o: KeyValuePair.c KeyValuePair.h Defs.h
	gcc -c KeyValuePair.c
LinkedList.o: LinkedList.c LinkedList.h Defs.h KeyValuePair.h
	gcc -c LinkedList.c
MultiValueHashTable.o: MultiValueHashTable.c MultiValueHashTable.h Defs.h HashTable.h KeyValuePair.h Defs.h Jerry.h LinkedList.h
	gcc -c MultiValueHashTable.c
JerryBoreeMain.o: JerryBoreeMain.c Defs.h HashTable.h KeyValuePair.h MultiValueHashTable.h LinkedList.h Jerry.h
	gcc -c JerryBoreeMain.c
clean:
	rm -f *.o
