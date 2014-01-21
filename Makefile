CXXFLAGS = -pipe -O2 -Wall

all: lazy
	g++ -lpthread -lboost_thread -lboost_system -c $(CXXFLAGS) lazy.cc -lboost_system

clean:
	rm -rf *o lazy temp.dat

run: 
	./lazy > ./temp.dat && gnuplot -persist plot.gnu
