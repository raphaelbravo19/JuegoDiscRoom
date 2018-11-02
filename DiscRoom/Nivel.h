#pragma once
#include "Personaje.h"
#include "Fondo.h"
#include "Disco.h"
#include "ArregloDisco.h"
#include <stdlib.h> 
#include <time.h>

class Nivel
{
private:
	Personaje * personaje; // Personaje
	Fondo * marco; // Marco
	Fondo * mapa; // Fondo
	ArregloDisco * arregloDiscos;
	int generarDisco; // Retraso para generar disco
	int nivel; // Nivel Actual
	int maxDiscos; // Maximo de discos que se generaran
	bool choque; // Un disco choco con el personaje
	bool IniciarMenu; // Se inicia el menu de niveles
public:
	Nivel(int pnivel, int pmax);
	~Nivel();
	bool getIniciarMenu(); 
	void ReiniciarNivel(); // Reinicia nivel
	Disco* GenerarDisco(); // Genera un disco 
	bool SeChocaron(Disco* temp); // Choco disco con personaje
	void ProcesarTick(System::Drawing::Graphics ^gr);
	void ProcesarKeyDown(System::Windows::Forms::Keys e);
	void ProcesarKeyUp(System::Windows::Forms::Keys e);
};

