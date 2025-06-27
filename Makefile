profile:
	g++ main.cpp compiler.cpp -o c.exe -pg -no-pie && c.exe
	gprof c.exe gmon.out -b > anaylsis.txt

run:
	g++ main.cpp compiler.cpp -o c.exe && c.exe

compile:
	g++ main.cpp compiler.cpp -o c.exe


