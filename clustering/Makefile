# Makefile

BUILD_HOME=..
include $(BUILD_HOME)/Options

all: built

%.o: %.c
	$(GCC) $(CFLAGS) $(DEFINES) $<

built: $(LIB_FILES)
	ar -cvq libclustering.a *.o	

clean:
	@rm -rf *.o *.out *.a
