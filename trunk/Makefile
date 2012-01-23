CPP  = i686-pc-mingw32-g++.exe
CC   = gcc.exe

RES  = 
OBJ  = FourmisActions.o ProjetFourmi.o InitPlayfield.o OurFourmiWorld.o $(RES)
LINKOBJ  = FourmisActions.o ProjetFourmi.o InitPlayfield.o OurFourmiWorld.o $(RES)
LIBS =  -L"." -lalleg -luser32 -lgdi32 -mwindows 
INCS =
CXXINCS =  -I"C:\cygwin\usr\i686-pc-mingw32\sys-root\mingw\include" -I"allegro442_include" 
BIN  = ants-hunting.exe
CXXFLAGS = $(CXXINCS)
CFLAGS = $(INCS)

.PHONY: all all-before all-after clean clean-custom

all: all-before ants-hunting.exe all-after


clean: clean-custom
	rm -f $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o "ants-hunting.exe" $(LIBS)

ProjetFourmi.o: ProjetFourmi.cpp
	$(CPP) -c ProjetFourmi.cpp -o ProjetFourmi.o $(CXXFLAGS)
	
FourmisActions.o: FourmisActions.cpp
	$(CPP) -c FourmisActions.cpp -o FourmisActions.o $(CXXFLAGS)

InitPlayfield.o: InitPlayfield.cpp
	$(CPP) -c InitPlayfield.cpp -o InitPlayfield.o $(CXXFLAGS)

OurFourmiWorld.o: OurFourmiWorld.cpp
	$(CPP) -c OurFourmiWorld.cpp -o OurFourmiWorld.o $(CXXFLAGS)
