##
## EPITECH PROJECT, 2022
## teams [WSL: Ubuntu-20.04]
## File description:
## Makefile
##

################################
### PREAMBLE                 ###
################################

# This makefile is built to compile a project.
# Here's what he can "make"... (lel)
# - all :	Build the project
# - fclean :	Remove the library archive and object files
# - clean :  Remove only the object files
# - re :	Basically: make fclean && make all
# - tests_run : Compile every unit test and run the built binary

################################
### OPTIONS                  ###
################################

TARGET_NAME	:=	myteams_cli
TESTS_NAME := unit_tests
SOURCES_DIR	:=	sources
OBJECTS_DIR	:=	objects
LIBRARIES_DIR := libraries
HEADERS_DIR	:=	include
TESTS_DIR	:=	tests

# vpath %.c $(SOURCES_DIR)

# MAKEFLAGS += --no-print-directory

################################
### COMPILER OPTIONS         ###
################################

CC	:=	gcc

ifneq (,$(shell command -v ccache))
	CC := ccache gcc
endif

CFLAGS	=	-Wall -Wextra -Werror -g3 \
		-std=gnu17 \
		-I./$(HEADERS_DIR) \
		-fno-builtin \
		-Wno-missing-field-initializers \
		-Wno-unused-parameter \
		-Wno-comment \
		$(CFLAGS_INPUT)

LDFLAGS := -L./$(LIBRARIES_DIR) -L../libs/myteams

LDLIBS := -l myteams -l uuid

########################
### FUNCTIONS        ###
########################

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) \
			$(filter $(subst *,%,$2),$d))

convertpath=$(subst /,\,$(1))

ifeq ($(OS),Windows_NT)
	mkdir=mkdir $(call convertpath,$(1))
	echo=echo $(1)
	rm=del /q "$(call convertpath,$(1))" 1>nul 2>&1
	rmdir=rmdir /S /q "$(call convertpath,$(1))" 1>nul 2>&1
	cp=copy $(call convertpath,$(1)) $(call convertpath,$(2)) 1>nul 2>&1
else
	mkdir=mkdir -p $(1)
	echo=echo -e $(1)
	rm=rm -f $(1)
	rmdir=rm -r -f $(1)
	cp=cp -r $(1) $(2)
endif

########################
### INTERNAL FILES   ###
########################

SOURCES	:=	$(call rwildcard,$(SOURCES_DIR),*.c)

TESTS_SOURCES := $(call rwildcard,$(TESTS_DIR),*.c)

LIBS_MAKEFILES := $(wildcard $(LIBRARIES_DIR)/*/.)

OBJECTS	:=	$(addprefix $(OBJECTS_DIR)/,$(patsubst %.c,%.o,$(SOURCES)))

NON_MAIN_OBJECTS := $(patsubst %main.o, ,$(OBJECTS))

TESTS_OBJECTS := $(addprefix $(OBJECTS_DIR)/,$(patsubst %.c,%.o,$(TESTS_SOURCES)))

########################
### RECIPES          ###
########################

.PHONY: all directories re clean fclean tests_run tests_dir

.PRECIOUS: $(OBJECTS_DIR)/. $(OBJECTS_DIR)%/.

all: directories $(TARGET_NAME)

directories: | $(SOURCES_DIR) $(OBJECTS_DIR)

re:	fclean all

clean: $(OBJECTS_DIR)
	@$(call rmdir,$(OBJECTS_DIR))
	@$(call echo,🗑️ -- Removed $(OBJECTS_DIR) --)

fclean: clean
	@$(call rm,$(TESTS_NAME))
	@$(call echo,🗑️ -- Removed $(TESTS_NAME) --)
	@$(call rm,$(TARGET_NAME))
	@$(call rm,$(TARGET_NAME).exe)
	@$(call echo,🗑️ -- Removed $(TARGET_NAME) --)

tests_run: tests_dir
	@make $(TESTS_NAME) CFLAGS_INPUT="-g -g3 --coverage -lcriterion" CC=gcc

tests_dir: | $(TESTS_DIR)

########################
### FILE GENERATORS  ###
########################

$(TESTS_NAME): $(LIBRARIES) $(NON_MAIN_OBJECTS) $(TESTS_OBJECTS)
	@$(CC) -o $(TESTS_NAME) $^ $(CFLAGS) $(LDFLAGS) $(LDLIBS) -lcriterion
	@./$(TESTS_NAME)

$(TARGET_NAME): $(LIBRARIES) $(OBJECTS)
	@$(CC) -o $(TARGET_NAME) $^ $(CFLAGS) $(LDFLAGS) $(LDLIBS)
	@$(call echo,🔧 -- Built with $(CFLAGS) --)
	@$(call echo,🔧 -- Linked with $(LDFLAGS) and $(LDLIBS) --)
	@$(call echo,😺 -- BUILD SUCCESSFUL --)

$(OBJECTS_DIR):
	@$(call mkdir,$@)

$(OBJECTS_DIR)/.:
	@$(call mkdir,$@)

$(OBJECTS_DIR)%/.:
	@$(call mkdir,$@)

$(TESTS_DIR):
	$(error ❌ -- Error: No tests folder --)

$(SOURCES_DIR):
	$(error 🙀 -- Error: Source folder not found --)

.SECONDEXPANSION:

########################
### PATTERN RULES    ###
########################

$(LIBRARIES_DIR)/%.a : $(LIBRARIES_DIR)/%/ | $$(@D)/.
	make -C $^

$(OBJECTS_DIR)/%.o : %.c | $$(@D)/.
	@$(CC) -c -o $@ $^ $(CFLAGS)
	@$(call echo,😺 -- $@ successfully compiled --)
