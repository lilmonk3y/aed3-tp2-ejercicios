CC = g++
CCFLAGS = -std=c++11
#-D_GLIBCXX_DEBUG
DEBUG = -g


TARGET_2 = 	ejercicio_2
SOURCE_2 = ejercicio-2/ejercicio_dos.h ejercicio-2/ejercicio_dos.cpp
MAIN_2 = ejercicio-2/main.cpp

all: $(TARGET_2)

ejercicio_2:
	$(CC) $(CCFLAGS) -o $(TARGET_2) $(SOURCE_2) $(MAIN_2)
	# ./ejercicio_2 < ejercicio-2/tests/test01.txt

ejercicio_2_tester:
	$(RM) $(TARGET_2)
	$(CC) $(CCFLAGS) -o $(TARGET_2) $(SOURCE_2) $(MAIN_2)
	
clean:
	$(RM) $(TARGET_2)
