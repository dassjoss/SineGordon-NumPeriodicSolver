#include "condiciones_iniciales.h"
#include "parametros.h"
#include <cmath>

// Inicializa el campo phi en t=0 (por ejemplo, todo en cero o con una perturbación)
void inicializar_phi(std::vector<std::vector<double>> &phi) {
    for (int i = 0; i < Nx; ++i) {
        double x = i*dx - Lx/2.0;
        for (int j = 0; j < Ny; ++j) {
            // Un kink posicionado en x=0, extendido a lo largo de y
            phi[i][j] = 4.0 * atan(exp(x));
        }
    }
}

// Inicializa la derivada temporal de phi en t=0 (por ejemplo, todo en cero)
void inicializar_phi_t(std::vector<std::vector<double>> &phi_t) {
    for (int i = 0; i < Nx; ++i) {
        for (int j = 0; j < Ny; ++j) {
            phi_t[i][j] = 0.0;
        }
    }
}