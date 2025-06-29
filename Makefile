profile: rand_expr.h compiler.h
	g++ main.cpp compiler.cpp -o c.exe -Wall Wextra -pg -no-pie && c.exe
	gprof c.exe gmon.out -b > anaylsis.txt
	echo "Profiling completed! go to anaylsis.txt to see results"

run: 	compiler.h rand_expr.h
	g++ main.cpp compiler.cpp -o -Wall -Wextra -pg c.exe && c.exe

compile: compiler.h rand_expr.h
	g++ main.cpp compiler.cpp -Wall -Wextra -o c.exe
	echo "compiled succesfully"

