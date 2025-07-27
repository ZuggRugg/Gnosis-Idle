# Overview
Here are some of the tools and techniques that I used to optimize my math parser and to make it run faster

A cycle is defined as parsing the prompts.txt file once, it is 8MB in size and usually ran over 5 cycles, you can increase that count if you want

# Techniques Used
- Profiling
- Memory Mapped Files

# Tools Used
- Flame Graph
- Gprof
- 


## The Get_Next_Token Method
The Largest bottleneck for the project was my original implementation of Get_Next_Token()
which used an if-else statement structure to figure out what was a token going character by character
in a string like so

```C++
    if (current == '+') { 
	// do something
    }

    else if (current == '-') { 
	// etc
    }

    else if (current == '*') { 
	// etc
    }
```

What ended up happening is that the function was first prioritizing the operands and then going for the digits, meaning that it was
going through each if-statement individually, we could speed this up slightly by putting everything into a switch-statement


