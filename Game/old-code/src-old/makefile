# the compiler: gcc for C program, define as g++ for C++
	CC = g++
 
	# compiler flags:
	#  -g     - this flag adds debugging information to the executable file
	#  -Wall  - this flag is used to turn on most compiler warnings
	CFLAGS  = -g -W

LIBS = -lglfw3 -lassimp -ldl -lGL -lX11 
$(target): $(target).cc glad.c shader.cc mesh.cpp instantiate.cc
	$(CC) -o $(target) $(target).cc glad.c shader.cc mesh.cpp -I../include $(CFLAGS) $(LIBS) 
#