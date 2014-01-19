CXXFLAGS = -pipe -O2 -Wall -W -ansi -pedantic-errors
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast

all: lazy
	g++ -c $(CXXFLAGS) lazy.cc

clean:
	rm -rf *o lazy temp.dat

run: lazy
	./lazy > ./temp.dat && gnuplot -persist plot.gnu
