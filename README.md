# prime_machine
Multithreaded prime finder written in C++

## Compilation
### Dependencies
* pthread
* c++11
### Compilation
`make`, to change the compiler use `make CXX=compiler`, `make OUTPUT=whatever` to change the output file, and to change the arguments use `make LIBS=whatever`. They can be combined. Default values:
```makefile
CXX= g++
LIBS=  -pthread -std=c++11
OUTPUT= primer
```
## Usage
`./primer [limit]`
## Output format
`<prime>\n`
