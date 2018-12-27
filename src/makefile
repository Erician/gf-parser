.PHONY: clean 
GFPARSER = ../obj/gfp
PRODUCTS = $(GFPARSER)
default: $(PRODUCTS)

OBJDIR = ../obj

include command/makefile
include font/makefile
include painting/makefile
include utils/makefile
include logging/makefile

include unittest/makefile
include unittest/painting/makefile
include unittest/utils/makefile
include unittest/logging/makefile

# OBJS can deal with either .cc or .c 
OBJS += $(OBJDIR)/gfp_command_factory.o $(OBJDIR)/gfp_command.o
OBJS += $(OBJDIR)/gfp_character.o $(OBJDIR)/gfp_font.o
OBJS += $(OBJDIR)/gfp_drawing_board.o $(OBJDIR)/gfp_pen.o $(OBJDIR)/gfp_painting.o
OBJS += $(OBJDIR)/gfp_stringutil.o 
OBJS += $(OBJDIR)/gfp_config.o $(OBJDIR)/gfp_logging.o 
OBJS += $(OBJDIR)/gfp_main.o

JUNK = *~ $(OBJDIR)/*.o $(OBJDIR)/*.a  

# Define the tools we are going to use
CC= g++
LD = g++

CFLAGS = -g -Wall -Wno-unused -Wno-sign-compare -std=c++11 -I.

LIBS = -lm -lc -lpthread

$(OBJDIR)/gfp_main.o: gfp_main.cc
	$(CC) $(CFLAGS) -c -o $@ $<

$(PRODUCTS): $(OBJS)     
	$(LD) -o $@  $^  $(LIBS)
	cp $(PRODUCTS) ./


#unittest,using googletest:https://github.com/google/googletest/blob/master/googletest/docs/Primer.md
#this make no sense, and just test googletest

ut-painting-drawing-board: $(OBJDIR)/gfp_drawing_board_ut
	./$(OBJDIR)/gfp_drawing_board_ut

ut-utils-stringutil: $(OBJDIR)/gfp_stringutil_ut
	./$(OBJDIR)/gfp_stringutil_ut

ut-logging-logging: $(OBJDIR)/gfp_logging_ut 
	./$(OBJDIR)/gfp_logging_ut  

ut-logging-config: $(OBJDIR)/gfp_config_ut
	./$(OBJDIR)/gfp_config_ut

clean:
	@rm -f $(JUNK) $(PRODUCTS) ./gfp ../logs/log.txt


