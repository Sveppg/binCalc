cc = gcc -Wall -Wextra -Werror
.c-file = binCalc.c
-o.file = binCalc.o
exec = binCalc

all: comp obj run
comp: 
  @$(cc) -c $(.c-file)
obj: $(comp)
  @$(cc) .o $(exec) $(.o-file)
run: $(exec)
  @./$(exec)
clean: @rm -f $(exec) $(.o-file)
