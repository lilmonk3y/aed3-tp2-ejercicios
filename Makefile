CC = g++
CCFLAGS = -std=c++11
#-D_GLIBCXX_DEBUG
DEBUG = -g
CCFLAGSOPT = -O

#ejercicio-1
TARGET_1 = ejercicio_1
SOURCE_1 =  ejercicio-1/ejercicio_uno.cpp ejercicio-1/ejercicio_uno.h
MAIN_1 = ejercicio-1/main.cpp

#ejercicio_2
TARGET_2 = 	ejercicio_2
SOURCE_2 = ejercicio-2/ejercicio_dos.h ejercicio-2/ejercicio_dos.cpp
MAIN_2 = ejercicio-2/main.cpp
TARGET_2_test = ejercicio_2_test02
MAIN_2_test = ejercicio-2/tests/test_codigo.cpp

#ejercicio_3
TARGET_3 = ejercicio_3
SOURCE_3 = ejercicio-3/ejercicio_3.cpp

all: $(TARGET_1) $(TARGET_2) $(TARGET_3)

ejercicio_1:
	$(CC) $(CCFLAGSOPT) -o $(TARGET_1) $(SOURCE_1) $(MAIN_1)


ejercicio_2:
	$(CC) $(CCFLAGS) -o $(TARGET_2) $(SOURCE_2) $(MAIN_2)
# ./ejercicio_2 < ejercicio-2/tests/test01.txt

# ejercicio_2_tester:
# 	$(RM) $(TARGET_2)
# 	$(CC) $(CCFLAGS) -o $(TARGET_2) $(SOURCE_2) $(MAIN_2)
# 	./ejercicio_2 < ejercicio-2/tests/test06.txt
#
# ejercicio_2_tests:
# 	$(CC) $(CCFLAGS) -o $(TARGET_2_test) $(SOURCE_2) $(MAIN_2_test)


ejercicio_3:
	$(CC) $(CCFLAGSOPT) -o $(TARGET_3) $(SOURCE_3)
	
clean:
	$(RM) $(TARGET_1) $(TARGET_2) $(TARGET_3)
