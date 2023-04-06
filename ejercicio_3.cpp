/*
 * File:	ejercicio3.cpp
 * Date:	april 2023
 * Comms:	Ejercicio 3 de la práctica 1 de la asignatura de Programación
 *		de Sistemas Concurrentes y Distribuidos
 *		Compilar mediante:
 * 			g++ ejercicio_3.cpp -o ejercicio3 -std=c++11 -pthread
 * 		Ejecutar mediante:
 * 			./ejercicio3
 */
#include <iostream>
#include <thread>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

//Definimos las variables globales
const int MAX_DATOS = 100;
const int NUM_PROCESOS = 3;

/*
 * Pre:  ---
 * Post: Calcula la media de los valores del vector v.
 */
void calculaMedia (double v[], double& media, bool& mediaDisponible){
    mediaDisponible = false;
    double suma = 0.0;

    for (int i = 0; i < MAX_DATOS; i++) {
        suma += v[i];
    }
    media = suma / MAX_DATOS;
    mediaDisponible = true;
}

/*
 * Pre:  ---
 * Post: Calcula los valores mínimo y máximo del vector v.
 */
void calculaMinMax (double v[], double& minimo, double& maximo){
    minimo = v[0];
    maximo = v[0];

    for(int i = 1; i < MAX_DATOS; i++){
        if (v[i] < minimo){
            minimo = v[i];
        }
        if (v[i] > maximo) {
            maximo = v[i];
        }
    }
}

/*
 * Pre:  ---
 * Post: Calcula la desviación típica de los elementos del vector v.
 */
void calculaDesviacion (double v[], double& sigma, bool& mediaDisponible){
    while(!mediaDisponible){}
    double media;
    double aux = 0.0;

    calculaMedia(v,media,mediaDisponible);

    for (int i = 0; i < MAX_DATOS; i++) {
        aux += pow(v[i] - media, 2);
    }
    aux = aux / MAX_DATOS;
    sigma = sqrt(aux);
}


int main (int argc, char* argv[]){
    srand(time(NULL));

    thread P[NUM_PROCESOS];
    double v[MAX_DATOS];

    //Muestro por pantalla los elementos del vector.
    cout << "Elementos del vector: " << endl;
    for(int i = 0; i < MAX_DATOS; i++) {
        //Inicializo el vector con números reales aleatorios.ç
        v[i] = ((double)rand()/RAND_MAX*10.0);
        cout << i+1 << ")  " << v[i] << endl;
    }

    double minimo, maximo, sigma, media;
    static bool mediaDisponible = false;

    //Lanzamos los 3 procesos
    P[0] = thread(&calculaMedia, v, ref(media));
    P[1] = thread(&calculaMinMax, v, ref(minimo),ref(maximo));
    P[2] = thread(&calculaDesviacion, v, ref(sigma),ref(mediaDisponible));

    for(int i = 0; i < NUM_PROCESOS; i++){
        P[i].join();
    }

    //Muestro los datos necesarios por pantalla.
    cout << "\n#datos: " << MAX_DATOS << endl;
    cout << "media: " << media << endl;
    cout << "minimo: " << minimo << endl;
    cout << "maximo: " << maximo << endl;
    cout << "sigma: " << sigma << endl;

    return 0;
}
