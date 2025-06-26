# Checklist
- [x] preform an arbitrary amount of calculations like '3+4-8*5'
- [x] Recognize left and right parentheses and Operator Precedence
- [x] Handle Floating point numbers and variables
- [x] Add support for Pos/Neg signs
- [ ] add support for Matrices
- [ ] Create AST and integrate
- [ ] add support for functions
- [ ] Rewrite and modularize everything
- [ ] Generate random math expressions
- [ ] Create Basic GUI (Window, Buttons, Camera)
- [ ] create basic gameplay loop
- [ ] show flame graphs and profiler

# TODO
- start creating functions like pow(), sin(), cos(), log()
- create some seperate function to handle matrices?
- maybe add some extra layer like analysing the properties of the numbers? (Prime, factors, etc)
- generate some new expresssions every 2 seconds then quit after 10 seconds???
- Break up the compiler.cpp file into Lexer/Parser/Interpreter
- Make Main file where everything is executed
- generate more complex expressions
- use a regex library to generate more complex expressions?
- Make this a continous thing until a limit is hit


# Description
This is a project where I am building a compiler/interpreter from scratch for an idle game 
It will also use Raylib as the graphics library for the game itself, One of the main goals behind the project is to learn
more about code optimization through tools like profilers and techniques like loop unrolling

## Gameplay Ideas
You will get randomized choices on how to improve your equation for the game, but might also have to choose which equations
would be the least detrimental for you in the long run, The Game would start preforming thousands of calculations through the Interpreter
with an Option to run the Program through an Input file to see how Optimized the Code is

## Implementation 
This Project requires C++11 or greater, and Raylib as a dependency
