#GENGETOPT = @gengetopt@

bin_PROGRAMS=stupiddns



stupiddns_SOURCES = notsrv.c
stupiddns_CFLAGS  = $(LIBEVENTSTUFF_CFLAGS) $(AM_CFLAGS)
stupiddns_LDFLAGS = $(LIBEVENTSTUFF_LIBS)

include_HEADERS=  #not having one yet except generated config

#no option parser yet.
#If somebody knows how to avoid this hack, please contact...
#dist_noinst_DATA=options.ggo 
#options.c: options.ggo
#options.h: options.ggo

##ifneq ($(GENGETOPT),"false")
#.ggo.c:
#	$(GENGETOPT) -F ${@:%.c=%} < $<
#	LANG=C sed -i -e 's/..&@//g' $@ ${@:%.c=%.h}
##endif


EXTRA_DIST= Makefile.bak config.h.bak #as alternative Makefile

