inverter: inverter.cc
	g++ inverter.cc -o inverter
all: inverter
clean:
	rm -f inverter *~
