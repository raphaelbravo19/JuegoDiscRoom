#pragma once
#include "Nivel.h"
#include "MenuPrincipal.h"
class Juego
{
private:
	Nivel * Nivel1;
	Nivel * Nivel2;
	Nivel * Nivel3;
	Nivel * Nivel4;
	Nivel * Nivel5;
	MenuPrincipal * menu;
	int estado; //1: MENU | 2: NIVEL
	int nivelActivo; // Nivel que se esta jugando
public:
	Juego();
	void ProcesarTick(System::Drawing::Graphics ^gr, System::Windows::Forms::Timer^  timer1);
	void ProcesarKeyDown(System::Windows::Forms::Keys e);
	void ProcesarKeyUp(System::Windows::Forms::Keys e);
	Nivel* GetNivelActual();
	~Juego();
};

