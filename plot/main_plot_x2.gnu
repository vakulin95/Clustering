set terminal png size 1280, 960
set terminal png font "Times-Roman,10"
set terminal png
set grid
set xtics auto
set ytics auto
set mxtics
set mytics
set style data linespoints
set style line 1 lc rgb '#0060ad' lt 1 lw 1 pt 0 ps 1   # --- blue
set style line 2 lc rgb '#dd181f' lt 2 lw 1 pt 0 ps 1   # --- red

#set yrange [-0.3:8]
#set key outside bottom right box

plot_file1 = "data/outdat1.dat"
plot_file2 = "data/outdat2.dat"

title1 = "1"
title2 = "2"

set output "data/out_time.png"
	set title ""
	set xlabel "N"
	set ylabel "t, с"
	#plot plot_file1 u 1 title title1 ls 1, plot_file1 u 2 title title2 ls 2
	plot plot_file1 u 1:2 title title1 ls 1, plot_file2 u 1:2 title title2 ls 2
unset out
