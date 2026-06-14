# simple makefile so i no need to write the long g++ command every time.
# just run "make" to build, and "make clean" to delete the program

CXX = g++
CXXFLAGS = -std=c++17 -Wall
TARGET = student_app
SOURCES = main.cpp Student.cpp InMemoryStudentRepository.cpp StudentService.cpp StudentController.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

# emily cruz was here :)
