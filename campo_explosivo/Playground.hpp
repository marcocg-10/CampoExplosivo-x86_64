#ifndef PLAYGROUND_HPP
#define PLAYGROUND_HPP

#include <iostream>
#include <vector>

class Playground{
  private:
    int64_t filas;
    int64_t columnas;
    int64_t numMinas;
    int64_t casillas;
    int64_t* minas;
    int64_t misiles;
    void calcularNumeros(); // ASM
   // void generarMinas(int64_t numMinas);
 
  public:

  Playground();
  Playground(int64_t filas, int64_t columnas, int64_t numMinas, int64_t misiles);
  ~Playground();
  void iniciarTablero();
  void mostrarTablero();
  bool descubrirCelda(int64_t fila, int64_t columna); // ASM
  void esVictoria(); // ASM
  void explote();
  void cellNumber();

  int64_t* tablero;
};

extern "C" void colocar_minas(int64_t* tablero, int64_t casillas, int64_t numMinas);
extern "C" void colocar_misiles(int64_t* tablero, int64_t casillas, int64_t misiles);
extern "C" void calcular_minas_esquinas(int64_t* tablero, int64_t* esquinas);
extern "C" void borde_Superior_Inferior(int64_t* tablero, int64_t* arrayBordeSup, int64_t* arrayBordeInf);
extern "C" void borde_Izquierdo_Derecho(int64_t* tablero, int64_t* arrayBordeIzq, int64_t* arrayBordeDer);
extern "C" void contar_minas_matriz_central(int64_t* tablero, int64_t* arrayIndex);
#endif