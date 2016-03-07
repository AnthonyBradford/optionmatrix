bin_PROGRAMS = optionmatrix

optionmatrix_CXXFLAGS = -DDATADIR=\"$(datadir)\"

optionmatrix_SOURCES = \
gtk_bonds.cpp\
gtk_calendar.cpp\
gtk_cashflow.cpp\
gtk_checkbutton.cpp\
gtk_combobox.cpp\
gtk_dialog.cpp\
gtk_display.cpp\
gtk_extern.h\
gtk_glade_xml.h\
gtk_include.h\
gtk_main.cpp\
gtk_main.h\
gtk_menu.cpp\
gtk_radio.cpp\
gtk_scale.cpp\
gtk_spin.cpp\
gtk_thread.cpp\
gtk_icon.h

GLADE_FILE = gtk_glade_xml.glade

EXTRA_DIST = \
$(GLADE_FILE)\
images/10.png\
images/11.png\
images/12.png\
images/13.png\
images/14.png\
images/1.png\
images/2.png\
images/3.png\
images/4.png\
images/5.png\
images/6.png\
images/7.png\
images/8.png\
images/9.png

optionmatrix_CPPFLAGS = -I$(top_srcdir)/src/models/financialrecipes/src -I$(top_srcdir)/src/models/metaoptions/src -I$(top_srcdir)/src/common

optionmatrix_LDADD = ../common/liboptionmatrix.a ../models/abradford/libabradford.a ../models/spinsky/libspinsky.a ../models/financialrecipes/src/librecipes.a ../models/metaoptions/src/libmetaoptions.a

install-glade-file:
	for file in $(GLADE_FILE); do \
		mkdir -p $(DESTDIR)$(pkgdatadir)/; \
		$(INSTALL_DATA) $(srcdir)/$$file $(DESTDIR)$(pkgdatadir)/; \
	done

install-data-local: install-glade-file
