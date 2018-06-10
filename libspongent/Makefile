CC          = gcc
AR          = ar
ARFLAGS     = -rcs

CFLAGS     += -std=c++11 -nostdinc -fvisibility=hidden -fpie -fstack-protector -g -Os

INCLUDE     = -I$(SGX_SDK)/include/ -I$(SGX_SDK)/include/tlibc -I$(SGX_SDK)/include/libcxx 
SOURCES     = $(shell ls *.cpp)
OBJECTS     = $(SOURCES:.cpp=.o)
OUTPUT      = libspongent.a

all: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	echo "$(INDENT)[AR] " $(OUTPUT)
	$(AR) $(ARFLAGS) $(OUTPUT) $(OBJECTS)

%.o : %.c
	echo "$(INDENT)[CC] " $<
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

%.o : %.cpp
	echo "$(INDENT)[CC] " $<
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

%.o : %.S
	echo "$(INDENT)[AS] " $<
	$(AS) $(INCLUDE) -c $< -o $@

clean:
	echo "$(INDENT)[RM]" $(OBJECTS) $(OUTPUT)
	rm -f $(OBJECTS) $(OUTPUT)
