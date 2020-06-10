FASTLED=../libraries/FastLED
FASTLED_SOURCES=$(shell find $(FASTLED) -name "*.cpp" 2>>/dev/null)
FASTLED_OBJECTS = $(FASTLED_SOURCES:%.cpp=%.o)

CXXFLAGS=-D__EMULATOR__ -g -include ../hal/arduino.h -I../hal -I../ -I$(FASTLED) -fPIC -g -rdynamic
LDFLAGS=-shared
PROJNAME = testled
INONAME = $(PROJNAME).ino
BUILDFOLDER=./build
CPPINONAME = $(INONAME:%.ino=%.cpp)
SOURCES = $(shell find $(BUILDFOLDER) -name "*.cpp" 2>>/dev/null)
OBJECTS = $(SOURCES:%.cpp=%.o)

all: buildenv link

%.o: %.cpp
	@echo "Building $< -> $@"
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

hal:
	@echo "Building Hardware Abstraction Layer"
	@make -C ../hal

fastled: $(FASTLED_OBJECTS)
	@echo "Compiling FASTLED"

buildenv:
	@echo "Creating buildenv"
	@mkdir -p $(BUILDFOLDER)
	@cp -r *.cpp *.h $(BUILDFOLDER) 2>/dev/null || true;
	@echo "Creating $(CPPINONAME)"
	@cat ../hal/arduino.tpl $(INONAME) > $(BUILDFOLDER)/$(CPPINONAME)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $(BUILDFOLDER)/$(CPPINONAME:%.cpp=%.o) $(BUILDFOLDER)/$(CPPINONAME)

link: buildenv $(OBJECTS) $(FASTLED_OBJECTS)
	@echo "Linking library"
	$(eval HAL_OBJECTS := $(shell find ../hal -name "*.o"))
	@$(CXX) $(LDFLAGS) $(HAL_OBJECTS) $(OBJECTS) $(FASTLED_OBJECTS) -o $(BUILDFOLDER)/$(PROJNAME).so

clean:
	@echo "Erasing all build"
	@rm -fr build
	@rm -f $(FASTLED_OBJECTS)

.PHONY: clean hal link fastled