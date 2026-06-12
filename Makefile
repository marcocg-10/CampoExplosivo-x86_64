# Nombre del ejecutable
EXE = build/CampoExplosivo

# Directorio de compilación
BUILD_DIR = build

# Archivos fuente
ASM_SRC = campo_explosivo/campoExplosivo.asm

# Archivos fuente C++
CPP_SRC = interfaz/main.cpp interfaz/Game.cpp interfaz/MainMenu.cpp \
          interfaz/SettingsMenu.cpp interfaz/RulesMenu.cpp interfaz/HowToPlayMenu.cpp \
          interfaz/Minesweeper.cpp interfaz/GameOver.cpp campo_explosivo/Playground.cpp

# Archivos objeto
ASM_OBJ = $(BUILD_DIR)/objASM.o
CPP_OBJS = $(BUILD_DIR)/objMain.o $(BUILD_DIR)/objGame.o $(BUILD_DIR)/objMainMenu.o \
           $(BUILD_DIR)/objSettingsMenu.o $(BUILD_DIR)/objRulesMenu.o $(BUILD_DIR)/objHowToPlayMenu.o \
           $(BUILD_DIR)/objMinesweeper.o $(BUILD_DIR)/objGameOver.o $(BUILD_DIR)/objPlayground.o

# Compiladores y flags
NASM = nasm
NASM_FLAGS = -g -f elf64

GPP = g++
GPP_FLAGS = -g -Iinclude -no-pie #-fsanitize=address
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Crear directorio build si no existe
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compilación del código ensamblador
$(ASM_OBJ): $(ASM_SRC) | $(BUILD_DIR)
	$(NASM) $(NASM_FLAGS) -o $(ASM_OBJ) $(ASM_SRC)

# Compilación del código C++ (se compilan archivo por archivo)
$(BUILD_DIR)/objMain.o: interfaz/main.cpp | $(BUILD_DIR)
	$(GPP) $(GPP_FLAGS) -c -o $(BUILD_DIR)/objMain.o interfaz/main.cpp

$(BUILD_DIR)/objGame.o: interfaz/Game.cpp | $(BUILD_DIR)
	$(GPP) $(GPP_FLAGS) -c -o $(BUILD_DIR)/objGame.o interfaz/Game.cpp

$(BUILD_DIR)/objMainMenu.o: interfaz/MainMenu.cpp | $(BUILD_DIR)
	$(GPP) $(GPP_FLAGS) -c -o $(BUILD_DIR)/objMainMenu.o interfaz/MainMenu.cpp

$(BUILD_DIR)/objSettingsMenu.o: interfaz/SettingsMenu.cpp | $(BUILD_DIR)
	$(GPP) $(GPP_FLAGS) -c -o $(BUILD_DIR)/objSettingsMenu.o interfaz/SettingsMenu.cpp

$(BUILD_DIR)/objRulesMenu.o: interfaz/RulesMenu.cpp | $(BUILD_DIR)
	$(GPP) $(GPP_FLAGS) -c -o $(BUILD_DIR)/objRulesMenu.o interfaz/RulesMenu.cpp

$(BUILD_DIR)/objHowToPlayMenu.o: interfaz/HowToPlayMenu.cpp | $(BUILD_DIR)
	$(GPP) $(GPP_FLAGS) -c -o $(BUILD_DIR)/objHowToPlayMenu.o interfaz/HowToPlayMenu.cpp

$(BUILD_DIR)/objMinesweeper.o: interfaz/Minesweeper.cpp | $(BUILD_DIR)
	$(GPP) $(GPP_FLAGS) -c -o $(BUILD_DIR)/objMinesweeper.o interfaz/Minesweeper.cpp

$(BUILD_DIR)/objGameOver.o: interfaz/GameOver.cpp | $(BUILD_DIR)
	$(GPP) $(GPP_FLAGS) -c -o $(BUILD_DIR)/objGameOver.o interfaz/GameOver.cpp

$(BUILD_DIR)/objPlayground.o: campo_explosivo/Playground.cpp | $(BUILD_DIR)
	$(GPP) $(GPP_FLAGS) -c -o $(BUILD_DIR)/objPlayground.o campo_explosivo/Playground.cpp

# Enlazado final
$(EXE): $(ASM_OBJ) $(CPP_OBJS)
	$(GPP) $(GPP_FLAGS) -o $(EXE) $(ASM_OBJ) $(CPP_OBJS) $(SFML_FLAGS)

# Ejecutar el programa
run: $(EXE)
	./$(EXE)

# Limpiar archivos objeto y ejecutables
clean:
	rm -rf $(BUILD_DIR)