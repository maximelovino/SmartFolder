all: specs.pdf

specs.pdf: specs.tex
	xelatex -shell-escape specs.tex
	rm -rf _minted-specs
	rm *.log *.aux
clean:
	rm specs.pdf
