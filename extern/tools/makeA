BASE = ../


ODIR = $(BASE)obj/
CODE = $(BASE)src/
SYMBOL = $(CODE)/Symbolic/
HEAD = $(CODE)/header/
LEX = $(CODE)/lexical/
TOOLS = $(BASE)tools/
TEST = $(BASE)test/
EXTERN = $(BASE)extern/lib/

COFILE = $(ODIR)Pikachu.o $(ODIR)PikaType.o $(ODIR)Nodes.o $(ODIR)tensor.o 
SOFILE = $(ODIR)symbolic.o $(ODIR)SymbolicIR.o $(ODIR)expression.o $(ODIR)manifold.o
LOFILE = $(LEX)automata.o $(LEX)dictionary.o
HFILE = $(HEAD)PikaType.h $(HEAD)PikaTemplate.h $(HEAD)Pikachu.h $(HEAD)Symbolic.h
Extern = -lHyperlex -lHyperAlgebra
TestOFile = $(TEST)main.o

#Option = -g
Option = -O3


libHyperPes.a:  $(COFILE) $(SOFILE) 
	ar -rcv $(BASE)libHyperPes.a  $(COFILE) $(SOFILE) 

libHyperlex.a: $(LOFILE)
	ar -rcv $(EXTERN)libHyperlex.a  $(LOFILE) 

$(ODIR)automata.o:$(LEX)automata.cpp $(LEX)automata.h
	g++ -o $(ODIR)automata.o -c $(Option) $(LEX)automata.cpp

$(ODIR)dictionary.o:$(LEX)dictionary.cpp $(LEX)automata.h $(LEX)dictionary.h
	g++ -o $(ODIR)dictionary.o -c $(Option) $(LEX)dictionary.cpp

#$(ODIR)formula.o:$(CODE)formula.cpp $(CODE)pes.h
#	g++ -o $(ODIR)formula.o -c -O3 $(CODE)formula.cpp

$(ODIR)Pikachu.o:$(CODE)network/Pikachu.cpp $(HFILE)
	g++ -o $(ODIR)Pikachu.o -c $(Option) $(CODE)network/Pikachu.cpp

$(ODIR)PikaType.o:$(CODE)tensors/PikaType.cpp $(HFILE)
	g++ -o $(ODIR)PikaType.o -c $(Option) $(CODE)tensors/PikaType.cpp

$(ODIR)Nodes.o:$(CODE)network/Nodes.cpp $(HFILE)
	g++ -o $(ODIR)Nodes.o -c $(Option) $(CODE)network/Nodes.cpp

$(ODIR)tensor.o:$(CODE)tensors/tensor.cpp $(HFILE)
	g++ -o $(ODIR)tensor.o -c $(Option) $(CODE)tensors/tensor.cpp

$(ODIR)symbolic.o:$(SYMBOL)symbolic.cpp $(HFILE)
	g++ -o $(ODIR)symbolic.o -c $(Option) $(SYMBOL)symbolic.cpp

$(ODIR)SymbolicIR.o:$(SYMBOL)SymbolicIR.cpp $(HFILE)
	g++ -o $(ODIR)SymbolicIR.o -c $(Option) $(SYMBOL)SymbolicIR.cpp

$(ODIR)expression.o:$(SYMBOL)expression.cpp $(HFILE)
	g++ -o $(ODIR)expression.o -c $(Option) $(SYMBOL)expression.cpp

$(ODIR)manifold.o:$(SYMBOL)manifold.cpp $(HFILE)
	g++ -o $(ODIR)manifold.o -c $(Option) $(SYMBOL)manifold.cpp

test.exe: $(COFILE) $(TestOFile) $(SOFILE) libHyperPes.a $(ODIR)libHyperlex.a 
	g++ -o $(TEST)test.exe $(TestOFile) -L$(BASE) -lHyperPes  -L$(EXTERN)  $(Extern)

$(TEST)main.o: $(HFILE) $(TEST)main.cpp
	g++ -o $(TEST)main.o -c $(Option) $(TEST)main.cpp




.PHONY: clean
clean:
	rm $(ODIR)*.o
	rm $(TEST)*.o







