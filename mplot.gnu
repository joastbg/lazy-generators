
# Plot geometric brownian motion (randomwalk.dat)

# Terminal and ranges

set title "Geometric Brownian Motion" font "Helvetica, 16"
set xlabel "Stock price"
set ylabel "Samples (n)"

drift=1.0
vol=0.2
sz = 1.0

set output "sim.eps"
set grid

plot for [col=1:10] 'mtemp.dat' using 0:col with lines lc rgb 'blue' notitle
