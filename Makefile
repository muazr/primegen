# tool macros
CC := g++
CCFLAGS := -std=c++11 -pedantic -Wall -Wextra -Werror -O2
DBGFLAGS := -g
CCOBJFLAGS := $(CCFLAGS) -c

# path macros
OBJ_PATH := build
SRC_PATH := src
DBG_PATH := debug
TEST_PATH := tests
TEST_OBJ_PATH := $(OBJ_PATH)/tests

# compile macros
TARGET_NAME := prime-number-generator
ifeq ($(OS),Windows_NT)
	TARGET_NAME := $(addsuffix .exe,$(TARGET_NAME))
endif
TARGET := $(TARGET_NAME)
TARGET_DEBUG := $(DBG_PATH)/$(TARGET_NAME)
TEST_TARGET := prime-number-generator-test

# src files & obj files
SRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.cpp)))
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
OBJ_DEBUG := $(addprefix $(DBG_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
TESTS := $(foreach x, $(TEST_PATH), $(wildcard $(addprefix $(x)/*,.cpp)))
TEST_OBJ := $(filter-out $(OBJ_PATH)/main.o, $(OBJ)) $(addprefix $(TEST_OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(TESTS)))))

$(info    TESTS is $(TESTS))
$(info    TEST_OBJ is $(TEST_OBJ))

# clean files list
CLEAN_FILE_LIST := $(TARGET) \
				   $(TEST_TARGET)
CLEAN_DIR_LIST := $(TEST_OBJ_PATH) \
				  $(OBJ_PATH) \
				  $(DBG_PATH)

# default rule
default: makedir build

# non-phony targets
$(TARGET): $(OBJ)
	$(CC) $(CCFLAGS) -o $@ $(OBJ)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CC) $(CCOBJFLAGS) -o $@ $<

$(DBG_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CC) $(CCOBJFLAGS) $(DBGFLAGS) -o $@ $<

$(TARGET_DEBUG): $(OBJ_DEBUG)
	$(CC) $(CCFLAGS) $(DBGFLAGS) $(OBJ_DEBUG) -o $@

$(TEST_TARGET): $(TEST_OBJ)
	$(CC) $(CCFLAGS) -o $@ $(TEST_OBJ)

$(TEST_OBJ_PATH)/%.o: $(TEST_PATH)/%.cpp
	$(CC) $(CCOBJFLAGS) -I $(SRC_PATH) -o $@ $< 

# phony rules
.PHONY: makedir
makedir:
	@mkdir -p $(OBJ_PATH) $(OBJ_PATH) $(TEST_OBJ_PATH) $(DBG_PATH)

.PHONY: all
all: makedir $(TARGET) $(TEST_TARGET)

.PHONY: build
build: $(TARGET)

.PHONY: debug
debug: $(TARGET_DEBUG)

.PHONY: test
test: $(TEST_TARGET)

.PHONY: clean
clean:
	@echo CLEAN $(CLEAN_DIR_LIST) $(CLEAN_FILE_LIST)
	@rm -rf $(CLEAN_DIR_LIST)
	@rm -f $(CLEAN_FILE_LIST)
