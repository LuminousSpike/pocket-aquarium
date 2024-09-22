#
# A Makefile that compiles all .c and .s files in "src" and "res"
# subdirectories and places the output in a "obj" subdirectory
#

# If you move this project you can change the directory
# to match your GBDK root directory (ex: GBDK_HOME = "C:/GBDK/"
ifndef GBDK_HOME
	GBDK_HOME = ./gbdk/
endif

LCC = $(GBDK_HOME)bin/lcc
LCCFLAGS += -Wm-yC

# GBDK_DEBUG = ON
ifdef GBDK_DEBUG
	LCCFLAGS += -debug -v
endif

# Detect the number of CPU cores
ifeq ($(OS),Windows_NT)
	JOBS := $(NUMBER_OF_PROCESSORS)
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		JOBS := $(shell nproc)
	endif
	ifeq ($(UNAME_S),Darwin)
		JOBS := $(shell sysctl -n hw.ncpu)
	endif
endif

# Use parallel execution by default, using the number of detected cores
MAKEFLAGS += --jobs=$(JOBS)

# You can set the name of the .gbc ROM file here
PROJECTNAME    = pocket_aquarium

SRCDIR      = src
OBJDIR      = obj
RESDIR      = res
BINS	    = $(OBJDIR)/$(PROJECTNAME).gbc
CSOURCES    = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.c))) $(foreach dir,$(RESDIR),$(notdir $(wildcard $(dir)/*.c)))
ASMSOURCES  = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.s)))
OBJS       = $(CSOURCES:%.c=$(OBJDIR)/%.o) $(ASMSOURCES:%.s=$(OBJDIR)/%.o)

all:	prepare background-tiles $(BINS)

compile.bat: Makefile
	@echo "REM Automatically generated from Makefile" > compile.bat
	@make -sn | sed y/\\//\\\\/ | sed s/mkdir\ -p\/mkdir\/ | grep -v make >> compile.bat

# Compile .c files in "src/" to .o object files
$(OBJDIR)/%.o:	$(SRCDIR)/%.c
	$(LCC) $(LCCFLAGS) -c -o $@ $<

# Compile .c files in "res/" to .o object files
$(OBJDIR)/%.o:	$(RESDIR)/%.c
	$(LCC) $(LCCFLAGS) -c -o $@ $<

# Compile .s assembly files in "src/" to .o object files
$(OBJDIR)/%.o:	$(SRCDIR)/%.s
	$(LCC) $(LCCFLAGS) -c -o $@ $<

# If needed, compile .c files in "src/" to .s assembly files
# (not required if .c is compiled directly to .o)
$(OBJDIR)/%.s:	$(SRCDIR)/%.c
	$(LCC) $(LCCFLAGS) -S -o $@ $<

# Link the compiled object files into a .gbc ROM file
$(BINS):	$(OBJS)
	$(LCC) $(LCCFLAGS) -o $(BINS) $(OBJS)

prepare:
	mkdir -p $(OBJDIR)

clean:
	rm -f  $(OBJDIR)/*.*

# Run clang-format on all .c files in the src directory
format:
	find $(SRCDIR) -name '*.c' -o -name '*.h' -exec clang-format -i {} +

background-tiles:
	@go run utils/spritegen/*.go -format gb -image ./assests/pngs/numbers.png -output res/numbers
	@go run utils/spritegen/*.go -format gb -image ./assests/pngs/symbols.png -output res/symbols
	find res -name '*.c' -exec clang-format -i {} +

.PHONY: background-tiles
