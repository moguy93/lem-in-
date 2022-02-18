make fclean && make DEBUG=1
./lem-in < $1
make re
valgrind --leak-check=full ./lem-in < $1
