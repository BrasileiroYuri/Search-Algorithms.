set terminal pngcairo size 1280,720 enhanced font 'Arial,14'
set output 'busca_comparacao.png'

# Melhorando os rótulos e título
set title 'Comparação de Algoritmos de Busca (Pior Caso)' font ',16'
set xlabel 'Tamanho do Array' font ',14'
set ylabel 'Tempo (microssegundos)' font ',14'

# Ajustando escala logarítmica para melhor visualização
set logscale x 10
set logscale y 10
set format y "10^%T"

# Adicionando grid para melhor leitura
set grid

# Limitando o eixo Y para evitar ruídos extremos (ajuste conforme necessário)
set yrange [100:1e6]

# Melhorando a posição da legenda
set key outside right top font ',12'

# Plotando os dados suavizados e reduzindo densidade de pontos
plot  'data/data_1000.txt' using 1:3 smooth unique with lines lw 2 title 'BSearch' linecolor rgb "orange", \
     'data/data_1000.txt' using 1:4 smooth unique with lines lw 2 title 'BSearchRec' linecolor rgb "green", \
     'data/data_1000.txt' using 1:5 smooth unique with lines lw 2 title 'LBound' linecolor rgb "red", \
     'data/data_1000.txt' using 1:6 smooth unique with lines lw 2 title 'UBound' linecolor rgb "purple", \
     'data/data_1000.txt' using 1:7 smooth unique with lines lw 2 title 'TSearch' linecolor rgb "brown", \
     'data/data_1000.txt' using 1:8 smooth unique with lines lw 2 title 'ISearch' linecolor rgb "black", \
     'data/data_1000.txt' using 1:9 smooth unique with lines lw 2 title 'ESearch' linecolor rgb "gray"
