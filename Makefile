FILES = src/main.cpp src/player/player.cpp src/timer/timer.cpp src/timer/fps.cpp src/colliders/colliders.cpp

BUILDNAME = build

all : $(FILES)
	g++ $(FILES) -w -lSDL2 -lSDL2_image -o $(BUILDNAME)