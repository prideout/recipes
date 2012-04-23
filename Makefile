CC=gcc
CFLAGS=-std=c99 -Wall -c -Wc++-compat -O3
LIBS=-lX11 -lGL -lpng
DEMOS=\
	GenCubeMap \
	Lava \
	SimpleText \
	TextGrid \
	ClipPlanes \
	VoronoiPicking \
	DistancePicking \
	ToonShading \

SHARED=pez.o bstrlib.o pez.linux.o lodepng.o
PREFIX=demo-

run: GenCubeMap
	./GenCubeMap

all: $(DEMOS)

define DEMO_RULE
$(1): $(PREFIX)$(1).o $(PREFIX)$(1).glsl $(SHARED)
	$(CC) $(PREFIX)$(1).o $(SHARED) -o $(1) $(LIBS)
endef

$(foreach demo,$(DEMOS),$(eval $(call DEMO_RULE,$(demo))))

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(DEMOS)
