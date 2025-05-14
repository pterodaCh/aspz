FROM gcc 
COPY task1var2.c .

RUN apt-get update
RUN apt-get upgrade -y
RUN apt install build-essential valgrind  -y
RUN gcc -Wall task1var2.c -o task1var 
CMD ["valgrind","--leak-check=full","--show-leak-kinds=all","./task1var"]
