# Makefile

include Options

all: build

rebuild: clean_all build links

%.o: %.c
	gcc $(CFLAGS) $(DEFINES) $<

build: main.o
	cd $(CLUSTERING_PATH) 	&& make
	cd $(GENDATA_PATH)	&& make
	gcc $^ $(CLUSTERING_PATH)/$(LIB_FILES) $(LFLAGS) main.out

links:
	if [ $(DIMENSIONS) \< 4 ] ; then \
	  ln -fs $(PLOT_PATH)/plot_$(DIMENSIONS)dim.gnu plot.gnu ; fi

clean:
	rm -rf *.o *.out

clean_all: clean
	rm -rf plot.gnu
	cd $(CLUSTERING_PATH) 	&& make clean
	cd $(GENDATA_PATH)	&& make clean
	cd $(DATA_PATH)	&& rm -rf *.png