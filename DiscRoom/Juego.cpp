#include "Juego.h"



Juego::Juego()
{
	estado = 0;
	Nivel1 = new Nivel(1, 7);
	Nivel2 = new Nivel(2, 7);
	Nivel3 = new Nivel(3, 7);
	Nivel4 = new Nivel(4, 7);
	Nivel5 = new Nivel(5, 7);
	menu = new MenuPrincipal();
	nivelActivo = 0;
}
Nivel* Juego::GetNivelActual() {
	switch (nivelActivo)
	{
	case 1: return Nivel1;
	case 2: return Nivel2;
	case 3: return Nivel3;
	case 4: return Nivel4;
	case 5: return Nivel5;
	default:
		break;
	}
}

void Juego::ProcesarTick(System::Drawing::Graphics ^gr, System::Windows::Forms::Timer^  timer1) {
	switch (estado)
	{
	case 0: menu->ProcesarTick(gr); if (menu->getIniciarNivel()!=0) {
		estado = 1; 
		nivelActivo = menu->getIniciarNivel();
		menu->setIniciarNivel(0);
		timer1->Interval = 10;
	} break;
	case 1: GetNivelActual()->ProcesarTick(gr); if (GetNivelActual()->getIniciarMenu()) {
		estado = 0;
		GetNivelActual()->ReiniciarNivel();
		nivelActivo = 0;
		timer1->Interval = 5;
	} break;
	default:
		break;
	}
	
}
void Juego::ProcesarKeyDown(System::Windows::Forms::Keys e) {
	switch (estado)
	{
	case 0: menu->ProcesarKeyDown(e); break;
	case 1:  GetNivelActual()->ProcesarKeyDown(e); break;
	default:
		break;
	}
}
void Juego::ProcesarKeyUp(System::Windows::Forms::Keys e) {
	switch (estado)
	{
	case 0: menu->ProcesarKeyUp(e); break;
	case 1:  GetNivelActual()->ProcesarKeyUp(e); break;
	default:
		break;
	}
}

Juego::~Juego()
{
}
