inverter: inverter.cc
	g++ inverter.cc -o run
all: inverter
clean:
	rm -f run *~
