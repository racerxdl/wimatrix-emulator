CXXFLAGS=-I. -Wall -DSHARED -fPIC -g -rdynamic
CFLAGS=-fPIC

SOURCES = $(shell find . -name "*.cpp")
OBJECTS = $(SOURCES:%.cpp=%.o)

all: $(OBJECTS)

%.o: %.cpp
	@echo "Building $< -> $@"
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:
	@echo "Erasing all .o files"
	@rm $(shell find . -name "*.o")
