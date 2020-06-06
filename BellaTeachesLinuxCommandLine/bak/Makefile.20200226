# Texinfo Publisher.
# Copyright (C) A. Bradford 2012.

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# See file 'COPYING' for more information.

SHELL = /bin/sh
DIRS = *

# The prefix filename 'Website' is controlled in several places.
# Change the Makefile variable 'Manual = Website' to something like
# 'Manual = YourName'. Rename the Manual.texi on the command line
# with 'mv Website.texi YourName.texi'
# You must also change the '@set Manual Website' inside the .texi file to
# '@set Manual YourName'
Manual = BellaTeachesLinuxCommandLine

# Other TEXI2DVI_FLAGS that can be used are
#-D XML -D POSTSCRIPT -D DVI -D INFO -D DOCBOOK -D DJVU
TEXI2DVI_FLAGS = -D SPLIT -D NOSPLIT -D PDF -D TEXT

# Cascading Style Sheet (CSS).
# Try from the shell 'make CSS=css/janix-texinfo.css'
CSS=''

# The EPUB format needs command dbtoepub to be created
dbtoepub_exists = $(shell { type dbtoepub; } 2>/dev/null)
ifneq ($(dbtoepub_exists),)
	TEXI2DVI_FLAGS += -D DOCBOOK -D EPUB
endif

zip_exists = $(shell { type zip; } 2>/dev/null)
ifneq ($(zip_exists),)
	TEXI2DVI_FLAGS += -D ZIP
endif

ifneq (,$(findstring PDF,$(TEXI2DVI_FLAGS)))
	PRE_BODY_CLOSE = 'PRE_BODY_CLOSE=<a href="$(Manual).pdf">PDF content of this website</a>'
	AFTER_BODY_OPEN = 'AFTER_BODY_OPEN=<a href="$(Manual).pdf">PDF content of this website</a>'
else
	PRE_BODY_CLOSE = ''
	AFTER_BODY_OPEN = ''
endif

IMAGES_DIR := images

FIND_EPS_FILES = $(wildcard $(IMAGES_DIR)/*.eps)
EPS_FILES_TO_PDF = $(FIND_EPS_FILES:.eps=.pdf)

FIND_PNG_FILES = $(wildcard $(IMAGES_DIR)/*.png)
FIND_PNG_FILES_UPPERCASE = $(wildcard $(IMAGES_DIR)/*.PNG)
PNG_FILES_TO_EPS = $(FIND_PNG_FILES:.png=.eps)
PNG_FILES_TO_TXT = $(FIND_PNG_FILES:.png=.txt)
PNG_FILES_TO_LOWERCASE = $(FIND_PNG_FILES_UPPERCASE:.PNG=.png)

FIND_PNG_FILES_FILTER = $(filter-out $(wildcard $(IMAGES_DIR)/*320x240*) $(wildcard $(IMAGES_DIR)/*640x480*) $(wildcard $(IMAGES_DIR)/*960x576*), $(wildcard $(IMAGES_DIR)/*.png))
PNG_FILES_TO_960x576 = $(FIND_PNG_FILES_FILTER:.png=-960x576.png)
PNG_FILES_TO_640x480 = $(FIND_PNG_FILES_FILTER:.png=-640x480.png)
PNG_FILES_TO_320x240 = $(FIND_PNG_FILES_FILTER:.png=-320x240.png)

FIND_JPG_FILES = $(wildcard $(IMAGES_DIR)/*.jpg)
FIND_JPG_FILES_UPPERCASE = $(wildcard $(IMAGES_DIR)/*.JPG)
FIND_JPEG_FILES = $(wildcard $(IMAGES_DIR)/*.JPEG)
FIND_jpeg_FILES = $(wildcard $(IMAGES_DIR)/*.jpeg)
JPG_FILES_TO_EPS = $(FIND_JPG_FILES:.jpg=.eps)
JPG_FILES_TO_TXT = $(FIND_JPG_FILES:.jpg=.txt)
JPG_FILES_TO_PNG = $(FIND_JPG_FILES:.jpg=.png)
JPG_FILES_TO_LOWERCASE = $(FIND_JPG_FILES_UPPERCASE:.JPG=.jpg)
JPEG_FILES_TO_LOWERCASE = $(FIND_JPEG_FILES:.JPEG=.jpg)
jpeg_FILES_TO_LOWERCASE = $(FIND_jpeg_FILES:.jpeg=.jpg)

FIND_JPG_FILES_FILTER = $(filter-out $(wildcard $(IMAGES_DIR)/*320x240*) $(wildcard $(IMAGES_DIR)/*640x480*) $(wildcard $(IMAGES_DIR)/*960x576*), $(wildcard $(IMAGES_DIR)/*.jpg))
JPG_FILES_TO_960x576 = $(FIND_JPG_FILES_FILTER:.jpg=-960x576.jpg)
JPG_FILES_TO_640x480 = $(FIND_JPG_FILES_FILTER:.jpg=-640x480.jpg)
JPG_FILES_TO_320x240 = $(FIND_JPG_FILES_FILTER:.jpg=-320x240.jpg)

FIND_GIF_FILES = $(wildcard $(IMAGES_DIR)/*.gif)
GIF_FILES_TO_EPS = $(FIND_GIF_FILES:.gif=.eps)
GIF_FILES_TO_PNG = $(FIND_GIF_FILES:.gif=.png)
GIF_FILES_TO_JPG = $(FIND_GIF_FILES:.gif=.jpg)

texi2any_exists = $(shell { type texi2any; } 2>/dev/null)
xmlto_exists = $(shell { type xmlto; } 2>/dev/null)
convert_exists = $(shell { type convert; } 2>/dev/null)
linkchecker_exists = $(shell { type linkchecker; } 2>/dev/null)
aspell_exists = $(shell { type aspell; } 2>/dev/null)
diction_exists = $(shell { type diction; } 2>/dev/null)
style_exists = $(shell { type style; } 2>/dev/null)
pdf2djvu_exists = $(shell { type pdf2djvu; } 2>/dev/null)
dblatex_exists = $(shell { type dblatex; } 2>/dev/null)
epstopdf_exists = $(shell { type epstopdf; } 2>/dev/null)
jp2a_exists = $(shell { type jp2a; } 2>/dev/null)
a2x_exists = $(shell { type a2x; } 2>/dev/null)

ifneq ($(convert_exists),)
	CONVERT_JP2A_EXISTS += Y
endif
ifneq ($(jp2a_exists),)
	CONVERT_JP2A_EXISTS += Y
endif

ifneq ($(texi2any_exists),)
	TEXI2ANY = texi2any
	TEXI2DVI = texi2any
	CUSTOM = --set-customization-variable
else
	TEXI2ANY = makeinfo
	TEXI2DVI = texi2dvi
	CUSTOM = -U CUST
endif

CLEAN_OBJECTS = *.html *.zip *.pdf *.djvu *.djv *.aux *.cp *.cps *.fn *.ky *.log *.op *.pg *.toc *.tp *.vr *.txt *.xml *.dbk *.hhc *.hhk *.hhp *.htmlhelp/docbook-xsl.css *.htmlhelp/*html *.htmlhelp/images/* *.epub *.proc *.dvi *.ps *.info *.info-* *.tar.gz *~ textsplit/* plaintextsplit/* images/*.txt images/*.eps *.texi2

.PHONY: all
#all: $(PNG_FILES_TO_LOWERCASE) $(JPG_FILES_TO_LOWERCASE) $(JPEG_FILES_TO_LOWERCASE) $(jpeg_FILES_TO_LOWERCASE) $(jpeg_FILES_TO_LOWERCASE) $(Manual).tar.gz $(Manual)_PlainText.txt plaintextsplit/$(Manual).txt index.html indexNoSplit.html $(Manual).pdf $(Manual).djvu $(Manual).info $(Manual).txt textsplit/$(Manual).txt $(Manual).epub $(Manual).xml $(Manual).ps $(Manual).dvi $(Manual).zip backup message

all: $(PNG_FILES_TO_LOWERCASE) $(JPG_FILES_TO_LOWERCASE) $(JPEG_FILES_TO_LOWERCASE) $(jpeg_FILES_TO_LOWERCASE) $(jpeg_FILES_TO_LOWERCASE) $(Manual).tar.gz $(Manual)_PlainText.txt plaintextsplit/$(Manual).txt index.html indexNoSplit.html $(Manual).pdf $(Manual).djvu $(Manual).info $(Manual).txt textsplit/$(Manual).txt $(Manual).epub $(Manual).xml $(Manual).zip backup message

.PHONY: backup
backup:
	@if [ ! -d bak ]; then \
		(mkdir bak ); \
	fi;
	@cp $(Manual).texi bak/"$(Manual).texi.`date '+%Y%m%d'`"
	@cp Makefile bak/"Makefile.`date '+%Y%m%d'`"

.PHONY: message
message:
	@echo "HTML contains links to all content formats."
	@echo
	@echo "See: index.html"
	@echo "     indexNoSplit.html"
	@echo "     $(Manual)_frame.html"
	@echo '     $(Manual).pdf'
	@echo '     $(Manual).epub'
	@echo '     $(Manual).dbk'
	@echo '     $(Manual).txt'
	@echo '     $(Manual)_PlainText.txt'
	@echo '     $(Manual).info'
	@echo '     $(Manual).tar.gz'
	@echo '     $(Manual).zip'
	@echo
	@echo 'See directories plaintextsplit, textsplit.'

.PHONY: dist
dist: clean $(Manual).tar.gz

$(Manual).tar.gz:
	if [ -d ../doc ]; then \
		(cd ../.. && tar --exclude '*.eps' --exclude '.git' --exclude 'bak' -czvf $(Manual).tar.gz $(Manual) ); \
		(mv -f ../../$(Manual).tar.gz .); \
	else \
		(cd .. && tar --exclude '*.eps' --exclude '.git' --exclude 'bak' -czvf $(Manual).tar.gz $(notdir $(shell pwd)) ); \
		(mv -f ../$(Manual).tar.gz .); \
	fi;

.PHONY: html
html: all

index.html: $(Manual).texi
	@$(if $(findstring -D SPLIT,$(TEXI2DVI_FLAGS)),	\
	$(TEXI2ANY) -D LongContents $(TEXI2DVI_FLAGS) \
		$(CUSTOM) 'FRAMES=TRUE' \
		$(CUSTOM) TOP_NODE_UP_URL=.. \
		$(CUSTOM) $(PRE_BODY_CLOSE) \
		$(CUSTOM) $(AFTER_BODY_OPEN) \
		--css-include=$(CSS) \
		--html $(Manual).texi -o . \
	)

indexNoSplit.html: $(Manual).texi
	@$(if $(findstring -D NOSPLIT,$(TEXI2DVI_FLAGS)), \
	$(TEXI2ANY) -D LongContents $(TEXI2DVI_FLAGS) \
		$(CUSTOM) TOP_NODE_UP_URL=.. \
		--no-split --no-headers \
		$(CUSTOM) $(PRE_BODY_CLOSE) \
		$(CUSTOM) $(AFTER_BODY_OPEN) \
		--css-include=$(CSS) \
		--html $(Manual).texi -o indexNoSplit.html \
	)

.PHONY: frame
.PHONY: frames
frame: frames
frames: $(Manual)_frame.html
$(Manual)_frame.html: $(Manual).texi
	@-rm -f *.html
	$(TEXI2ANY) \
		-D LongContents \
		$(TEXI2DVI_FLAGS) \
		$(CUSTOM) 'FRAMES=TRUE' \
		$(CUSTOM) TOP_NODE_UP_URL=.. \
		$(CUSTOM) $(PRE_BODY_CLOSE) \
		$(CUSTOM) $(AFTER_BODY_OPEN) \
		--css-include=$(CSS) \
		--html $(Manual).texi -o .
	@echo
	@echo "Frame HTML created. See $(Manual)_frame.html"

.PHONY: pdf2
pdf2: docbook
ifneq ($(dblatex_exists),)
	dblatex --pdf $(Manual).dbk -o $(Manual).pdf
	@echo
	@echo "Alternative form of PDF."
	@echo "PDF created. See $(Manual).pdf"
else
	@echo "Program \"dblatex\" missing."
	@echo "Run or read file 'configure' for information on adding this program."
endif

.PHONY: html2
html2: docbook
ifneq ($(xmlto_exists),)
	@-rm -f *.html
	xmlto --skip-validation html $(Manual).dbk
	@echo
	@echo "Alternative form of HTML."
	@echo "Use \"make all\" for regular HTML."
	@echo "To view type:"
	@echo "               firefox index.html (UNIX/Linux)"
	@echo "               nautilus .          (GNOME Desktop)"
	@echo "               explorer .          (Windows/Cygwin)"
	@echo "               explorer index.html (Windows/Cygwin)"
else
	@echo "Program \"xmlto\" missing."
	@echo "Run or read file 'configure' for information on adding this program."
endif

.PHONY: xml
xml: TEXI2DVI_FLAGS += -D XML
xml: $(Manual).xml
$(Manual).xml: $(Manual).texi
	@$(if $(findstring -D XML,$(TEXI2DVI_FLAGS)), $(TEXI2ANY) --xml $(Manual).texi ; echo "XML created. See $(Manual).xml" )

.PHONY: dbk
.PHONY: docbook
dbk: docbook
docbook: TEXI2DVI_FLAGS += -D DOCBOOK
docbook: $(Manual).dbk
$(Manual).dbk: $(Manual).texi
	@$(if $(findstring -D DOCBOOK,$(TEXI2DVI_FLAGS)), $(TEXI2ANY) --docbook $(Manual).texi -o $(Manual).dbk; echo "DocBook created. See $(Manual).dbk" )

$(Manual).texi2:
$(Manual).texi2: $(Manual).texi
	sed 's/@\*/@\*\n@ifdocbook\n\n@end ifdocbook/g' $(Manual).texi >$(Manual).texi2
	texi2any --docbook $(Manual).texi2 -o $(Manual).dbk

.PHONY: pdf
pdf: TEXI2DVI_FLAGS += -D PDF
pdf: $(Manual).pdf
$(Manual).pdf: $(Manual).texi
	@$(if $(findstring -D PDF,$(TEXI2DVI_FLAGS)), $(TEXI2DVI) --pdf $(Manual).texi -o $(Manual).pdf ; echo "PDF created. See $(Manual).pdf" )

.PHONY: djvu
djvu: TEXI2DVI_FLAGS += -D PDF -D DJVU
djvu: $(Manual).djvu
$(Manual).djvu: $(Manual).pdf
ifneq ($(pdf2djvu_exists),)
	@$(if $(findstring -D DJVU,$(TEXI2DVI_FLAGS)), pdf2djvu -o $(Manual).djvu $(Manual).pdf ; echo "DjVu file created. See $(Manual).djvu" )
else
	@echo "Program \"pdf2djvu\" missing."
	@echo "Run or read file 'configure' for information on adding this program."
endif

.PHONY: epub
epub: TEXI2DVI_FLAGS += -D EPUB -D DOCBOOK
epub: $(Manual).epub
$(Manual).epub: $(Manual).dbk
ifneq ($(dbtoepub_exists),)
	@$(if $(findstring -D EPUB,$(TEXI2DVI_FLAGS)), dbtoepub $(Manual).dbk ; mv -f $(Manual).dbk.epub $(Manual).epub ; echo "EPUB created with images. See $(Manual).epub" ; echo "$(Manual).epub can be imported into a EPUB e-book" ; echo "editor such as sigil." )
else
	@echo "Program \"dbtoepub\" missing."
	@echo "\"dbtoepub\" is needed to generate EPUB documents."
	@echo "Run or read file 'configure' for information on adding this program."
endif

.PHONY: plaintext
plaintext: TEXI2DVI_FLAGS += -D TEXT
plaintext: $(Manual)_PlainText.txt
$(Manual)_PlainText.txt: $(Manual).texi
	@-rm -f images/*.txt
	$(TEXI2ANY) --no-headers $(Manual).texi -o $(Manual)_PlainText.txt
	@echo
	@echo "Plain text created. Images have NOT been converted to ASCII. See $(Manual).txt"

.PHONY: plaintextsplit
plaintextsplit: TEXI2DVI_FLAGS += -D TEXT
plaintextsplit: plaintextsplit/$(Manual).txt
plaintextsplit/$(Manual).txt: $(Manual).texi
	@-rm -f images/*.txt
	@$(if $(findstring -D TEXT,$(TEXI2DVI_FLAGS)), $(TEXI2ANY) --split=chapter --no-headers $(Manual).texi -o plaintextsplit ; echo "Split plain text created. Images have NOT been converted to ASCII. See directory plaintextsplit" )

.PHONY: txt
txt: text
.PHONY: text
text: TEXI2DVI_FLAGS += -D TEXT
text: $(Manual).txt
$(Manual).txt: $(Manual).texi $(JPG_FILES_TO_TXT) $(PNG_FILES_TO_TXT)
	@$(if $(findstring -D TEXT,$(TEXI2DVI_FLAGS)), $(TEXI2ANY) --no-headers $(Manual).texi -o $(Manual).txt ; echo "Plain text created. Images converted to ASCII. See $(Manual).txt" )

.PHONY: textsplit
textsplit: TEXI2DVI_FLAGS += -D TEXT
textsplit: textsplit/$(Manual).txt
textsplit/$(Manual).txt: $(Manual).texi $(JPG_FILES_TO_TXT) $(PNG_FILES_TO_TXT)
	@$(if $(findstring -D TEXT,$(TEXI2DVI_FLAGS)), $(TEXI2ANY) --split=chapter --no-headers $(Manual).texi -o textsplit ; echo "Split plain text created. Images converted to ASCII. See directory textsplit" )

.PHONY: zip
zip: TEXI2DVI_FLAGS += -D ZIP
zip: all $(Manual).zip
$(Manual).zip: $(Manual).texi
	@-rm -f $(Manual).aux $(Manual).cp $(Manual).cps $(Manual).fn $(Manual).ky $(Manual).op $(Manual).pg $(Manual).toc $(Manual).tp $(Manual).vr $(Manual).log
ifneq ($(zip_exists),)
	@$(if $(findstring -D ZIP,$(TEXI2DVI_FLAGS)), zip -r $(Manual).zip * --exclude *.eps *.zip bak/* images/bak/* $(Manual).tar.gz)
else
	@echo "Program \"zip\" missing."
	@echo "Run or read file 'configure' for information on adding this program."
endif

.PHONY: info
info: TEXI2DVI_FLAGS += -D INFO
info: $(Manual).info
	@$(if $(findstring -D INFO,$(TEXI2DVI_FLAGS)), \
		$(TEXI2DVI) $(Manual).texi \
	)

.PHONY: postscript
.PHONY: ps
postscript: ps
ps: TEXI2DVI_FLAGS += -D POSTSCRIPT
ps: $(Manual).ps
$(Manual).ps: $(Manual).texi $(JPG_FILES_TO_EPS) $(PNG_FILES_TO_EPS) $(GIF_FILES_TO_EPS)
	@$(if $(findstring -D POSTSCRIPT,$(TEXI2DVI_FLAGS)), $(TEXI2DVI) --ps $(Manual).texi; echo "PostScript created. See $(Manual).ps" )

.PHONY: dvi
dvi: TEXI2DVI_FLAGS += -D DVI
dvi: $(Manual).dvi
$(Manual).dvi: $(Manual).texi $(JPG_FILES_TO_EPS) $(PNG_FILES_TO_EPS) $(GIF_FILES_TO_EPS)
	@$(if $(findstring -D DVI,$(TEXI2DVI_FLAGS)), $(TEXI2DVI) --dvi $(Manual).texi ; echo "Device independent file format (DVI) created. See $(Manual).dvi" )

# Build Microsoft HTML Helper File (.chm)
# The HTML Helper only runs under Windows
.PHONY: htmlhelp
.PHONY: htmlhelper
htmlhelper: htmlhelp
htmlhelp: $(Manual).hhp
$(Manual).hhp: $(Manual).texi $(Manual).texi2
ifneq ($(a2x_exists),)
	@mv -f $(Manual).dbk $(Manual).xml
	a2x -v -f htmlhelp --icons -D . $(Manual).xml
	@echo
	@echo "Under Cygwin or MingGW download the Microsoft HTML Help Workshop."
	@echo "copy hhc.exe to this directory."
	@echo "run \"./hhc.exe $(Manual).hhp\" to generate Microsoft HTML Helper for Windows."
	@echo "The name of the created file will be \"$(Manual).chm\". Double click to run"
	@echo "this file under Windows. Microsoft HTML Helper files will not run from"
	@echo "network drives."
	#./hhc.exe $(Manual).hhp
else
	@echo "Program \"a2x\" missing."
	@echo "Run or read file 'configure' for information on adding this program."
endif

# Run spelling checker on .texi content
.PHONY: spell
.PHONY: spelling
spell: spelling
spelling:
ifneq ($(aspell_exists),)
	aspell --mode=texinfo -c $(Manual).texi
else
	@echo "Program \"aspell\" missing."
	@echo "Run or read file 'configure' for information on adding this program."
endif

# Check diction. For more information type 'man diction' on the command line.
.PHONY: diction
diction:
ifneq ($(diction_exists),)
	@-rm -f images/*.txt
	$(TEXI2ANY)  --no-headers \
		$(Manual).texi -o $(Manual).txt
	diction < $(Manual).txt
else
	@echo "Program \"diction\" missing."
	@echo "Run or read file 'configure' for information on adding this program."
endif

# Check style. For more information type 'man style' on the command line.
.PHONY: style
style:
ifneq ($(style_exists),)
	@-rm -f images/*.txt
	$(TEXI2ANY)  --no-headers \
		$(Manual).texi -o $(Manual).txt
	style < $(Manual).txt
else
	@echo "Program \"style\" missing."
	@echo "Run or read file 'configure' for information on adding this program."
endif

.PHONY: resize
resize: backup_images resizejpg resizepng

.PHONY: resizejpg
resizejpg: $(JPG_FILES_TO_960x576) $(JPG_FILES_TO_640x480) $(JPG_FILES_TO_320x240)

images/%-960x576.jpg: images/%.jpg
ifneq ($(convert_exists),)
	convert '$<' -resize 960x576 '$@'
else
	@echo "Program \"convert\" missing."
	@echo "Run or read file 'configure' for information on adding this program."
endif

images/%-640x480.jpg: images/%.jpg
ifneq ($(convert_exists),)
	convert '$<' -resize 640x480 '$@'
else
	@echo "Program \"convert\" missing."
	@echo "Run or read file 'configure' for information on adding this program."
endif

images/%-320x240.jpg: images/%.jpg
ifneq ($(convert_exists),)
	convert '$<' -resize 320x240 '$@'
else
	@echo "Program \"convert\" missing."
	@echo "Run or read file 'configure' for information on adding this program."
endif

.PHONY: resizepng
resizepng: $(PNG_FILES_TO_960x576) $(PNG_FILES_TO_640x480) $(PNG_FILES_TO_320x240)

images/%-960x576.png: images/%.png
ifneq ($(convert_exists),)
	convert '$<' -resize 960x576 '$@'
else
	@echo "Program \"convert\" missing."
	@echo "Run or read file 'configure' for information on adding this program."
endif

images/%-640x480.png: images/%.png
ifneq ($(convert_exists),)
	convert '$<' -resize 640x480 '$@'
else
	@echo "Program \"convert\" missing."
	@echo "Run or read file 'configure' for information on adding this program."
endif

images/%-320x240.png: images/%.png
ifneq ($(convert_exists),)
	convert '$<' -resize 320x240 '$@'
else
	@echo "Program \"convert\" missing."
	@echo "Run or read file 'configure' for information on adding this program."
endif

.PHONY: backup_images
backup_images:
	if [ ! -d images ]; then \
		(mkdir images ) ; \
	fi;
	if [ ! -d images/bak ]; then \
		(mkdir images/bak ) ; \
	fi;
	find ./images/ -maxdepth 1 -type f -exec cp {} ./images/bak \;
	@echo All images in ./images backed up to ./images/bak

.PHONY: png2eps
png2eps: $(PNG_FILES_TO_EPS)

images/%.eps: images/%.png
ifneq ($(convert_exists),)
	convert '$<' '$@'
else
	@echo "Program \"convert\" missing."
	@echo "Run or read file 'configure' for information on adding this program."
endif

.PHONY: jpg2eps
jpg2eps: $(JPG_FILES_TO_EPS)

images/%.eps: images/%.jpg
ifneq ($(convert_exists),)
	convert '$<' '$@'
else
	@echo "Program \"convert\" missing."
	@echo "Run or read file 'configure' for information on adding this program."
endif

.PHONY: gif2eps
gif2eps: $(GIF_FILES_TO_EPS)

images/%.eps: images/%.gif
ifneq ($(convert_exists),)
	convert '$<' '$@'
else
	@echo "Program \"convert\" missing."
	@echo "Run or read file 'configure' for information on adding this program."
endif

.PHONY: jpg2txt
jpg2txt: $(JPG_FILES_TO_TXT)

images/%.txt: images/%.jpg
ifneq ($(jp2a_exists),)
	jp2a --width=155  '$<' > '$@'
else
	@echo "Program \"jp2a\" missing."
	@echo "Run or read file 'configure' for information on adding this program."
endif

.PHONY: png2txt
png2txt: $(PNG_FILES_TO_TXT)

images/%.txt: images/%.png
ifeq ($(CONVERT_JP2A_EXISTS),Y Y)
	convert '$<' jpg:- | jp2a - --width=155 > '$@'
else
	@echo "Program \"convert\" or \"jp2a\" missing."
	@echo "Run or read file 'configure' for information on adding this program."
endif

images/%.jpg: images/%.JPG
	mv '$<' '$@'

images/%.jpg: images/%.JPEG
	mv '$<' '$@'

images/%.jpg: images/%.jpeg
	mv '$<' '$@'

images/%.png: images/%.PNG
	mv '$<' '$@'

.PHONY: gif2png
gif2png: $(GIF_FILES_TO_PNG)

images/%.png: images/%.gif
ifneq ($(convert_exists),)
	convert '$<' '$@'
else
	@echo "Program \"convert\" missing."
	@echo "Run or read file 'configure' for information on adding this program."
endif

.PHONY: gif2jpg
gif2jpg: $(GIF_FILES_TO_JPG)

images/%.jpg: images/%.gif
ifneq ($(convert_exists),)
	convert '$<' '$@'
else
	@echo "Program \"convert\" missing."
	@echo "Run or read file 'configure' for information on adding this program."
endif

.PHONY: jpg2png
jpg2png: $(JPG_FILES_TO_PNG)

images/%.png: images/%.jpg
ifneq ($(convert_exists),)
	convert '$<' '$@'
else
	@echo "Program \"convert\" missing."
	@echo "Run or read file 'configure' for information on adding this program."
endif

.PHONY: eps2pdf
eps2pdf: $(EPS_FILES_TO_PDF)

images/%.pdf: images/%.eps
ifneq ($(convert_exists),)
	convert '$<' '$@'
else
	@echo "Program \"convert\" missing."
	@echo "Run or read file 'configure' for information on adding this program."
endif

# Check for bad links
.PHONY: linkchecker
linkchecker: all
ifneq ($(linkchecker_exists),)
	linkchecker -Fhtml index.html
	@echo
	@echo
	@echo
	@echo See file: linkchecker-out.html
	@echo
	@echo
	@echo
else
	@echo "Program \"linkchecker\" missing."
	@echo "Run or read file 'configure' for information on adding this program."
endif

# Print help information
.PHONY: help
help:
	if [ -e README ]; then \
		(less README ); \
	else \
		(echo "No help available") ; \
	fi;

.PHONY: nothing
nothing:
	@echo "Nothing done."

.PHONY: exists
exists:
	@echo $(dbtoepub_exists)
	@echo $(zip_exists)
	@echo $(texi2any_exists)
	@echo $(xmlto_exists)
	@echo $(convert_exists)
	@echo $(linkchecker_exists)
	@echo $(aspell_exists)
	@echo $(diction_exists)
	@echo $(style_exists)
	@echo $(pdf2djvu_exists)
	@echo $(dblatex_exists)
	@echo $(epstopdf_exists)
	@echo $(jp2a_exists)
	@echo $(a2x_exists)

.PHONY: distclean
distclean: clean
	@-rm -f bak/*
	@-rm -f images/bak/*

.PHONY: clean
clean:
	@-rm -f $(CLEAN_OBJECTS)
	for d in $(DIRS); do\
		if [ -d $$d ] && [ -e "$$d/Makefile" ]; then\
			(cd $$d; $(MAKE) clean );\
		fi;\
	done
