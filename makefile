Resultados_hw5.pdf:Resultados_hw5.tex
	pdflatex Resultados_hw5.tex
Resultados_hw5.tex:fig%.png fig_2%.png
	pdflatex Resultados_hw5.tex
fig%.png fig_2%.png:plots_canal_ionico.py circuitoRC.py
	python plots_canal_ionico.py
	python circuitoRC.py
plots_canal_ionico.py:canal_ionico.x
	./canal_ionico.x
canal_ionico.x:canal_ionico.c
	gcc canal_ionico.c -lm -o canal_ionico.x
