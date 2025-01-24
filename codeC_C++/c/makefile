CC = gcc
CFLAGS = -Wall

BUILD_DIR := ./build
SRC_DIR := ./src
INC_DIR := ./inc

all:
	mkdir -p $(SRC_DIR) $(BUILD_DIR) $(INC_DIR) 

project tree:
	@echo |
	@echo |
	@echo |
	@echo |
	@echo |

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

rebuild: clean build

clean:
	rm -r $(BUILD_DIR)


