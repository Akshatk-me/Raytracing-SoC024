BUILD_DIR := ./build
SRC_DIR := ./src
INCLUDE_DIR := ./include
LIB_DIR := ./lib

TARGET_EXEC := $(BUILD_DIR)/bin


SRCS := $(SRC_DIR)/main.cpp
OBJS := $(patsubst $(SRC_DIR)%.cpp, $(BUILD_DIR)%.o,  $(SRCS))
LIBSRC := $(LIB_DIR)/vecops.cpp
LIBOBJS := $(patsubst $(LIB_DIR)%.cpp, $(BUILD_DIR)%.o, $(LIBSRC))
LIBS := $(patsubst $(LIB_DIR)/%.cpp, $(BUILD_DIR)/lib%.a, $(LIBSRC))

CPPFLAGS = -Wall 
CC = g++


$(TARGET_EXEC): $(OBJS) $(LIBS)
	@echo "bin: $@ preq: $<"
	$(CC) $(CPPFLAGS) $(OBJS) $(LIBS) -o $@
	rm $(LIBOBJS) $(OBJS)


$(filter $(BUILD_DIR)%.o,$(OBJS)): $(BUILD_DIR)%.o: $(SRC_DIR)%.cpp
	@echo "compiling objs target: $@ prereq: $<"
	g++ -c $< -o $@

$(filter $(BUILD_DIR)/lib%.a,$(LIBS)): $(BUILD_DIR)/lib%.a: $(BUILD_DIR)/%.o
	@echo "compiling libs target: $@ prereq: $<"
	ar rcs $@ $<

$(filter $(BUILD_DIR)%.o,$(LIBOBJS)): $(BUILD_DIR)%.o: $(LIB_DIR)%.cpp $(INCLUDE_DIR)%.h
	@echo "compiling libobjs target: $@ prereq: $<"
	g++ -c $< -o $@

.PHONY: test
test:
	@echo "$(SRCS) src"
	@echo "$(OBJS) obj"
	@echo "$(LIBSRC) libsrc"
	@echo "$(LIBOBJS) libobjs"
	@echo "$(LIBS) libs"
 
.PHONY: clean 
clean:
	rm $(OBJS) $(LIBOBJS) $(LIBS) $(TARGET_EXEC)
