
MQTT=../libraries/MQTT/src/
MQTT_SOURCES=$(shell find $(MQTT) -name "*.cpp" 2>>/dev/null)
MQTT_CSOURCES=$(shell find $(MQTT) -name "*.c" 2>>/dev/null)
MQTT_OBJECTS = $(MQTT_SOURCES:%.cpp=%.o)
MQTT_COBJECTS = $(MQTT_CSOURCES:%.c=%.co)

CXXFLAGS=-I../hal -I$(MQTT) -fPIC -g -rdynamic
CFLAGS=-I../hal -I$(MQTT) -fPIC -g -rdynamic
LDFLAGS=-shared
PROJNAME = testmqtt
INONAME = $(PROJNAME).ino
BUILDFOLDER=./build
CPPINONAME = $(INONAME:%.ino=%.cpp)
SOURCES = $(shell find $(BUILDFOLDER) -name "*.cpp" 2>>/dev/null)
OBJECTS = $(SOURCES:%.cpp=%.o)

all: buildenv link

%.o: %.cpp
	@echo "Building C++ $< -> $@"
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

%.co: %.c
	@echo "Building C $< -> $@"
	@$(CC) $(CFLAGS) -c -o $@ $<

hal:
	@echo "Building Hardware Abstraction Layer"
	@make -C ../hal


mqtt: $(MQTT_OBJECTS) $(MQTT_COBJECTS)
	@echo "Compiling MQTT"
	@echo $(MQTT_SOURCES)
	@echo $(MQTT_OBJECTS)
	@echo $(MQTT_COBJECTS)

buildenv:
	@echo "Creating buildenv"
	@mkdir -p $(BUILDFOLDER)
	@cp -r *.cpp *.h $(BUILDFOLDER) 2>/dev/null || true;
	@echo "Creating $(CPPINONAME)"
	@cat ../hal/arduino.tpl $(INONAME) > $(BUILDFOLDER)/$(CPPINONAME)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $(BUILDFOLDER)/$(CPPINONAME:%.cpp=%.o) $(BUILDFOLDER)/$(CPPINONAME)

link: buildenv $(OBJECTS) $(MQTT_OBJECTS) $(MQTT_COBJECTS)
	@echo "Linking library"
	$(eval HAL_OBJECTS := $(shell find ../hal -name "*.o"))
	@$(CXX) $(LDFLAGS) $(HAL_OBJECTS) $(OBJECTS) $(MQTT_OBJECTS) $(MQTT_COBJECTS) -o $(BUILDFOLDER)/$(PROJNAME).so

clean:
	@echo "Erasing all build"
	@rm -fr build
	@rm -f $(MQTT_OBJECTS)
	@rm -f $(MQTT_COBJECTS)

.PHONY: clean hal link