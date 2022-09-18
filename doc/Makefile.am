info_TEXINFOS = optionmatrix.texi

optionmatrix_TEXINFOS = optionmatrix.texi\
	version.texi\
	fdl.texi\
	epsf.tex

# Do nothing for 'make dvi'
# Try 'make png2eps ; make ps' for DVI and PS
dvi:

CLEANFILES = optionmatrix.dvi

TEXTFILES = images/ConsoleChain.txt\
	images/ConsoleSelect.txt\
	images/ConsoleFormat.txt\
	images/ConsoleWelcome.txt\
	images/SleepDelay.txt\
	images/Calendar.txt\
	images/CouponEditor.txt\
	images/DateEngine.txt\
	images/OptionMatrixCalendarDated.txt\
	images/OptionMatrixSpreads.txt\
	images/OptionMatrix.txt\
	images/Time.txt\
	images/PriceInterestStandard.txt\
	images/StrikesDrop.txt\
	images/Strikes.txt\
	images/StrikeDropDownAndAdjuster.txt\
	images/ModelDropDownOpen.txt\
	images/CNDDrop.txt\
	images/CNDDropDown.txt\
	images/Greeks.txt\
	images/UseDateEngine.txt\
	images/DisplayFormats.txt\
	images/MonthsToStrike.txt\
	images/MonthToStrikes.txt\
	images/MonthsAcross.txt\
	images/3Calls3Puts.txt\
	images/CycleDropOpen.txt\
	images/DateEngineProperties.txt\
	images/LegControls.txt\
	images/CalendarSpread.txt\
	images/SpreadLegs.txt\
	images/PrefsSettings.txt\
	images/ModelsList.txt\
	images/Precision.txt\
	images/DateEngineSelected.txt\
	images/CycleClosed.txt\
	images/RealTime.txt\
	images/SpreadCheckbox.txt\
	images/SpreadsCCPPCPPC.txt\
	images/ConsoleCategories.txt\
	images/ConsoleInputs.txt\
	images/OptionMatrixWin1.txt\
	images/Leg1.txt\
	images/Leg1Leg2.txt\
	images/ModelByAuthor.txt\
	images/CalendarButton.txt\
	images/CUSTInput.txt\
	images/MonthAdjuster.txt\
	images/Export.txt\
	images/10.txt\
	images/11.txt\
	images/1.txt\
	images/2.txt\
	images/3.txt\
	images/4.txt\
	images/5.txt\
	images/6.txt\
	images/7.txt\
	images/8.txt\
	images/9.txt

EQN_IMAGES = images/ConsoleChain.png\
	images/ConsoleSelect.png\
	images/ConsoleFormat.png\
	images/ConsoleWelcome.png\
	images/SleepDelay.png\
	images/CouponEditor.png\
	images/DateEngine.png\
	images/OptionMatrixCalendarDated.png\
	images/Calendar.png\
	images/OptionMatrix.png\
	images/OptionMatrixSpreads.png\
	images/3Calls3Puts.png\
	images/CalendarSpread.png\
	images/CNDDropDown.png\
	images/CNDDrop.png\
	images/CycleDropOpen.png\
	images/DateEngineProperties.png\
	images/DisplayFormats.png\
	images/Greeks.png\
	images/LegControls.png\
	images/ModelDropDownOpen.png\
	images/ModelsList.png\
	images/MonthsAcross.png\
	images/MonthsToStrike.png\
	images/MonthToStrikes.png\
	images/Precision.png\
	images/PrefsSettings.png\
	images/PriceInterestStandard.png\
	images/SpreadLegs.png\
	images/StrikeDropDownAndAdjuster.png\
	images/StrikesDrop.png\
	images/Strikes.png\
	images/Time.png\
	images/UseDateEngine.png\
	images/DateEngineSelected.png\
	images/CycleClosed.png\
	images/RealTime.png\
	images/SpreadCheckbox.png\
	images/SpreadsCCPPCPPC.png\
	images/ConsoleCategories.png\
	images/ConsoleInputs.png\
	images/OptionMatrixWin1.png\
	images/download.png\
	images/Leg1.png\
	images/Leg1Leg2.png\
	images/ModelByAuthor.png\
	images/CalendarButton.png\
	images/CUSTInput.png\
	images/MonthAdjuster.png\
	images/Export.png\
	images/10.png\
	images/11.png\
	images/1.png\
	images/2.png\
	images/3.png\
	images/4.png\
	images/5.png\
	images/6.png\
	images/7.png\
	images/8.png\
	images/9.png\
	images/icon_optionmatrix128x128.png\
	images/icon_optionmatrix256x256.png\
	images/icon_optionmatrix32x32.png\
	images/icon_optionmatrix48x48.png\
	images/icon_optionmatrix64x64.png

ICO_IMAGES = \
	images/favicon.ico

EXTRA_DIST = $(EQN_IMAGES) $(TEXTFILES) $(ICO_IMAGES) README html/images/README

# Try "sudo apt-get install imagemagick" if missing ImageMagick mogrify
# under a GNU/Linux system using apt-get
.PHONY: png2eps
png2eps:
	if test -z '$(MOGRIFY)'; then \
		echo ; \
		echo ; \
		echo "mogrify not installed."; \
		echo ; \
		echo ; \
	else \
		mogrify -format eps -- images/*.png; \
		echo ; \
		echo See EPS images in images/; \
		echo ; \
	fi; 

.PHONY: clean
clean:
	-rm -f images/*.eps
	-rm -f html/images/*.png
	-rm -f html/images/*.ico
	-rm -f html/*.gz
	-rm -f html/*.html
	-rm -f html/optionmatrix.zip optionmatrix.pdf optionmatrix.info
	-rm -f optionmatrix.xml
	-rm -f optionmatrix.aux optionmatrix.ky optionmatrix.cp
	-rm -f optionmatrix.log optionmatrix.cps optionmatrix.op
	-rm -f optionmatrix.fn optionmatrix.pg optionmatrix.hhc
	-rm -f optionmatrix.hhk optionmatrix.toc optionmatrix.hhp
	-rm -f optionmatrix.tp optionmatrix.vr optionmatrix.epub
	-rm -f optionmatrix.dbk optionmatrix.txt
	-rm -f optionmatrix.dvi optionmatrix.ps
	-rm -f optionmatrix.chm optionmatrix.chw optionmatrix.xml
	-rm -f optionmatrix.htmlhelp/images/*
	-rm -f optionmatrix.htmlhelp/*.css
	-rm -f optionmatrix.htmlhelp/*.html
	-rm -f linkchecker-out.html
	-rm -f optionmatrix.texi2
	-rm -rf html/source_html/*

install-info:
	install-info --info-dir="$(DESTDIR)$(infodir)/optionmatrix" \
		"$(DESTDIR)$(infodir)/optionmatrix.info";

install-html: $(optionmatrix__TEXINFOS) $(EQN_IMAGES)
	$(MKDIR_P) $(DESTDIR)${htmldir}/optionmatrix.html/images
	for i in $(EQN_IMAGES); do cp -f ${srcdir}/$$i $(DESTDIR)${htmldir}/optionmatrix.html/images ; done
	if (test -n '$(MAKEINFO_INSTALLED)' && test -z '$(TEXI2ANY)'); then \
		echo "texi2any not installed. Using makeinfo"; \
		$(MAKEINFO) $(AM_MAKEINFOFLAGS) $(MAKEINFOFLAGS) -I $(srcdir) --html --number-sections -o $(DESTDIR)${htmldir}/optionmatrix.html $(abs_top_srcdir)/doc/optionmatrix.texi -I $(abs_top_srcdir)/doc/images/; \
		$(MAKEINFO) $(AM_MAKEINFOFLAGS) $(MAKEINFOFLAGS) -I $(srcdir) --html --no-split --no-headers -o $(DESTDIR)${htmldir}/optionmatrix.html/indexNoSplit.html $(abs_top_srcdir)/doc/optionmatrix.texi -I $(abs_top_srcdir)/doc/images/; \
	fi;
	if test -n '$(TEXI2ANY)'; then \
		echo "texi2any installed"; \
		$(MAKEINFO) $(AM_MAKEINFOFLAGS) $(MAKEINFOFLAGS) -I $(srcdir) --set-customization-variable TOP_NODE_UP_URL=https://github.com --html --number-sections -o $(DESTDIR)${htmldir}/optionmatrix.html $(abs_top_srcdir)/doc/optionmatrix.texi -I $(abs_top_srcdir)/doc/images/; \
		$(MAKEINFO) $(AM_MAKEINFOFLAGS) $(MAKEINFOFLAGS) -I $(srcdir) --set-customization-variable TOP_NODE_UP_URL=https://github.com/ --html --no-split --no-headers -o $(DESTDIR)${htmldir}/optionmatrix.html/indexNoSplit.html $(abs_top_srcdir)/doc/optionmatrix.texi -I $(abs_top_srcdir)/doc/images/; \
	fi; 
	if ( test -z '$(TEXI2ANY)' && test -z '$(MAKEINFO_INSTALLED)' ); then \
		echo "makeinfo or texi2any needs to be installed to create HTML documentation."; \
	fi;

# Create zipped HTML document file
.PHONY: zip
zip: html
	if test -z '$(ZIP)'; then \
		echo ; \
		echo ; \
		echo "zip not installed."; \
		echo ; \
		echo ; \
	else \
		zip -r html/optionmatrix.zip html/*; \
		echo ; \
		echo "See file html/optionmatrix.zip"; \
		echo ; \
	fi;

.PHONY: text
text: check_makeinfo_texi2any
	$(MAKEINFO) $(AM_MAKEINFOFLAGS) $(MAKEINFOFLAGS) -I $(srcdir) --no-headers $(DESTDIR)optionmatrix.texi -o $(DESTDIR)optionmatrix.txt
	@echo
	@echo "See file optionmatrix.txt"
	@echo

.PHONY: check_texi2any
check_texi2any:
	if test -n '$(TEXI2ANY)'; then \
		echo "texi2any is installed."; \
	fi;

.PHONY: check_makeinfo
check_makeinfo:
	if test -n '$(MAKEINFO_INSTALLED)'; then \
		echo "makeinfo is installed."; \
	fi;

.PHONY: check_makeinfo_texi2any
check_makeinfo_texi2any:
	@echo "TEXI2ANY = " $(TEXI2ANY) " MAKEINFO_INSTALLED = " $(MAKEINFO_INSTALLED)
	if ( (test -z '$(TEXI2ANY)') && (test -z '$(MAKEINFO_INSTALLED)') ); then \
		echo "makeinfo or texi2any needs to be installed."; \
		exit 1; \
	fi;

# Create HTML documentation
.PHONY: html
html: $(optionmatrix__TEXINFOS) $(EQN_IMAGES) check_makeinfo_texi2any
	if test -z '$(TEXI2ANY)'; then \
		echo "texi2any not installed. Using makeinfo"; \
		$(MAKEINFO) $(AM_MAKEINFOFLAGS) $(MAKEINFOFLAGS) -I $(srcdir) --html --number-sections -o html $(DESTDIR)optionmatrix.texi; \
		$(MAKEINFO) $(AM_MAKEINFOFLAGS) $(MAKEINFOFLAGS) -I $(srcdir) --html --no-split --no-headers -o html/indexNoSplit.html $(DESTDIR)optionmatrix.texi; \
	else \
		echo "texi2any installed"; \
		$(MAKEINFO) $(AM_MAKEINFOFLAGS) $(MAKEINFOFLAGS) -I $(srcdir) --set-customization-variable 'FRAMES=TRUE' --set-customization-variable TOP_NODE_UP_URL=https://github.com --set-customization-variable 'AFTER_BODY_OPEN=<a href="http://anthonybradford.github.io/optionmatrix/optionmatrix.pdf">OptionMatrix PDF manual</a>' --set-customization-variable 'PRE_BODY_CLOSE=<a href="http://anthonybradford.github.io/optionmatrix/optionmatrix.pdf">OptionMatrix PDF manual</a>' --html --number-sections -o html $(DESTDIR)optionmatrix.texi; \
		$(MAKEINFO) $(AM_MAKEINFOFLAGS) $(MAKEINFOFLAGS) -I $(srcdir) --set-customization-variable TOP_NODE_UP_URL=https://github.com --set-customization-variable 'AFTER_BODY_OPEN=<a href="http://anthonybradford.com/om/doc/optionmatrix.pdf">OptionMatrix PDF manual</a>' --set-customization-variable 'PRE_BODY_CLOSE=<a href="http://anthonybradford.com/om/doc/optionmatrix.pdf">OptionMatrix PDF manual</a>' --html --no-split --no-headers -o html/indexNoSplit.html $(DESTDIR)optionmatrix.texi; \
	fi;
	for i in $(EQN_IMAGES); do cp -f ${srcdir}/$$i $(DESTDIR)html/images ; done
	@echo
	@echo "See directory html/"
	@echo

# Create Frames HTML documentation
.PHONY: frames
frames: check_makeinfo_texi2any
	for i in $(EQN_IMAGES); do cp -f ${srcdir}/$$i $(DESTDIR)html/images ; done
	if test -z '$(TEXI2ANY)'; then \
		echo ; \
		echo "texi2any needed for Frames HTML"; \
		echo ; \
	else \
		$(MAKEINFO) $(AM_MAKEINFOFLAGS) $(MAKEINFOFLAGS) -I $(srcdir) --set-customization-variable 'FRAMES=TRUE' --set-customization-variable TOP_NODE_UP_URL=https://github.com --set-customization-variable 'AFTER_BODY_OPEN=<a href="http://anthonybradford.github.io/optionmatrix/optionmatrix.pdf">OptionMatrix PDF manual</a>' --set-customization-variable 'PRE_BODY_CLOSE=<a href="http://anthonybradford.github.io/optionmatrix/optionmatrix.pdf">OptionMatrix PDF manual</a>' --html --number-sections -o html $(DESTDIR)optionmatrix.texi; \
	echo ; \
	echo "See file html/optionmatrix_frame.html"; \
	echo ; \
	fi;

.PHONY: docbook
docbook: check_makeinfo_texi2any $(optionmatrix__TEXINFOS) $(EQN_IMAGES)
	sed 's/@\*/@\*\n@ifdocbook\n\n@end ifdocbook/g' $(DESTDIR)optionmatrix.texi >$(DESTDIR)optionmatrix.texi2
	$(MAKEINFO) $(AM_MAKEINFOFLAGS) $(MAKEINFOFLAGS) -I $(srcdir) \
		--docbook $(DESTDIR)optionmatrix.texi2 -o $(DESTDIR)optionmatrix.dbk
	rm $(DESTDIR)optionmatrix.texi2
	@echo
	@echo "See file optionmatrix.dbk"
	@echo

.PHONY: pdf2
pdf2: docbook
	if test -z '$(DBLATEX)'; then \
		echo ; \
		echo ; \
		echo "dblatex not installed."; \
		echo ; \
		echo ; \
	else \
		dblatex --pdf optionmatrix.dbk -o optionmatrix.pdf; \
		echo ; \
		echo "Alternative form of PDF."; \
		echo "See optionmatrix.pdf"; \
		echo ; \
	fi;

.PHONY: html2
html2: docbook
	for i in $(EQN_IMAGES); do cp -f ${srcdir}/$$i $(DESTDIR)html/images ; done
	if test -z '$(XMLTO)'; then \
		echo ; \
		echo ; \
		echo "xmlto not installed."; \
		echo ; \
		echo ; \
	else \
		xmlto --skip-validation html optionmatrix.dbk -o html; \
		echo ; \
		echo "Alternative form of HTML."; \
		echo "See directory html/"; \
		echo ; \
	fi;

.PHONY: xml
xml: check_makeinfo_texi2any $(optionmatrix__TEXINFOS) $(EQN_IMAGES)
	$(MAKEINFO) $(AM_MAKEINFOFLAGS) $(MAKEINFOFLAGS) -I $(srcdir) \
		--xml $(DESTDIR)optionmatrix.texi -o $(DESTDIR)optionmatrix.xml
	@echo
	@echo "See file optionmatrix.xml"
	@echo

# Create EPUB document
# Install dbtoepub with
# sudo apt-get install dbtoepub
.PHONY: epub
epub: docbook
	if test -z '$(DBTOEPUB)'; then \
		echo ; \
		echo ; \
		echo "dbtoepub not installed."; \
		echo ; \
		echo ; \
	else \
		dbtoepub $(DESTDIR)optionmatrix.dbk; \
		mv $(DESTDIR)optionmatrix.dbk.epub $(DESTDIR)optionmatrix.epub; \
		echo ; \
		echo "See file optionmatrix.epub"; \
		echo ; \
	fi;

# Create HTML source-highlight
.PHONY: source_html
source_html:
	if test -z '$(SOURCEHIGHLIGHT)'; then \
		echo ; \
		echo ; \
		echo "source-highlight not installed."; \
		echo ; \
		echo ; \
	else \
		$(MKDIR_P) html/source_html; \
		rm -r html/source_html/*; \
		cp -r $(top_srcdir)/* html/source_html; \
		cp $(top_srcdir)/doc/* html/source_html/doc; \
		(cd html/source_html ; find . -type f -exec source-highlight {} \; ); \
		(cd html/source_html ; find . -type f -name "*.c" -exec rm -f {} \; ); \
		(cd html/source_html ; find . -type f -name "*.cpp" -exec rm -f {} \; ); \
		(cd html/source_html ; find . -type f -name "*.cc" -exec rm -f {} \; ); \
		(cd html/source_html ; find . -type f -name "*.h" -exec rm -f {} \; ); \
		(cd html/source_html ; find . -type f -name "*.o" -exec rm -f {} \; ); \
		(cd html/source_html ; find . -type f -name "*.a" -exec rm -f {} \; ); \
		(cd html/source_html ; find . -type f -name "*.am" -exec rm -f {} \; ); \
		(cd html/source_html ; find . -type f -name "*.in" -exec rm -f {} \; ); \
		(cd html/source_html ; find . -type f -name "*.ac" -exec rm -f {} \; ); \
		(cd html/source_html ; find . -type f -name "*.gz" -exec rm -f {} \; ); \
		(cd html/source_html ; find . -type f -name "*.texi" -exec rm -f {} \; ); \
		(cd html/source_html ; find . -type f -name "*.tex" -exec rm -f {} \; ); \
		(cd html/source_html ; find . -type f -name "*.log" -exec rm -f {} \; ); \
		(cd html/source_html ; find . -type f -name "Makefile" -exec rm -f {} \; ); \
		(cd html/source_html ; find . -type f -name "ChangeLog" -exec rm -f {} \; ); \
		(cd html/source_html ; find . -type f -executable -exec rm -f {} \; ); \
		(cd html ; tar -czvf source_html.tar.gz source_html ); \
		echo ; \
		echo "See html/source_html"; \
		echo "See html/source_html.tar.gz"; \
		echo ; \
	fi;

# Run spelling checker on .texi content
# Install aspell with
# sudo apt-get install aspell
.PHONY: spelling
spelling:
	if test -z '$(ASPELL)'; then \
		echo ; \
		echo ; \
		echo "aspell not installed."; \
		echo ; \
		echo ; \
	else \
		aspell --mode=texinfo -c $(DESTDIR)optionmatrix.texi;\
	fi;

# Check diction. See 'man diction'
# Install diction with
# sudo apt-get install diction
.PHONY: diction
diction: check_makeinfo_texi2any
	if test -z '$(DICTION)'; then \
		echo ; \
		echo ; \
		echo "diction not installed."; \
		echo ; \
		echo ; \
	else \
		$(MAKEINFO) --no-headers $(DESTDIR)optionmatrix.texi -o $(DESTDIR)optionmatrix.txt; \
		diction < $(DESTDIR)optionmatrix.txt; \
	fi;

# Check style. See 'man style'
# Install style with
# sudo apt-get install diction
.PHONY: style
style: check_makeinfo_texi2any
	if test -z '$(STYLE)'; then \
		echo ; \
		echo ; \
		echo "style not installed."; \
		echo ; \
		echo ; \
	else \
		$(MAKEINFO) --no-headers $(DESTDIR)optionmatrix.texi -o $(DESTDIR)optionmatrix.txt; \
		style < $(DESTDIR)optionmatrix.txt; \
	fi;

# Check for bad HTML links
# To install linkchecker do the following
# sudo apt-get install linkchecker
# linkchecker will only work if MAKEINFO uses texi2any
.PHONY: linkchecker
linkchecker: check_makeinfo_texi2any $(optionmatrix__TEXINFOS) $(EQN_IMAGES)
	for i in $(EQN_IMAGES); do cp -f ${srcdir}/$$i $(DESTDIR)html/images ; done
	if test -z '$(LINKCHECKER)'; then \
		echo ; \
		echo ; \
		echo "linkchecker not installed."; \
		echo ; \
		echo ; \
	else \
		$(MAKEINFO) $(AM_MAKEINFOFLAGS) $(MAKEINFOFLAGS) -I $(srcdir) --html --number-sections -o html $(DESTDIR)optionmatrix.texi; \
		$(MAKEINFO) $(AM_MAKEINFOFLAGS) $(MAKEINFOFLAGS) -I $(srcdir) --set-customization-variable TOP_NODE_UP_URL=https://github.com --html --no-split --no-headers -o html/indexNoSplit.html $(DESTDIR)optionmatrix.texi; \
		linkchecker -Fhtml -o none html/index.html; \
		echo ; \
		echo "See linkchecker-out.html"; \
		echo ; \
	fi;

# Build Microsoft HTML Helper File (.chm)
# The HTML Helper only runs under Windows
.PHONY: htmlhelp
htmlhelp: check_makeinfo_texi2any $(optionmatrix__TEXINFOS) $(EQN_IMAGES)
	$(MAKEINFO) $(AM_MAKEINFOFLAGS) $(MAKEINFOFLAGS) -I $(srcdir) \
		--docbook $(DESTDIR)optionmatrix.texi
	if test -z '$(A2X)'; then \
		echo ; \
		echo ; \
		echo "a2x not installed."; \
		echo ; \
		echo ; \
	else \
		a2x -v -f htmlhelp --icons -D . optionmatrix.xml; \
		echo ; \
		echo ; \
		echo ; \
		echo "Under Cygwin or MingGW download the Microsoft HTML Help Workshop."; \
		echo "copy hhc.exe to this directory."; \
		echo "run \"./hhc.exe optionmatrix.hhp\" to generate Microsoft HTML Helper for Windows."; \
		echo "The name of the created file will be \"optionmatrix.chm\". Double click to run"; \
		echo "this file under Windows."; \
		echo ; \
		echo ; \
		echo ; \
	fi;

maintainer-clean-local:
	-rm -rf html/images/*
	-rm -rf html/*.html
