# Makefile

BUILD_HOME=..
include $(BUILD_HOME)/Options

all: built

%.o: %.c
	$(GCC) $(CFLAGS) $(DEFINES) $<

built: main.o
	$(GCC) $(LFLAGS) gendata.out $(BUILD_HOME)/$(CLUSTERING_PATH)/*.o $^

clean:
	@rm -rf *.o *.out *.log

