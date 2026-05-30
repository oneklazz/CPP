# компилятор и флаги
CXX = clang++
CXXFLAGS = -std=c++17 -I src

# все .cpp файлы в src/ и подпапках
SOURCES = $(shell find src -name "*.cpp")
TARGET = five_in_a_row

# цель по умолчанию
all: $(TARGET)

# сборка
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# очистка
clean:
	rm -f $(TARGET)

# запуск
run: $(TARGET)
	./$(TARGET)