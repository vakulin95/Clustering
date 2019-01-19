# Makefile

BUILD_HOME=..
include $(BUILD_HOME)/Options

all: built

%.o: %.c
	@gcc $(CFLAGS) $(DEFINES) $<

built: $(LIB_FILES)

clean:
	@rm -rf *.o *.out
