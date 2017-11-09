VPATH = ./libs
OBJS_DIR = .objs
EXE_DIR = ..
LIBS_DIR = libs
EXE_FACEREC=facerec
# add more libraries here if necessary
OBJS_FACEREC=$(EXE_FACEREC).o linalg.o tiff_util.o

## COMPILER
# using gcc over clang because of pre-fetching optimization that is coming eventually
CC = gcc
WARNINGS = -Wall -Wextra -Werror -Wno-error=unused-parameter
INC=-I./libs/
CFLAGS_DEBUG   = -O0 $(WARNINGS) $(INC) -g -std=c99 -c -MMD -MP -D_GNU_SOURCE -pthread -DDEBUG
CFLAGS_RELEASE = -O2 $(WARNINGS) $(INC) -g -std=c99 -c -MMD -MP -D_GNU_SOURCE -pthread

## LINKER
# eventually I would like to use a static library here
LD = gcc
LDFLAGS = -pthread -ltiff

# PHONY declarations
.PHONY: all
.PHONY: debug
.PHONY: release
.PHONY: clean

## BUILD TARGETS
# if cp fails in pre-build then remove any of the files that was already copied
all:
	($(MAKE) --no-print-directory pre-build && $(MAKE) --no-print-directory post-build) || $(MAKE) --no-print-directory failed

### Update: 11/9/2017 using VPATH now ###
# but keep the existing hierarchy sturcture in case
# other commands need to be added
# it would be nice to have echo "useful output" during make
#### static library fix ####
# without static libraries, this is the best solution I have
pre-build:
	# cp ./libs/linalg.c ./linalg.c
	# cp ./libs/linalg.h ./linalg.h
	# cp ./libs/tiff_util.c ./tiff_util.c
	# cp ./libs/tiff_util.h ./tiff_util.h

post-build: release
	# rm ./linalg.c
	# rm ./linalg.h
	# rm ./tiff_util.c
	# rm ./tiff_util.h
	rm -r ./$(OBJS_DIR)

failed:	
	# -rm ./linalg.c
	# -rm ./linalg.h
	# -rm ./tiff_util.c
	# -rm ./tiff_util.h
	-rm -r ./$(OBJS_DIR)
#### static library fix end ####

release: $(EXE_DIR)/$(EXE_FACEREC)

debug: clean
	($(MAKE) --no-print-directory pre-build && $(MAKE) --no-print-directory post-build-debug) || $(MAKE) --no-print-directory failed

post-build-debug: $(EXE_DIR)/$(EXE_FACEREC:%=%-debug)
	# rm ./linalg.c
	# rm ./linalg.h
	# rm ./tiff_process.c
	# rm ./tiff_process.h
	rm -r ./$(OBJS_DIR)

## OBJECTS
-include $(OBJS_DIR)/*.d
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%-debug.o: %.c | $(OBJS_DIR)
	@mkdir -p $(basename $@)
	$(CC) $(CFLAGS_DEBUG) $< -o $@

$(OBJS_DIR)/%-release.o: %.c | $(OBJS_DIR)
	@mkdir -p $(basename $@)
	$(CC)  $(CFLAGS_RELEASE) $< -o $@

## EXES
$(EXE_DIR)/$(EXE_FACEREC): $(OBJS_FACEREC:%.o=$(OBJS_DIR)/%-release.o)
	$(LD) $^ $(LDFLAGS) -o $@

$(EXE_DIR)/$(EXE_FACEREC)-debug: $(OBJS_FACEREC:%.o=$(OBJS_DIR)/%-debug.o)
	$(LD) $^ $(LDFLAGS) -o $@




## CLEAN
clean:
	-rm -rf .objs $(EXE_DIR)/$(EXE_FACEREC) $(EXE_DIR)/$(EXE_FACEREC:%=%-debug)
