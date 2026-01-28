#ifndef PARAMETROS_H
#define PARAMETROS_H

// Tamaño de la malla espacial
const int Nx = 100;      // Número de puntos en x
const int Ny = 100;      // Número de puntos en y

// Dominio espacial
const double Lx = 40.0;  // Longitud en x
const double Ly = 10.0;  // Longitud en y

// Pasos espaciales
const double dx = Lx / (Nx - 1);
const double dy = Ly / (Ny - 1);

// Tiempo
const int Nt = 1000;     // Número de pasos de tiempo
const double T = 20.0;   // Tiempo total de simulación
const double dt = T / Nt;

// Parámetros físicos adicionales (si se requieren)
// const double c = 1.0; // Velocidad de propagación, si aplica

#endif // PARAMETROS_H