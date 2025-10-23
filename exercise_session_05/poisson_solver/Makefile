CXX       := g++
CXXFLAGS  := -O3 -ffast-math -march=native -fopenmp
LDFLAGS   := -fopenmp
TARGET    := main
OBJS      := main.o init.o io.o jacobi.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
