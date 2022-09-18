SUBDIRS = src/models/abradford/ src/models/spinsky src/models/financialrecipes/src src/models/financialrecipes/examples src/models/metaoptions/src src/models/metaoptions/tests src/common src/curses src/gtk man doc doc/html

appicondir = $(datadir)/pixmaps
appicon_DATA = icons/32x32/optionmatrix.xpm\
	icons/32x32/optionmatrix_console.xpm

desktopdir = $(datadir)/applications
desktop_DATA = icons/optionmatrix.desktop\
	icons/optionmatrix_console.desktop

icondir = $(datadir)/icons/hicolor/256x256/apps
icon_DATA = icons/256x256/optionmatrix.png\
	icons/256x256/optionmatrix_console.png

icon128dir = $(datadir)/icons/hicolor/128x128/apps
icon128_DATA = icons/128x128/optionmatrix.png\
	icons/128x128/optionmatrix_console.png

icon64dir = $(datadir)/icons/hicolor/64x64/apps
icon64_DATA = icons/64x64/optionmatrix.png\
	icons/64x64/optionmatrix_console.png

icon48dir = $(datadir)/icons/hicolor/48x48/apps
icon48_DATA = icons/48x48/optionmatrix.png\
	icons/48x48/optionmatrix_console.png

icon32dir = $(datadir)/icons/hicolor/32x32/apps
icon32_DATA = icons/32x32/optionmatrix.png\
	icons/32x32/optionmatrix_console.png

EXTRA_DIST = \
	README.md\
	README.how_to_make_a_release\
	icons/mac/README\
	icons/mac/optionmatrix.icns\
	icons/32x32/optionmatrix.xpm\
	icons/32x32/optionmatrix_console.xpm\
	icons/32x32/optionmatrix.png\
	icons/32x32/optionmatrix_console.png\
	icons/48x48/optionmatrix.png\
	icons/48x48/optionmatrix_console.png\
	icons/64x64/optionmatrix.png\
	icons/64x64/optionmatrix_console.png\
	icons/128x128/optionmatrix.png\
	icons/128x128/optionmatrix_console.png\
	icons/256x256/optionmatrix.png\
	icons/256x256/optionmatrix_console.png\
	icons/optionmatrix.desktop\
	icons/optionmatrix_console.desktop\
	icons/OptionMatrix.png\
	icons/windows/README\
	icons/windows/optionmatrix.ico\
	icons/windows/optionmatrixdos.ico\
	icons/windows/installer.ico\
	icons/windows/C++.ico\
	icons/windows/HTMLhelper.ico\
	icons/windows/information.ico\
	icons/windows/pdf.ico\
	icons/windows/Tests.ico\
	icons/windows/Website.ico\
	HOWTO\
	utils/tab.sh\
	utils/apt-get.sh\
	utils/yum.sh\
	utils/dnf.sh\
	utils/zypper.sh\
	utils/README\
	src/README\
	src/models/metaoptions/tests/TESTSUITE.README\
	src/models/metaoptions/AUTHORS\
	src/models/metaoptions/ChangeLog\
	src/models/financialrecipes/AUTHORS\
	src/models/financialrecipes/ChangeLog\
	src/models/financialrecipes/README

install: install-html install-pdf install-data
	$(MKDIR_P) $(DESTDIR)$(bindir)
	install src/curses/optionmatrix_console $(DESTDIR)$(bindir)
	install src/gtk/optionmatrix $(DESTDIR)$(bindir)

private_images = \
	src/gtk/images/10.png\
	src/gtk/images/11.png\
	src/gtk/images/1.png\
	src/gtk/images/2.png\
	src/gtk/images/3.png\
	src/gtk/images/4.png\
	src/gtk/images/5.png\
	src/gtk/images/6.png\
	src/gtk/images/7.png\
	src/gtk/images/8.png\
	src/gtk/images/9.png

install-icons:
	for icon in $(private_images); do \
		$(MKDIR_P) $(DESTDIR)$(pkgdatadir)/images/; \
		$(INSTALL_DATA) $(srcdir)/$$icon $(DESTDIR)$(pkgdatadir)/images/; \
	done

install-data-local: install-icons

# After you run 'sudo make uninstall' the command
# find /usr -name "optionmatrix*" -print 2>/dev/null
# should yield nothing. If you find installation files there could be a problem
# with this section.
uninstall-local:
	rm -f $(DESTDIR)$(pkgdatadir)/images/*.png
	rm -f $(DESTDIR)$(pkgdatadir)/*.glade
	if test -d $(DESTDIR)${pkgdatadir}/images; then rmdir $(DESTDIR)${pkgdatadir}/images; fi
	if test -d $(DESTDIR)${pkgdatadir}; then rmdir $(DESTDIR)${pkgdatadir}; fi
	if test -d $(DESTDIR)$(docdir); then rmdir $(DESTDIR)$(docdir); fi
