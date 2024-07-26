TARGET=main.cpp
DEPENDENCIES=glad.c Shader.cpp
EXECUTABLE=a.out
LIBS=-lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
DEBUG_FLAGS=-Wall

make: $(TARGET) $(DEPENDENCIES)
	g++ $(TARGET) $(DEPENDENCIES) $(LIBS)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f *.o *.out
	touch *
