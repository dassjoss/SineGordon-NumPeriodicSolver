#ifndef CONDICIONES_INICIALES_H
#define CONDICIONES_INICIALES_H

#include <vector>

// Inicializa el campo phi en t=0
void inicializar_phi(std::vector<std::vector<double>> &phi);

// Inicializa la derivada temporal de phi en t=0
void inicializar_phi_t(std::vector<std::vector<double>> &phi_t);

#endif // CONDICIONES_INICIALES_H
