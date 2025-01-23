########################################### <-- VARIABLES --> ###########################################

APP_NAME := s21_containers
LIB_NAME := s21_containers.a
BUILD_DIR := build

SRC_DIR := .
MAIN_FILE := tests/test.cc
TEST_FILE := tests/test.cc

TEST_REPEAT := 25

SOURCE_EXTENSION := .cc

CC := gcc
CC_FLAGS := \
	-std=c++17 \
	\
	-Wall \
	-Wextra \
	-Wpedantic \
	\
	-Winit-self \
	-Wunreachable-code \
	-Wctor-dtor-privacy \
	-march=native \
	-Wctor-dtor-privacy \
	-Wnon-virtual-dtor \
	-Wold-style-cast \
	-Woverloaded-virtual \
	-Wsign-promo \
	-Wduplicated-branches \
	-Wduplicated-cond \
	-Wshadow=compatible-local \
	-Wcast-qual \
	-Wconversion \
	-Wzero-as-null-pointer-constant \
	-Wextra-semi \
	-Wsign-conversion \
	-Wlogical-op


LL_FLAGS := -lstdc++ -lm -lgtest

VALGRIND_FLAGS := --leak-check=full --show-leak-kinds=all --leak-resolution=med --track-origins=yes -s

########################################### <-- MAKEFILE --> ###########################################

.PHONY: all clean install run uninstall valgrind format check_format

MAIN_COLOR := 32
WARNING_COLOR := 33
ERROR_COLOR := 1;31

INSTALLATION_DIR := installation

GTEST_FLAGS := --gtest_repeat=$(TEST_REPEAT) --gtest_break_on_failure

OBJ_DIR := $(BUILD_DIR)/bin
CACHE_DIR := $(BUILD_DIR)/cache
HASH_CMD := shasum -a256

SRC_FILES := $(shell find $(SRC_DIR) -type f \( -name "*$(SOURCE_EXTENSION)" \) | grep -v -e $(TEST_FILE) -e $(MAIN_FILE))
OBJ_FILES := $(SRC_FILES:$(SOURCE_EXTENSION)=.o)

REPORT_DIR := $(BUILD_DIR)/report
FORMAT_STYLE := Google

APP_BIN := $(APP_NAME).app
TEST_BIN := $(APP_NAME)-test.app

all: test

install: uninstall build
	@mkdir -p $(INSTALLATION_DIR)
	@printf "\nInstall app to \e[$(MAIN_COLOR)m$(INSTALLATION_DIR)\e[0m\n"
	@cp $(BUILD_DIR)/$(APP_BIN) $(INSTALLATION_DIR) 

run: build
	@./$(BUILD_DIR)/$(APP_BIN)

uninstall: clean
	@printf "Uninstall \e[$(MAIN_COLOR)m$(APP_BIN)\e[0m\n"
	@rm -rf $(INSTALLATION_DIR)/$(APP_BIN)

$(LIB_NAME): $(OBJ_FILES)
	@mkdir -p $(BUILD_DIR)
	@printf "Building library \e[$(MAIN_COLOR)m$(LIB_NAME)\e[0m\n"
	@ar rcs $(BUILD_DIR)/$(LIB_NAME) $(foreach obj, $(OBJ_FILES), $(OBJ_DIR)/$(obj))
	@ranlib $(BUILD_DIR)/$(LIB_NAME)

build: format $(OBJ_FILES) $(LIB_NAME)
	@mkdir -p $(BUILD_DIR)
	@printf "Linking app \e[$(MAIN_COLOR)m$(APP_BIN)\e[0m\n"
	@printf "\t--> Used main file \e[$(MAIN_COLOR)m$(MAIN_FILE)\e[0m\n"
	@$(CC) $(CC_FLAGS) $(MAIN_FILE) -o $(BUILD_DIR)/$(APP_BIN) $(LL_FLAGS) -L. $(BUILD_DIR)/$(LIB_NAME)

test: format clear_coverage_files $(LIB_NAME)
	@mkdir -p $(BUILD_DIR)
	@printf "Linking test app \e[$(MAIN_COLOR)m$(TEST_BIN)\e[0m\n"
	@printf "\t--> Used main file \e[$(MAIN_COLOR)m$(TEST_FILE)\e[0m\n"
	@$(CC) $(CC_FLAGS) $(TEST_FILE) $(SRC_FILES) -fprofile-arcs -ftest-coverage -o $(BUILD_DIR)/$(TEST_BIN) $(LL_FLAGS)
	@printf "Run \e[$(MAIN_COLOR)mtests\e[0m\n"
	@./$(BUILD_DIR)/$(TEST_BIN) $(GTEST_FLAGS)

gcov_report: test
	@mkdir -p $(REPORT_DIR)
	@printf "Creating \e[$(MAIN_COLOR)mlcov report\e[0m\n"
	@lcov --ignore-errors inconsistent --filter brace -t "$(BUILD_DIR)/$(TEST_BIN)" --output-file $(REPORT_DIR)/report.info -c -q --directory ./ --include "$(shell pwd)/*" --exclude "$(shell pwd)/$(TEST_FILE)" 1>/dev/null 2>/dev/null
	@genhtml -q -o $(REPORT_DIR) $(REPORT_DIR)/report.info 1>/dev/null
	@printf "\t--> Path to index.html \e[$(MAIN_COLOR)m$(REPORT_DIR)/index.html\e[0m\n"

valgrind: test
	@printf "Run \e[$(MAIN_COLOR)mvalgrind\e[0m\n"
	@CK_FORK=no valgrind $(VALGRIND_FLAGS) ./$(BUILD_DIR)/$(TEST_BIN) > /dev/null

dist: clean
	@printf "Creating \e[$(MAIN_COLOR)mdistribution .tar file\e[0m\n"
	@mkdir -p $(BUILD_DIR)
	@tar -czvf ../$(APP_NAME).tar . > /dev/null
	@mv ../$(APP_NAME).tar $(BUILD_DIR)

clean:
	@printf "Target \e[$(MAIN_COLOR)mclean\e[0m\n"
	@rm -rf $(BUILD_DIR) $(REPORT_DIR) $(OBJ_DIR) $(APP_NAME).tar

clear_coverage_files:
	@printf "Target \e[$(MAIN_COLOR)mclear coverage files\e[0m\n"
	@rm -rf $(BUILD_DIR)/*.gcno $(BUILD_DIR)/*.gcda

format:
	@printf "Formatting to \e[$(WARNING_COLOR)m$(FORMAT_STYLE)\e[0m style \e[$(MAIN_COLOR)m$(SRC_DIR)/*\e[0m\n"
	@find $(SRC_DIR) -type f \( -name "*$(SOURCE_EXTENSION)" -o -name "*.h" -o -name "*.tpp" \) -exec clang-format -i --style=$(FORMAT_STYLE) {} \;

check_format:
	@find $(SRC_DIR) -type f \( -name "*$(SOURCE_EXTENSION)" -o -name "*.h" -o -name "*.tpp" \) -exec clang-format -n --style=$(FORMAT_STYLE) {} \; -exec printf "Check format \e[$(MAIN_COLOR)m{}$<\e[0m\n" \;

%.o: %$(SOURCE_EXTENSION)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $(OBJ_DIR)/$@)
	@mkdir -p $(CACHE_DIR)
	@mkdir -p $(dir $(CACHE_DIR)/$@)

	$(eval HASH_FILE := $(dir $(CACHE_DIR)/$@)/$(basename $(notdir $<)).hash)
	@touch $(HASH_FILE)
	$(eval HASH :=$(shell $(HASH_CMD) $< | grep -o "^[^ ]*"))

	@if grep -q "$(HASH)" $(HASH_FILE); then \
		printf "Up to date \e[$(WARNING_COLOR)m./$(BUILD_DIR)/$@\e[0m\n"; \
	else \
		printf "Compiling \e[$(MAIN_COLOR)m./$<\e[0m\n"; \
		$(CC) $(CC_FLAGS) -c $< -o $(OBJ_DIR)/$@; \
		if [ $$? != '0' ]; then \
			printf "\t--> Error during compilation \e[$(ERROR_COLOR)m$<\e[0m\n"; \
			rm $(HASH_FILE); \
			exit 1; \
		fi; \
		echo $(HASH) > $(HASH_FILE); \
	fi
