BASE = ../


ODIR = $(BASE)obj/
CODE = $(BASE)src/
SYMBOL = $(CODE)Symbolic/
HEAD = $(CODE)header/
LEX = $(CODE)parser/
TOOLS = $(BASE)tools/
TEST = $(BASE)test/
EXTERN = $(BASE)extern/lib/

COFILE = $(ODIR)Pikachu.o $(ODIR)PikaType.o $(ODIR)Nodes.o $(ODIR)tensor.o 
SOFILE = $(ODIR)symbolic.o $(ODIR)SymbolicIR.o $(ODIR)expression.o $(ODIR)manifold.o
POFILE = $(ODIR)Pexp.o $(ODIR)LGsheet.o $(ODIR)parser.o $(ODIR)GUnit.o 
HFILE = $(HEAD)PikaType.h $(HEAD)PikaTemplate.h $(HEAD)Pikachu.h $(HEAD)Symbolic.h $(HEAD)parser.h
Extern = -lHyperlex -lHyperAlgebra
TestOFile = $(TEST)main.o $(TEST)test.o $(TEST)test_old.o 

#CC = icc -std=c++11
CC = g++ -std=c++11

#Option = -g 
Option ?= -O3


libHyperPes.a:  $(COFILE) $(SOFILE) $(POFILE)
	ar -rcv $(BASE)libHyperPes.a  $(COFILE) $(SOFILE) $(POFILE)

$(ODIR)Pikachu.o:$(CODE)network/Pikachu.cpp $(HFILE)
	$(CC) -o $(ODIR)Pikachu.o -c $(Option) $(CODE)network/Pikachu.cpp

$(ODIR)PikaType.o:$(CODE)tensors/PikaType.cpp $(HFILE)
	$(CC) -o $(ODIR)PikaType.o -c $(Option) $(CODE)tensors/PikaType.cpp

$(ODIR)Nodes.o:$(CODE)network/Nodes.cpp $(HFILE)
	$(CC) -o $(ODIR)Nodes.o -c $(Option) $(CODE)network/Nodes.cpp

$(ODIR)tensor.o:$(CODE)tensors/tensor.cpp $(HFILE)
	$(CC) -o $(ODIR)tensor.o -c $(Option) $(CODE)tensors/tensor.cpp

$(ODIR)symbolic.o:$(SYMBOL)symbolic.cpp $(HFILE)
	$(CC) -o $(ODIR)symbolic.o -c $(Option) $(SYMBOL)symbolic.cpp

$(ODIR)SymbolicIR.o:$(SYMBOL)SymbolicIR.cpp $(HFILE)
	$(CC) -o $(ODIR)SymbolicIR.o -c $(Option) $(SYMBOL)SymbolicIR.cpp

$(ODIR)expression.o:$(SYMBOL)expression.cpp $(HFILE)
	$(CC) -o $(ODIR)expression.o -c $(Option) $(SYMBOL)expression.cpp

$(ODIR)manifold.o:$(SYMBOL)manifold.cpp $(HFILE)
	$(CC) -o $(ODIR)manifold.o -c $(Option) $(SYMBOL)manifold.cpp

$(ODIR)Pexp.o:$(LEX)Pexp.cpp $(HFILE)
	$(CC) -o $(ODIR)Pexp.o -c $(Option) $(LEX)Pexp.cpp

$(ODIR)LGsheet.o:$(LEX)LGsheet.cpp $(HFILE)
	$(CC) -o $(ODIR)LGsheet.o -c $(Option) $(LEX)LGsheet.cpp

$(ODIR)parser.o:$(LEX)parser.cpp $(HFILE)
	$(CC) -o $(ODIR)parser.o -c $(Option) $(LEX)parser.cpp

$(ODIR)GUnit.o:$(LEX)GUnit.cpp $(HFILE)
	$(CC) -o $(ODIR)GUnit.o -c $(Option) $(LEX)GUnit.cpp

test.exe: $(COFILE) $(TestOFile) $(SOFILE) $(POFILE)   libHyperPes.a
	$(CC) -o $(TEST)test.exe $(TestOFile) -L$(BASE) -lHyperPes  -L$(EXTERN)  $(Extern)

$(TEST)main.o: $(HFILE) $(TEST)main.cpp $(TEST)extern.h
	$(CC) -o $(TEST)main.o -c $(Option) $(TEST)main.cpp

$(TEST)test.o: $(HFILE) $(TEST)test.cpp $(TEST)extern.h
	$(CC) -o $(TEST)test.o -c $(Option) $(TEST)test.cpp

$(TEST)test_old.o: $(HFILE) $(TEST)test_old.cpp $(TEST)extern.h
	$(CC) -o $(TEST)test_old.o -c $(Option) $(TEST)test_old.cpp

.PHONY: clean
clean:
	rm $(ODIR)*.o
	rm $(TEST)*.o
	rm $(BASE)extern/obj/*.o
	rm $(BASE)extern/lib/*.a





