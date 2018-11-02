#pragma once
class MenuPrincipal
{
private:
	int selectMenu1; // MENU INICIAL -> 1: PLAY | 2: HELP | 3: EXIT 
	int selectMenu2; // NIVELES -> 1: Nivel 1 | 2: Nivel 2 | 3: Nivel 3 | 4: Nivel 4 | 5: Nivel 5 
	int estado; // ESTADOS -> 1: Menu inicial | 2: Niveles | 3: Instrucciones
	int IniciarNivel; // Iniciar nivel seleccionado
public:
	MenuPrincipal();
	void setIniciarNivel(int value);
	int getIniciarNivel();
	void DibujarOpcionNivel(System::Drawing::Graphics ^gr, int nive);
	void Mostrar(System::Drawing::Graphics ^gr);
	void ProcesarTick(System::Drawing::Graphics ^gr);
	void ProcesarKeyDown(System::Windows::Forms::Keys e);
	void ProcesarKeyUp(System::Windows::Forms::Keys e);
	~MenuPrincipal();
};

