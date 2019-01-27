set terminal png size 900, 900

set xtics auto
set ytics auto
set ztics auto

set mxtics
set mytics
set mztics

set grid
set style line 1 lc rgb 'red' pt 7 ps 1

plot_file = "data/output.dat"

set output "data/out.png"
	set xlabel "X"
	set ylabel "Y"
    set view 80, 80

    splot plot_file u 1:2:3:4 ls 1 palette

unset out
