# set the include path for X, qt and KDE
INCLUDES = $(all_includes)

# these are the headers for your project
noinst_HEADERS = datacruncher.h histogram.h mainwindow.h mcpd8.h mesydaq2.h \
	mpsd8.h networkdevice.h

# let automoc handle all of the meta source files (moc)
METASOURCES = AUTO

messages: rc.cpp
	$(EXTRACTRC) `find . -name \*.ui -o -name \*.rc` > rc.cpp
	$(XGETTEXT) *.cpp -o $(podir)/mesydaq2.pot

KDE_ICON = AUTO

#########################################################################
# APPLICATION SECTION
#########################################################################
# this is the program that gets installed.  it's name is used for all
# of the other Makefile.am variables
bin_PROGRAMS = mesydaq2

# the application source, library search path, and link libraries
mesydaq2_SOURCES = controlinterface.cpp datacruncher.cpp histogram.cpp main.cpp \
	mainwindow.cpp mcpd8.cpp measurement.cpp mesydaq2.cpp mesydaq2mainwindow.ui mpsd8.cpp \
	networkdevice.cpp
mesydaq2_LDFLAGS = $(KDE_RPATH) $(all_libraries)
mesydaq2_LDADD = $(LIBPTHREAD) $(LIB_KDEUI)

# this is where the desktop file will go 
shelldesktopdir   = $(kde_appsdir)/Utilities
shelldesktop_DATA = mesydaq2.desktop

# this is where the shell's XML-GUI resource file goes
shellrcdir   = $(kde_datadir)/mesydaq2
shellrc_DATA = mesydaq2ui.rc

