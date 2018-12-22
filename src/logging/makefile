LOGGINGDIR := logging


$(OBJDIR)/gfp_config.o: $(LOGGINGDIR)/gfp_config.cc
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/gfp_logging.o: $(LOGGINGDIR)/gfp_logging.cc $(LOGGINGDIR)/gfp_logging.ini ../logs
	$(CC) $(CFLAGS) -c -o $@ $<

../logs: 
	mkdir ../logs



