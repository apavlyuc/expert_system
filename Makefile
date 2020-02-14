TARGET := expert

SRC_DIR := src
INC_DIR := inc
OBJ_DIR := build

COMPILER := g++
CFLAGS := -std=c++14 -I./$(INC_DIR) -Wall -Werror -Wextra

DIRS := $(patsubst $(SRC_DIR)%, $(OBJ_DIR)%, $(shell find $(SRC_DIR) -type d))
SRCS := $(shell find $(SRC_DIR) -type f -name "*.cpp")
OBJS := $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	@$(COMPILER) $(OBJS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@$(COMPILER) -o $@ -c $< $(CFLAGS)

$(OBJ_DIR):
	@mkdir -p $(DIRS)



clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(TARGET)

re: fclean all

