CC= g++

srcs = raytracer.cc raybox.cc mymatrix.cc DriverWeek6.cc
objects = $(patsubst %.cc, %.o,$(srcs))
PROJECT= Raytracing

LINKFLAGS=
LIBS= -lboost_system -lboost_timer
CFLAGS=  -Wno-deprecated -g -O2

.PHONY: all
all:${PROJECT}
#	$(shell ctags -Re)

# regel for exe-filen, dvs link filer
${PROJECT}: $(objects)
	$(CC) $(objects) $(LINKFLAGS) $(LIBS) -o ${PROJECT}

%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -f *.o
	rm -f $(PROJECT)
	rm -f TAGS
