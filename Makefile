# Makefile

include Options

all: build

rebuild: clean_all build links

%.o: %.c
	$(GCC) $(CFLAGS) $(DEFINES) $<

build: main.o
	cd $(CLUSTERING_PATH) 	&& make
	cd $(GENDATA_PATH)	&& make
	$(GCC) $^ $(CLUSTERING_PATH)/*.o $(LFLAGS) main.out

links:
	if [ $(DIMENSIONS) \< 4 ] ; then \
	  ln -fs $(PLOT_PATH)/plot_$(DIMENSIONS)dim.gnu plot.gnu ; fi

clean:
	rm -rf *.o *.out *.log

clean_all: clean
	rm -rf plot.gnu
	cd $(CLUSTERING_PATH) 	&& make clean
	cd $(GENDATA_PATH)	&& make clean
	cd $(DATA_PATH)	&& rm -rf *.png output.dat outime.dat
