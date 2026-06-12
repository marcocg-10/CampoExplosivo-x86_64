#include "Playground.hpp"
#include <random>
#include <stdint.h>
#include <iomanip>  // Para setw

Playground::Playground(){

}

Playground::Playground(int64_t filas, int64_t columnas, int64_t numMinas,  int64_t misiles){
    this->filas = filas;
    this->columnas = columnas;
    this->numMinas = numMinas;
    this->casillas = columnas * filas;
    this->misiles = misiles;
    // this->minas = new int64_t[numMinas]; // NO se usa este arreglo pero se conserva de manera auxiliar
    this->tablero = new int64_t[filas * columnas];
}

Playground::~Playground(){
  delete tablero;
  //delete minas;
}

void Playground::iniciarTablero() {
  for(int64_t i = 0; i < this->filas * this->columnas; ++i){
    this -> tablero[i] = 0;
  }
  // generarMinas(numMinas);
  colocar_minas(this->tablero, this->casillas, this->numMinas);
  colocar_misiles(this->tablero, this->casillas, this->misiles);
  calcularNumeros();
}



void Playground::calcularNumeros(){
  int64_t* indice_esquinas = new int64_t[4];
  int64_t* indice_borde_sup = new int64_t[this->columnas-2];
  int64_t* indice_borde_inf = new int64_t[this->columnas-2];
  int64_t* indice_borde_izq = new int64_t[this->columnas-2];
  int64_t* indice_borde_der = new int64_t[this->columnas-2];
  int64_t tam_tablero_central = (this->columnas-2)*(this->filas-2); 
  int64_t* indice_centrales = new int64_t[tam_tablero_central];
  int64_t index = 0;
  
  for(int64_t i = 0; i < 4; ++i){
    indice_esquinas[i] = index;
    if (i == 1) {
      index = index * this->columnas;
    } else {
      index = index + (this->columnas-1);
    }
  }

  
  
  int64_t index_sup = 1;
  int64_t index_inf = 1+this->filas*(this->columnas-1);
  int64_t index_izq = this->columnas;
  int64_t index_der = (this->columnas*2)-1;
  int64_t index_cen = this->columnas + 1;

  for (int i = 0; i < 13; ++i) {
    indice_borde_sup[i] = index_sup;
    indice_borde_inf[i] = index_inf;
    indice_borde_izq[i] = index_izq;
    indice_borde_der[i] = index_der;
    index_inf++;
    index_sup++;
    index_izq+=this->filas;
    index_der+=this->filas;
  }
  int64_t cont = 0;
  for (int i = 0; i < tam_tablero_central; ++i) {
    indice_centrales[i] = index_cen;
    // std::cout << indice_centrales[i] << std::endl;
    cont++;
    if(cont == 13){
      index_cen+=3;
      cont = 0;
    }else{
      index_cen++;
    }
  }



  calcular_minas_esquinas(this->tablero, indice_esquinas);                        //ASM
  borde_Superior_Inferior(this->tablero, indice_borde_sup, indice_borde_inf);     //ASM
  borde_Izquierdo_Derecho(this->tablero, indice_borde_izq, indice_borde_der);
  contar_minas_matriz_central(this->tablero, indice_centrales);

  // delete indice_centrales;
  // delete indice_borde_der;
  // delete indice_borde_izq;
  // delete indice_borde_inf;
  // delete indice_borde_sup;
  // delete indice_esquinas;
} // ASM

// void Playground::generarMinas(int64_t numMinas) // NO se usa esta función pero se conserva de manera auxiliar
// {
//     std::random_device rd;  // Obtiene una semilla aleatoria
//     std::mt19937 gen(rd()); // Usa Mersenne Twister como generador

//     // Define el rango para la distribución uniforme
//     std::uniform_int64_t_distribution<> distrib(0, filas * columnas - 1); // Números entre 1 y 100

//     for (int64_t i = 0; i < numMinas; ++i) {
//         int64_t random_number = distrib(gen);
//         minas[i] = random_number;
//         //std::cout << minas[i] << std::endl;
//     }
// }

void Playground::mostrarTablero(){
  for(int64_t i = 1; i <= this->filas * this->columnas; ++i){
      std::cout << std::setw(4) << tablero[i-1];
    if(i % this->filas == 0){
      std::cout << std::endl;
    }
  }
  std::cout << std::endl;
}

bool Playground::descubrirCelda(int64_t fila, int64_t columna){
 return true;
} // ASM

void Playground::esVictoria(){

} // ASM

void Playground::explote(){

}

void Playground::cellNumber(){

}
