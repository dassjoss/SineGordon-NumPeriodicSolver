#include<iostream>
#include<vector>
#include<cmath>
#include<fstream>
#include<string>
#include "parametros.h"
#include "condiciones_iniciales.h"

using namespace std;

//Función para calcular la energía total
double calcular_energia(const vector<vector<double>>& curr, const vector<vector<double>>& old) {
    double energia = 0.0;
    for (int i = 1; i < Nx - 1; ++i) {
        for (int j = 1; j < Ny - 1; ++j) {
            double phi_t = (curr[i][j] - old[i][j]) / dt;
            double grad_x = (curr[i+1][j] - curr[i-1][j]) / (2.0 * dx);
            double grad_y = (curr[i][j+1] - curr[i][j-1]) / (2.0 * dy);
            
            energia += 0.5 * (phi_t * phi_t + grad_x * grad_x + grad_y * grad_y) + (1.0 - cos(curr[i][j]));
        }
    }
    return energia * dx * dy;
}

//Función para calcular la carga topológica

double calcular_carga(const vector<vector<double>>& curr) {
    double carga = 0.0;
    // Para un Kink que varía en X, integramos d_phi/dx a lo largo de una línea media en Y
    int j_mid = Ny / 2;
    for (int i = 1; i < Nx - 1; ++i) {
        carga += (curr[i+1][j_mid] - curr[i-1][j_mid]) / 2.0;
    }
    return carga / (2.0 * M_PI); // M_PI requiere #include <cmath>
}

//void guardar_csv(const vector<vector<double>>&phi, int t){
//    string nombre_archivo = "datos_" + to_string(t) + ".csv";
//    ofstream archivo(nombre_archivo);

 //   for(int i = 0; i < Nx; ++i){
   //     for (int j = 0; j < Ny ; ++j){
     //       archivo << phi[i][j];
       //     if (j < Ny - 1) archivo << "," ;
        //}
        //archivo << "\n"; 
    //}
    //archivo.close();git
//}
int main() { 
    //Se reserva memoria para los tres pasos de tiempo
    vector<vector<double>> phi_old(Nx,vector<double>(Ny));
    vector<vector<double>> phi_curr(Nx, vector<double>(Ny));
    vector<vector<double>> phi_next(Nx, vector<double>(Ny));
    vector<vector<double>> phi_t(Nx, vector<double>(Ny));

    //inicializar
    inicializar_phi(phi_curr);
    inicializar_phi_t(phi_t);

    //Primer paso de tiempo 

    for (int i = 1; i < Nx - 1; ++i) {
        for (int j = 1; j < Ny - 1; ++j) {
            double lap = (phi_curr[i+1][j] - 2*phi_curr[i][j] + phi_curr[i-1][j])/(dx*dx) +
                         (phi_curr[i][j+1] - 2*phi_curr[i][j] + phi_curr[i][j-1])/(dy*dy);
            phi_old[i][j] = phi_curr[i][j] - dt * phi_t[i][j] + 0.5 * dt * dt * (lap - sin(phi_curr[i][j]));
        }
    }

    //Bucle principal de tiempo 

    for (int t=0; t<Nt ; ++t){
        for (int i = 1; i < Nx - 1; ++i) {
            for (int j = 1; j < Ny - 1; ++j) {
                double lap = (phi_curr[i+1][j] - 2*phi_curr[i][j] + phi_curr[i-1][j])/(dx*dx) +
                             (phi_curr[i][j+1] - 2*phi_curr[i][j] + phi_curr[i][j-1])/(dy*dy);
                
                // Ecuación de evolución
                phi_next[i][j] = 2.0 * phi_curr[i][j] - phi_old[i][j] + 
                                 (dt * dt) * (lap - sin(phi_curr[i][j]));
            }
        }

        //condiciones de frontera: Se mantienen los bordes fijos

        for (int j = 0; j < Ny; ++j){
            phi_next[0][j] = phi_curr[0][j]; //Borde izquierdo 
            phi_next[Nx-1][j] = phi_curr[Nx-1][j]; //Borde derecho
        }

        for (int i = 0; i < Nx; i++){
            phi_next[i][0] = phi_curr[i][0]; //Borde inferior
            phi_next[i][Ny-1] = phi_curr[i][Ny-1]; //Borde superior
        }
        if (t%50 == 0){
            double E = calcular_energia(phi_curr,phi_old);
            double Q = calcular_carga(phi_curr);
            cout << "Paso : " << t << "\t| Energía : " << E << "\t| Carga topológica: " << Q << endl;
        }
        //Actualización de punteros
        phi_old = phi_curr;
        phi_curr = phi_next;
    }

    cout << "Simulación completa" << endl;
    return 0;
}  