OBJS = Chaos_game.o
default : chaos.exe

LIBS-CONFIG = -L "$$SFML_HOME/bin/" -lsfml-graphics-2 -lsfml-window-2 -lsfml-system-2
CFLAGS-CONFIG = -I "$$SFML_HOME/include"

chaos.exe : $(OBJS)
	g++ $^ -o $@ $(LIBS-CONFIG)

%.o : %.cpp $(HEADER_RELY)
	g++ -c $*.cpp -o $*.o $(CFLAGS-CONFIG)

# Debug
%.i : %.cpp $(HEADER_RELY)
	g++ -E $*.cpp -o $*.i $(CFLAGS-CONFIG)

# Debug
%.s : %.cpp $(HEADER_RELY)
	g++ -S $*.cpp -o $*.s $(CFLAGS-CONFIG)

.PHONY : run
run : chaos.exe
	./chaos

.PHONY : clean
clean :
	$(RM) src/*.o
	$(RM) chaos.exe
