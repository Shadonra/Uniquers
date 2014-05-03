CC = g++
CFLAGS = -O2 -fpermissive

alg_1: alg_1.c alg_1.h
	$(CC) $(CFLAGS) -c alg_1.c alg_1.h

alg_2: alg_2.c utils.h
	$(CC) $(CFLAGS) utils.c alg_1.h alg_2.c

alg_3: alg_3.h utils.h
	$(CC) $(CFLAGS) -c rb.c utils.c alg_3.c

mktest: make_test.c
	$(CC) $(CFLAGS) make_test.c -o make_test

test_uniq: test_uniq.c test_uniq.h
	$(CC) $(CFLAGS) -c test_uniq.c test_uniq.h

test: test_uniq alg_1 alg_3
	$(CC) $(CFLAGS) -o test test_uniq.o alg_1.o alg_3.o rb.o utils.o

test_hash: test_hash.c utils.h
	$(CC) $(CFLAGS) -o test_hash test_hash.c && ./test_hash
