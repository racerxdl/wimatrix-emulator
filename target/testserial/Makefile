CXXFLAGS=-I../hal -fPIC -g -rdynamic
LDFLAGS=-shared
PROJNAME = testserial
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

buildenv:
	@echo "Creating buildenv"
	@mkdir -p $(BUILDFOLDER)
	@cp -r *.cpp *.h $(BUILDFOLDER) 2>/dev/null || true;
	@echo "Creating $(CPPINONAME)"
	@cat ../hal/arduino.tpl $(INONAME) > $(BUILDFOLDER)/$(CPPINONAME)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $(BUILDFOLDER)/$(CPPINONAME:%.cpp=%.o) $(BUILDFOLDER)/$(CPPINONAME)

link: buildenv $(OBJECTS)
	@echo "Linking library"
	$(eval HAL_OBJECTS := $(shell find ../hal -name "*.o"))
	@$(CXX) $(LDFLAGS) $(HAL_OBJECTS) $(OBJECTS) -o $(BUILDFOLDER)/$(PROJNAME).so

clean:
	@echo "Erasing all build"
	@rm -fr build

.PHONY: clean hal link