# makefile pro preklad LaTeX verze Bc. prace
# (c) 2008 Michal Bidlo
# E-mail: bidlom AT fit vutbr cz
#===========================================
# asi budete chtit prejmenovat:
CO=projekt

all: $(CO).pdf
	rm -f *.dvi *.log $(CO).blg $(CO).bbl $(CO).toc *.aux $(CO).out $(CO).lof
	rm -f *~

pdf: $(CO).pdf

$(CO).ps: $(CO).dvi
	dvips $(CO)

$(CO).pdf: clean
	pdflatex $(CO)
	bibtex $(CO)
	pdflatex $(CO)
	pdflatex $(CO)

$(CO).dvi: $(CO).tex 
	latex $(CO)
	# bibtex $(CO)
#	latex $(CO)
	latex $(CO)

desky:
#	latex desky
#	dvips desky
#	dvipdf desky
	pdflatex desky

picx:
	convert fig/bdd1.eps fig/bdd1.pdf
	convert fig/bdd2.eps fig/bdd2.pdf
	convert fig/bdd3.eps fig/bdd3.pdf
	convert fig/bdd4.eps fig/bdd4.pdf
	convert fig/bdd6.eps fig/bdd6.pdf

clean:
	rm -f *.dvi *.log $(CO).blg $(CO).bbl $(CO).toc *.aux $(CO).out $(CO).lof
	rm -f *~

del:
	rm -f $(CO).pdf
pack:
	@tar czvf bp-xtrosk00.tar.gz *.tex *.bib *.bst ./fig/* \
makefile \
Changelog \
algorithm2e.sty \
fitthesis.cls
