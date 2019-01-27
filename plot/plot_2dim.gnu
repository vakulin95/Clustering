set terminal png size 1280, 960
set terminal png font "Times-Roman,10"
set terminal png
set grid
set xtics auto
set ytics auto
set mxtics
set mytics
set style line 1 lc rgb 'red' pt 7 ps 1
#set style data points pointtype 7
#set style data linespoints
#set style line 1 lc rgb '#dd181f' lt 2 lw 1 pt 0 ps 0   # --- red
set xrange [0:1000]
set yrange [0:1000]
#set key outside bottom right box

plot_file1 = "data/output.dat"

set output "data/out.png"
	set title "Input"
	set xlabel "X"
	set ylabel "Y"
	
	plot plot_file1 u 1:2:3 with points ls 1 palette
unset out