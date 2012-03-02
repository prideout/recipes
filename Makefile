CC=gcc
CFLAGS=-std=c99 -Wall -c -Wc++-compat -O3
LIBS=-lX11 -lGL -lpng
DEMOS=\
	Lava \
	SimpleText \
	TextGrid \
	ClipPlanes \
	VoronoiPicking \
	DistancePicking \
	ToonShading \

SHARED=glew.o pez.o bstrlib.o pez.linux.o lodepng.o
PREFIX=demo-

run: Lava
	./Lava

all: $(DEMOS)

%: $(PREFIX)%.glsl $(PREFIX)%.o $(SHARED)
	$(CC) $(PREFIX)$*.o $(SHARED) -o $* $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(DEMOS)
