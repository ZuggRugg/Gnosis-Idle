profile: gen_expr.h compiler.h
	g++ compiler.cpp -o c.exe -Wall -Wextra -pg -no-pie
	c.exe
	gprof c.exe gmon.out -b > anaylsis.txt
	echo "Profiling completed! go to anaylsis.txt to see results"

run: 	compiler.h gen_expr.h
	g++ main.cpp compiler.cpp -Wall -Wextra -pg -o c.exe && c.exe

compile: compiler.h gen_expr.h
	g++ main.cpp compiler.cpp -Wall -Wextra -o c.exe
	echo "compiled succesfully"


g: compiler.h gen_expr.h
	g++ main.cpp compiler.cpp -g -o c.exe && c.exe
	echo "compiled succesfully"


generate: gen_expr.h
	g++ gen_expr.cpp -o g.exe && g.exe
	echo "Generated Numbers"
