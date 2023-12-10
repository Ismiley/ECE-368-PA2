WARNING = -Wall -Wshadow
ERROR = -Wvla
GCC = gcc -std=c99 -pedantic -O3 $(WARNING) $(ERROR) 
EXEC = pa2
OBJS = pa2.o

all: $(OBJS)
	$(GCC) $(OBJS) -o $(EXEC)

$(EXEC): $(OBJS)
	$(GCC) $(OBJS) -o $(EXEC)

%.o: %.c 
	$(GCC) -c $<

testall: test1 

test1: $(EXEC)
	./$(EXEC) -b examples/ops0.b outputs/tree_0.b

test2: $(EXEC)
	./$(EXEC) -b examples/ops1.b outputs/tree_1.b

testdup: $(EXEC)
	./$(EXEC) -b examples/ops1dup.b outputs/tree_dup.b

testBF: $(EXEC)
	./$(EXEC) examples/testBF.b

testE: $(EXEC)
	./$(EXEC) -e examples/tree0.b

testInvTree: $(EXEC)
	./$(EXEC) -e examples/invTree01.b

testE2: $(EXEC)
	./$(EXEC) -e examples/invalidtree2.b

memory: $(EXEC)
	valgrind --log-file=log1 --leak-check=full ./$(EXEC) -b examples/ops0.b outputs/tree_0.b

memoryE: $(EXEC)
	valgrind --log-file=logE --leak-check=full ./$(EXEC) -e examples/invalidtree2.b


clean: # remove all machine generated files
	rm -f pa2 *.o log*



