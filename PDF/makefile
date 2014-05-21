# makefile pro preklad LaTeX verze Bc. prace
# (c) 2008 Michal Bidlo
# E-mail: bidlom AT fit vutbr cz
#===========================================
# asi budete chtit prejmenovat:
PROJ=projekt
TITLE=desky

all: $(PROJ).pdf
	rm -f *.dvi *.log $(PROJ).blg $(PROJ).bbl $(PROJ).toc *.aux $(PROJ).out $(PROJ).lof
	rm -f *~

pdf: $(PROJ).pdf

$(PROJ).pdf: clean
	pdflatex $(PROJ)
	bibtex $(PROJ)
	pdflatex $(PROJ)
	pdflatex $(PROJ)


$(TITLE):
	pdflatex $(TITLE)
	rm -f $(TITLE).aux $(TITLE).log

picx:
	convert fig/bdd1.eps fig/bdd1.pdf
	convert fig/bdd2.eps fig/bdd2.pdf
	convert fig/bdd3.eps fig/bdd3.pdf
	convert fig/bdd4.eps fig/bdd4.pdf
	convert fig/bdd6.eps fig/bdd6.pdf

clean:
	rm -f *.dvi *.log $(PROJ).blg $(PROJ).bbl $(PROJ).toc *.aux $(PROJ).out $(PROJ).lof
	rm -f *~ $(TITLE).aux $(TITLE).log

del:
	rm -f *.pdf

pack:
	@tar czvf bp-xtrosk00.tar.gz *.tex *.bib *.bst ./fig/* \
makefile \
Changelog \
algorithm2e.sty \
fitthesis.cls
