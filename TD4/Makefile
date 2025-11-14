# Nom du compilateur
CXX = g++

# Options de compilation
CXXFLAGS = -Wall -Wextra -std=c++17

# Nom de l'exécutable
TARGET = programme

# Fichiers source
SRC = main.cpp lib.cpp

# Fichiers objets
OBJ = $(SRC:.cpp=.o)

# Règle par défaut
all: $(TARGET)

# Édition de liens
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)
	@echo "Suppression des fichiers objets..."
	@rm -f $(OBJ)

# Compilation des .cpp en .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJ) $(TARGET)

# Rebuild complet
rebuild: clean all

.PHONY: all clean rebuild