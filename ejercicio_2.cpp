/*
 * File:	ejercicio2.cpp
 * Date:	march 2023
 * Comms:	Ejercicio 2 de la práctica 1 de la asignatura de Programación
 * 		de Sistemas Concurrentes y Distribuidos
 *		Compilar mediante:
 * 			g++ ejercicio_2.cpp -o ejercicio2 -std=c++11 -pthread
 * 		Ejecutar mediante:
 * 			./ejercicio2
 */
#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <cstdlib>
using namespace std;

const int NUM_PROCESOS = 10;



void saludo(int id, int retardo, int veces){
	for (int j = 1; j <= veces; j++){
		cout << "Soy " + to_string(id) + "\n";
		this_thread::sleep_for(chrono::milliseconds(retardo));
	}
}


int main (int argc, char* argv[]){
	thread P[NUM_PROCESOS];
	int veces, retardo;

	for (int i = 1; i <= NUM_PROCESOS; i++){
		veces = 5 + rand()%10;		//valor aleatorio entre 5 y 15
		retardo = 100 + rand()%200; //valor aleatorio entre 100 y 300
		P[i-1] = thread(&saludo, i, retardo, veces);	//lanzamos los procesos
	}
	for (int i = 0; i< NUM_PROCESOS; i++){
		P[i].join();		//me bloqueo hasta que P[i] termine
	}
	cout << "Fin\n";
	return 0;
}
