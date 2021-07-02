CXX       := g++
CXX_FLAGS := -O2 -Wall -Wextra -std=c++17 -pedantic -Wcast-align -Wunused -Wshadow -Wold-style-cast -Wpointer-arith -Wcast-qual -Wno-missing-braces

BIN     := bin
SRC     := src
INCLUDE := headers

LIBRARIES   :=
EXECUTABLE  := program


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) $^ -o $@ $(LIBRARIES)

create_dirs:
	@mkdir $(BIN)

clean:
	-rm $(BIN)/*
