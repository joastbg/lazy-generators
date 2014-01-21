set key left noreverse enhanced autotitles box linetype -1 linewidth 1.000
#plot 'temp.dat' using 0:1 with lines lc rgb 'blue' ti "geometric brownian motion"
#plot 'temp.dat' with lines lc rgb 'blue' ti "geometric brownian motion"
set xrange [0:2*365]
set xlabel "Time"
set ylabel "Price"
set title "Geometric Brownian Motion" font "Helvetica, 16"
plot "temp.dat" index 0:19 with lines lc rgb "blue" ti "simulations", "" index 20 with lines lc rgb "red" lw 4 ti "expected"
