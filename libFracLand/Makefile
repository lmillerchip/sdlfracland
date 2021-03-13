SRC_DIR=.
SRC_FILES=$(wildcard $(SRC_DIR)/*.cpp) 

OBJECTS=$(patsubst $(SRC_DIR)/%.cpp,%.o,$(SRC_FILES))

libFracLand.a: $(SRC_FILES) $(OBJECTS)
	$(AR) -rcs $@ $(OBJECTS)

%.o: $(SRC_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f *.o *.a

