CC=g++
RM=del
ZIP=7z


LIB= -lmingw32 \
	 -lSDL2main \
	 -lSDL2 \
	 -lSDL2_ttf \
	 -lSDL2_mixer \
	 -lSDL2_image

CXXINCS  = -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image
CXXFLAGS = $(CXXINCS) -std=c++14 -Wall -O

EXEC=bin\engine.exe
VER=0

SRC = $(wildcard src/*.cpp)
OBJ = $(addprefix obj/,$(notdir $(SRC:%.cpp=%.o)))
DELOBJ = $(subst /,\,$(OBJ))

# $(info Src find : $(SRC))
# $(info Obj find : $(OBJ))


all: clean $(EXEC)

zip: $(EXEC) clean
	-$(RM) $(VER).zip
	$(ZIP) a -tzip $(VER).zip game/

$(EXEC): $(OBJ)
	$(info Build $@ ...)
	@$(CC) -o $@ $^ $(CXXFLAGS) lib/libstdc++.a 

obj/%.o: src/%.cpp
	$(info $@ ...)
	@$(CC) -o $@ -c $< $(CXXFLAGS)

clean:
	$(info Cleaning ...)
	-@$(RM) $(DELOBJ) $(EXEC)

#EoF