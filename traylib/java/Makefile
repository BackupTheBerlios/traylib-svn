# Set the C flags
CFLAGS = -g `pkg-config --cflags gtk+-2.0`  -I. -I/usr/lib/java2/include/ -I/usr/lib/java2/include/linux/ -I../include/
LDFLAGS = `pkg-config --libs gtk+-2.0`  -lgthread-2.0

CLASSPATH		= class
PACKAGEPATH	= de/asuhm/trayicon
SOURCEPATH		= source

default: all


# make rules


libtrayicon.so: $(SOURCEPATH)/$(PACKAGEPATH)/JTrayiconWrap.o
	$(CC) $(LDFLAGS) -shared $^ ../src/libtraylib_la-eggtrayicon.o  ../src/libtraylib_la-trayicon.o -o $@

$(SOURCEPATH)/$(PACKAGEPATH)/JTrayiconWrap.o: $(SOURCEPATH)/$(PACKAGEPATH)/JTrayiconWrap.c
	$(CC) -c $(CFLAGS) $^ -o $@

$(CLASSPATH)/$(PACKAGEPATH)/%.class:		$(SOURCEPATH)/$(PACKAGEPATH)/%.java
	javac -d $(CLASSPATH) -classpath $(CLASSPATH) $<


PKG_TRAYICON	=	$(CLASSPATH)/$(PACKAGEPATH)/JTrayiconEvent.class \
							$(CLASSPATH)/$(PACKAGEPATH)/JTrayiconListener.class \
							$(CLASSPATH)/$(PACKAGEPATH)/JTrayiconWrap.class\
							$(CLASSPATH)/$(PACKAGEPATH)/JTrayicon.class 
	
							

trayicon.jar:	$(PKG_TRAYICON)
	jar -cvf $@ -C $(CLASSPATH)/ .

all:	trayicon.jar	libtrayicon.so


		
# A rule to clean the generated files
clean:
	rm -f libtrayicon.so *.o 

.PHONY: clean
