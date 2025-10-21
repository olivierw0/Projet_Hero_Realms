# Compilateur et flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g

# Nom de l'exécutable
TARGET = hero_realms

# Fichiers sources
SOURCES = main.cpp table_partie.cpp zone_de_carte.cpp joueur.cpp carte.cpp champion.cpp effet.cpp carte_db.cpp

# Fichiers objets (générés automatiquement à partir des sources)
OBJECTS = $(SOURCES:.cpp=.o)

# Fichiers headers
HEADERS = carte.h champion.h effet.h joueur.h zone_de_carte.h table_partie.h carte_db.h

# Règle par défaut
all: $(TARGET)

# Création de l'exécutable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compilation des fichiers .cpp en .o
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Règle pour exécuter le programme
run: $(TARGET)
	./$(TARGET)

# Nettoyage des fichiers générés
clean:
	rm -f $(OBJECTS) $(TARGET) *~

# Recompilation complète
rebuild: clean all

# Vérification des dépendances
depend:
	$(CXX) -MM $(SOURCES) > dependencies.mk

# Règles qui ne correspondent pas à des fichiers
.PHONY: all run clean rebuild depend

# Inclure les dépendances si elles existent
-include dependencies.mk 

