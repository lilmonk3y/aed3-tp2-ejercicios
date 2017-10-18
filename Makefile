CC = g++
CCFLAGS = -std=c++11
#-D_GLIBCXX_DEBUG
DEBUG = -g


TARGET_2 = 	ejercicio_2
SOURCE_2 = ejercicio-2/ejercicio_dos.h ejercicio-2/ejercicio_dos.cpp
MAIN_2 = ejercicio-2/main.cpp
TARGET_2_test = ejercicio_2_test02
MAIN_2_test = ejercicio-2/tests/test_codigo.cpp

all: $(TARGET_2)

ejercicio_2:
	$(CC) $(CCFLAGS) -o $(TARGET_2) $(SOURCE_2) $(MAIN_2)
# ./ejercicio_2 < ejercicio-2/tests/test01.txt

ejercicio_2_tester:
	$(RM) $(TARGET_2)
	$(CC) $(CCFLAGS) -o $(TARGET_2) $(SOURCE_2) $(MAIN_2)
	./ejercicio_2 < ejercicio-2/tests/test07.txt

ejercicio_2_tests:
	$(CC) $(CCFLAGS) -o $(TARGET_2_test) $(SOURCE_2) $(MAIN_2_test)

clean:
	$(RM) $(TARGET_2) $(TARGET_2_test)
