CFLAGS=-I../hal -fPIC -rdynamic
PROJNAME = testserial
INONAME = $(PROJNAME).ino
CPPINONAME = $(INONAME:%.ino=%.cpp)
SOURCES = $(shell find . -name "*.cpp")
OBJECTS = $(SOURCES:%.cpp=%.o)

all: link

%.o: %.cpp
	@echo "Building $< -> $@"
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

hal:
	@echo "Building Hardware Abstraction Layer"
	@make -C ../hal

inofile:
	@echo "Creating $(CPPINONAME)"
	@cat ../hal/arduino.tpl $(INONAME) > $(CPPINONAME)
	@$(CXX) -c -o $(PROJNAME).o $(CFLAGS) $(CPPINONAME)

link: inofile $(OBJECTS)
	echo "Linking library"
	$(eval HAL_OBJECTS := $(shell find ../hal -name "*.o"))
	$(CXX) -shared $(HAL_OBJECTS) $(OBJECTS) -o $(PROJNAME).so

clean:
	@echo "Erasing all .o files"
	@rm -f *.o
	@echo "Erasing $(CPPINONAME)"
	@rm -f $(CPPINONAME)

.PHONY: clean hal inofile link