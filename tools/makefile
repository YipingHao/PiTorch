BASE = ../


ODIR = $(BASE)obj/
CODE = $(BASE)code/
TOOLS = $(BASE)tools/
TEST = $(BASE)test/
EXTERN = $(BASE)extern/lib/

COFILE = $(ODIR)Pikachu.o $(ODIR)PikaType.o $(ODIR)Nodes.o $(ODIR)tensor.o 
SOFILE = $(ODIR)symbolic.o $(ODIR)SymbolicIR.o $(ODIR)expression.o $(ODIR)manifold.o
HFILE = $(CODE)PikaType.h $(CODE)PikaTemplate.h $(CODE)Pikachu.h $(CODE)Symbolic.h
Extern = -lHyperAcc -lHyperAlgebra
TestOFile = $(TEST)main.o

#Option = -g
Option = -O3


libHyperPes.a:  $(COFILE) $(SOFILE) 
	ar -rcv $(BASE)libHyperPes.a  $(COFILE) $(SOFILE) 

#$(ODIR)formula.o:$(CODE)formula.cpp $(CODE)pes.h
#	g++ -o $(ODIR)formula.o -c -O3 $(CODE)formula.cpp

$(ODIR)Pikachu.o:$(CODE)Pikachu.cpp $(HFILE)
	g++ -o $(ODIR)Pikachu.o -c $(Option) $(CODE)Pikachu.cpp

$(ODIR)PikaType.o:$(CODE)PikaType.cpp $(HFILE)
	g++ -o $(ODIR)PikaType.o -c $(Option) $(CODE)PikaType.cpp

$(ODIR)Nodes.o:$(CODE)Nodes.cpp $(HFILE)
	g++ -o $(ODIR)Nodes.o -c $(Option) $(CODE)Nodes.cpp

$(ODIR)tensor.o:$(CODE)tensor.cpp $(HFILE)
	g++ -o $(ODIR)tensor.o -c $(Option) $(CODE)tensor.cpp

$(ODIR)symbolic.o:$(CODE)symbolic.cpp $(HFILE)
	g++ -o $(ODIR)symbolic.o -c $(Option) $(CODE)symbolic.cpp

$(ODIR)SymbolicIR.o:$(CODE)SymbolicIR.cpp $(HFILE)
	g++ -o $(ODIR)SymbolicIR.o -c $(Option) $(CODE)SymbolicIR.cpp

$(ODIR)expression.o:$(CODE)expression.cpp $(HFILE)
	g++ -o $(ODIR)expression.o -c $(Option) $(CODE)expression.cpp

$(ODIR)manifold.o:$(CODE)manifold.cpp $(HFILE)
	g++ -o $(ODIR)manifold.o -c $(Option) $(CODE)manifold.cpp

test.exe: $(COFILE) $(TestOFile) $(SOFILE) libHyperPes.a
	g++ -o $(TEST)test.exe $(TestOFile) -L$(BASE) -lHyperPes -L$(EXTERN)  $(Extern)

$(TEST)main.o: $(HFILE) $(TEST)main.cpp
	g++ -o $(TEST)main.o -c $(Option) $(TEST)main.cpp




.PHONY: clean
clean:
	rm $(ODIR)*.o
	rm $(TEST)*.o







