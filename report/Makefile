LATEX = pdflatex
LATEXFLAGS = -shell-escape
BIBTEX = bibtex
REPORT = report
TWOSIDE = report-twoside
TEMPS = toc bbl blg log out lof lot lol aux pyg

.PHONY: all clean remake purge twoside

all:
	$(LATEX) $(LATEXFLAGS) report.tex
	$(LATEX) $(LATEXFLAGS) report.tex

show: all
	xdg-open $(REPORT).pdf

# $(LATEX) $(LATEXFLAGS) $*.tex
# $(BIBTEX) $*.aux
#%.pdf:
#	$(LATEX) $(LATEXFLAGS) $*.tex
#	$(LATEX) $(LATEXFLAGS) $*.tex

clean:
	for s in $(TEMPS); do rm -f $(REPORT).$$s; done

purge: clean
	-rm -f $(REPORT).pdf

remake:
	-rm -f $(REPORT).pdf
	$(MAKE) all
