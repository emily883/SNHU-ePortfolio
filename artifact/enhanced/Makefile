# simple makefile so i no need to write the long g++ command every time.
# just run "make" to build, and "make clean" to delete the program.
# module 5: now i link sqlite (the database) and crypto (for password hash)

CXX = g++
CXXFLAGS = -std=c++17 -Wall
TARGET = student_app
SOURCES = main.cpp Student.cpp \
          InMemoryStudentRepository.cpp SqliteStudentRepository.cpp \
          StudentService.cpp StudentController.cpp \
          SqliteUserRepository.cpp PasswordHasher.cpp AuthService.cpp
LDLIBS = -lsqlite3 -lcrypto

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET) $(LDLIBS)

clean:
	rm -f $(TARGET) *.o *.db

# emily cruz was here :)
