ofiles = main.o DistanceFunction.o DataPoint.o Algorithm.o
gpp_0 = g++ -c -std=c++98

act1.out: $(ofiles)
	g++ -std=c++98 $(ofiles) -o act1.out

main.o: main.cpp DataPoint.h DistanceFunction.h Algorithm.h
	$(gpp_0) main.cpp

DataPoint.o: DataPoint.cpp 
	$(gpp_0) DataPoint.cpp

DistanceFunction.o: DistanceFunction.cpp
	$(gpp_0) DistanceFunction.cpp

Algorithm.o: Algorithm.cpp
	$(gpp_0) Algorithm.cpp		

run: 
	./act1.out

clean:
	rm *.o act1.out