#Target to make and objects needed
TARGET = main
OBJS = $(TARGET).o MergeSorter.o BubbleSorter.o InsertionSorter.o SortingAudialVisualization.o AudialVisualization.o SelectionSorter.o ShakerSorter.o LinearSearch.o

#Compiler, remove command, and OS we're working on
CC = g++
RM = rm -f
UNAME := $(shell uname)

#Check if we're on a Mac or a Linux machine

#Linux
ifeq ($(UNAME), Linux)
	OS_LFLAGS :=
	OS_INCLUDE :=
	OS_LDIRS := -L/usr/lib -L/usr/local/lib
	OS_EXTRA_LIB := 
	OS_GLFW := glfw
	OS_GL := -lGL
endif

#Mac
ifeq ($(UNAME), Darwin)
	OS_LFLAGS := -framework Cocoa -framework OpenGl -framework IOKit -framework Corevideo
	OS_INCLUDE := 
	OS_LDIRS := 
	OS_EXTRA_LIB := 
	OS_GLFW := glfw3
	OS_GL :=
	OS_EXTRA_LINK :=
endif

#Compiler flags
CXXFLAGS=-c -O3 -g3 \
    -Wall -Wextra -pedantic-errors \
    -I/usr/include/ \
    -I/usr/include/TSGL/ \
    ${OS_INCLUDE} \
    -I/usr/include/freetype2/ \
    -I/usr/include/freetype2/freetype  \
    -I/usr/local/include/tsal/ \
    -std=c++11 -fopenmp \
    -Wno-unused-function #Supress warnings

#Linking flags
LFLAGS=-o $(TARGET) \
    ${OS_EXTRA_LIB} \
	${OS_LDIRS} \
    ${OS_EXTRA_LINK} \
    -ltsgl -lfreetype \
    -lGLEW -l${OS_GLFW} \
    -lportaudio \
    -ltsal \
    -lX11 ${OS_GL} -lXrandr \
	-L/usr/lib \
	-L/usr/local/lib \
    -fopenmp \
    ${OS_LFLAGS}

.SUFFIXES: .cpp .o

#all command
all: $(TARGET)

#Linking
$(TARGET): $(OBJS)
	@echo "\nLinking $(TARGET)..."
	$(CC) $(OBJS) $(LFLAGS)
	@echo

# $(TARGET).o : main.cpp MergeSort.cpp
# 	$(CC) -c main.cpp

# MergeSort.o : MergeSort.cpp
# 	$(CC) -c MergeSort.cpp

# SortingAudialVisualizations.o : SortingAudialVisualizations.cpp
# 	$(CC) -c SortingAudialVisualizations.cpp

# AudialVisualization.o : AudialVisualization.cpp
# 	$(CC) AudialVisualization.cpp $(CXXFLAGS)
	
#Compiling
.cpp.o:
	@echo "\nCompiling $<..."
	$(CC) $(CXXFLAGS) $< 

#Clean command
clean:
	$(RM) $(TARGET) $(OBJS) *~
