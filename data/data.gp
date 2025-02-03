set terminal pngcairo size 1600,1000 enhanced font "Arial,16"
set output 'pics/algorithms_bsearch_isearch.png'

set title "Comparação de Algoritmos de Busca (Pior Caso) - Sem Linear Search" font "Arial,18"
set xlabel "Tamanho do Array" font "Arial,16"
set ylabel "Tempo (microsegundos)" font "Arial,16"

set logscale x 10   # Escala logarítmica no eixo X
set logscale y 10   # Escala logarítmica no eixo Y (se os valores variarem muito)
set grid xtics ytics lw 1 lc rgb "#bbbbbb" # Linhas de grade mais visíveis

set key outside right top font "Arial,14" # Ajustar legenda para não sobrepor o gráfico
set border lw 2 # Deixa as bordas do gráfico mais visíveis
set style fill solid 0.5 # Melhor preenchimento de pontos

# Definição de estilos de linha mais visíveis
set style line 1 lc rgb "#ff7f0e" lw 3 pt 5 ps 1.5 # Laranja (BSearch)
set style line 4 lc rgb "#9467bd" lw 3 pt 3 ps 1.5 # Roxo (UBound)
set style line 6 lc rgb "#e377c2" lw 3 pt 4 ps 1.5 # Rosa (ISearch)

# Suavizar as curvas
set samples 1000

plot "data/data_1000.txt" using 1:3 smooth csplines title "BSearch" ls 1, \
 "data/data_1000.txt" using 1:4 smooth csplines title "BSearch_Rec" ls 2, \
     "data/data_1000.txt" using 1:8 smooth csplines title "ISearch" ls 6, 
