# Nom du compilateur
CXX = g++

# Options de compilation
CXXFLAGS = -Wall -Wextra -std=c++17

# Nom de l'exécutable
TARGET = programme

# Fichiers source
SRC = main.cpp

# Fichiers objets (générés à partir des sources)
OBJ = $(SRC:.cpp=.o)

# Règle par défaut
all: $(TARGET)

# Compilation de l'exécutable puis suppression des .o
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)
	@echo "Suppression des fichiers objets..."
	@rm -f $(OBJ)

# Compilation des .cpp en .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage manuel
clean:
	rm -f $(OBJ) $(TARGET)

# Tout nettoyer et recompiler
rebuild: clean all

.PHONY: all clean rebuild
