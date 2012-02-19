CC=gcc
CFLAGS=-std=c99 -Wall -c -Wc++-compat -O3
LIBS=-lX11 -lGL
DEMOS=\
	ClipPlanes \
	VoronoiPicking \
	DistancePicking \
	ToonShading \

SHARED=glew.o pez.o bstrlib.o pez.linux.o
PREFIX=demo-

run: DistancePicking
	./DistancePicking

all: $(DEMOS)

VoronoiPicking: $(PREFIX)VoronoiPicking.o $(PREFIX)VoronoiPicking.glsl $(SHARED)
	$(CC) $(PREFIX)$@.o $(SHARED) -o $@ $(LIBS)

ClipPlanes: $(PREFIX)ClipPlanes.o $(PREFIX)ClipPlanes.glsl $(SHARED)
	$(CC) $(PREFIX)$@.o $(SHARED) -o $@ $(LIBS)

DistancePicking: $(PREFIX)DistancePicking.o $(PREFIX)DistancePicking.glsl $(SHARED)
	$(CC) $(PREFIX)$@.o $(SHARED) -o $@ $(LIBS)

ToonShading: $(PREFIX)ToonShading.o $(PREFIX)ToonShading.glsl $(SHARED)
	$(CC) $(PREFIX)$@.o $(SHARED) -o $@ $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(DEMOS)
