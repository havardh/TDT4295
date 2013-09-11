LATEX = pdflatex
LATEXFLAGS = -shell-escape
BIBTEX = bibtex
REPORT = report
TWOSIDE = report-twoside
TEMPS = toc bbl blg log out lof lot lol aux pyg

.PHONY: clean remake purge twoside

all: $(REPORT).pdf

show: all
	evince $(REPORT).pdf

# $(LATEX) $(LATEXFLAGS) $*.tex
# $(BIBTEX) $*.aux
%.pdf:
	$(LATEX) $(LATEXFLAGS) $*.tex
	$(LATEX) $(LATEXFLAGS) $*.tex


twoside: report-twoside.pdf

clean:
	for s in $(TEMPS); do rm -f $(REPORT).$$s $(TWOSIDE).$$s; done

purge: clean
	-rm -f $(REPORT).pdf
	-rm -f $(TWOSIDE).pdf

remake:
	-rm -f $(REPORT).pdf
	$(MAKE) all
