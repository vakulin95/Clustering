# Makefile

BUILD_HOME=..
include $(BUILD_HOME)/Options

all: built

%.o: %.c
	@gcc $(CFLAGS) $(DEFINES) $<

built: main.o
	@gcc $^ $(BUILD_HOME)/$(CLUSTERING_PATH)/$(LIB_FILES) $(LFLAGS) gendata.out

clean:
	@rm -rf *.o *.out *.log

