CC = g++
CCFLAGS = -std=c++11 -D_GLIBCXX_DEBUG
DEBUG = -g

TARGET_2 = 	ejer-2
SOURCE_2 =

all: $(TARGET_2)

ejercicio-2:
	$(CC) $(CCFLAGS) -o $(TARGET_2) $(SOURCE_2)

clean:
	$(RM) $(TARGET_2)
