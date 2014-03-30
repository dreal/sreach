statsmt_sq: statsmt_sq.o replace.o simulation.o pdrh2drh.o
	g++ pdrh2drh.o simulation.o replace.o statsmt_sq.o -lboost_regex -lgsl -o statsmt_sq

statsmt_sq.o: statSMT_sq.cpp replace.hpp simulation.hpp pdrh2drh.hpp
	g++ statSMT_sq.cpp -c -o statsmt_sq.o

replace.o: replace.cpp replace.hpp
	g++ replace.cpp -c -o replace.o

simulation.o: simulation.cpp simulation.hpp
	g++ simulation.cpp -c -o simulation.o

pdrh2drh.o: pdrh2drh.cpp pdrh2drh.hpp
	g++ pdrh2drh.cpp -c -o pdrh2drh.o

clean:
	rm statsmt_sq.o replace.o simulation.o pdrh2drh.o statsmt_sq
