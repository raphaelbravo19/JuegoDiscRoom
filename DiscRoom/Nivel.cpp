#include "Nivel.h"
#include <math.h>
#include <iostream>
Nivel::Nivel(int pnivel,int pmaxDiscos)
{
	nivel = pnivel;
	maxDiscos = pmaxDiscos;
	personaje = new Personaje(315,314,10,12,0,0,"Sprite1.png",0,0,0);
	System::String^ s = "marco" + nivel + ".png";
	char cnivel[1];
	sprintf(cnivel, "%d", nivel);
	char nmarco [10]= "marco";
	char nfondo [10]= "fondo";
	strcat(nmarco, cnivel); strcat(nfondo, cnivel);
	strcat(nmarco, ".png"); strcat(nfondo, ".png");
	marco = new Fondo(0, 0, 320, 320, 0, 0, nmarco, 0, 0, 0,true);
	mapa = new Fondo(64, 64, 256, 256, 0, 0, nfondo, 0, 0, 0,false);
	arregloDiscos = new ArregloDisco();
	generarDisco = 0;
	choque = false;
	IniciarMenu = false;
}

Disco* Nivel::GenerarDisco() {
	srand(time(NULL));
	int tempDeltaX, tempDeltaY;
	//MOVIMIENTO ALEATORIO
	do { tempDeltaX = rand() % 7 - 3; } while (tempDeltaX == 0);
	do { tempDeltaY = rand() % 7 - 3; } while (tempDeltaY == 0);
	Disco* temp;
	int sec;
	if (nivel == 1) {
		//NIVEL 1 solo discos pequeños
		temp = new Disco(294, 294, 26, 26, tempDeltaX, tempDeltaY, "SmallDisc.png", 0, 0, 1, 1);
	}
	if (nivel == 2) {
		//NIVEL 2 solo discos pequeños
		temp = new Disco(294, 294, 26, 26, tempDeltaX, tempDeltaY, "SmallDisc.png", 0, 0, 1, 1);
	}
	if (nivel == 3) {
		//NIVEL 3 discos pequeños y grandes
		sec = rand() % 2 + 1;
		if(sec==1)temp = new Disco(294, 294, 26, 26, tempDeltaX, tempDeltaY, "SmallDisc.png", 0, 0, 1, 1);
		if (sec == 2)temp = new Disco(268, 268, 52, 52, tempDeltaX, tempDeltaY, "BigDisc.png", 0, 0, 1, 1);
	}
	if (nivel == 4) {
		//NIVEL 4 solo discos grandes
		temp = new Disco(268, 268, 52, 52, tempDeltaX, tempDeltaY, "BigDisc.png", 0, 0, 1, 1);
	}
	if (nivel == 5) {
		//NIVEL 5 discos pequeños y persecutores
		sec = rand() % 3 + 1;
		if (sec == 1)temp = new Disco(294, 294, 26, 26, tempDeltaX, tempDeltaY, "SmallDisc.png", 0, 0, 1, 1);
		if (sec == 2 || sec == 3)temp = new Disco(294, 294, 26, 26, tempDeltaX, tempDeltaY, "FollowDisc.png", 0, 0, 1, 3);
	}

	return temp;
	
}
void Nivel::ProcesarTick(System::Drawing::Graphics ^gr) {

	generarDisco++; // Contador para generar disco
	mapa->Mostrar(gr);
	personaje->Mostrar(gr);
	arregloDiscos->MostrarTodos(gr);
	arregloDiscos->MoverTodos();
	personaje->Mover();
	if (arregloDiscos->GetCantidad() < maxDiscos) {
		if (generarDisco == 60) { //60 ticks para poder generar un Disco 
			Disco* Disco = GenerarDisco();
			arregloDiscos->AgregaDisco(Disco);
			generarDisco = 0; 
		}
	}
	for (int i = 0; i < arregloDiscos->GetCantidad(); i++){
		arregloDiscos->DameDisco(i)->DistanciaPerseguir(personaje); //Discos persecutores perseguiran si estan cerca
		if (SeChocaron(arregloDiscos->DameDisco(i))) { 
			choque = true; // Personaje se choco con Disco
		}
	}
	marco->Mostrar(gr);
}

bool Nivel::SeChocaron(Disco* temp) {
	int tposx = temp->GetPosX() + temp->GetAncho();
	int tposy = temp->GetPosY() + temp->GetAlto();

	int pposx =	personaje->GetPosX() + personaje->GetAncho();
	int pposy = personaje->GetPosY() + personaje->GetAlto();

	double distance = sqrt(pow(tposx - pposx, 2) + pow(tposy - pposy, 2));

	double comp = temp->GetAncho() + personaje->GetAncho()-5;

	if (distance < comp) return true;
	else return false;
	
}
void Nivel::ProcesarKeyDown(System::Windows::Forms::Keys e) {
	// MOVIMIENTO PERSONAJE
	switch (e) {
	case System::Windows::Forms::Keys::Left:
		personaje->SetDeltaX(-1);
		break;
	case System::Windows::Forms::Keys::Up:
		personaje->SetDeltaY(-1);
		break;
	case System::Windows::Forms::Keys::Right:
		personaje->SetDeltaX(1);
		break;
	case System::Windows::Forms::Keys::Down:
		personaje->SetDeltaY(1);
		break;
	default:
		break;
	}
}
void Nivel::ProcesarKeyUp(System::Windows::Forms::Keys e) {
	// DETENER MOVIMIENTO
	switch (e) {
	case System::Windows::Forms::Keys::Left:
		personaje->SetDeltaX(0);
		break;
	case System::Windows::Forms::Keys::Up:
		personaje->SetDeltaY(0);
		break;
	case System::Windows::Forms::Keys::Right:
		personaje->SetDeltaX(0);
		break;
	case System::Windows::Forms::Keys::Down:
		personaje->SetDeltaY(0);
		break;
	case System::Windows::Forms::Keys::Escape: //INICIAR MENU
		IniciarMenu = true;
		break;
	default:
		break;
	}
}
void Nivel::ReiniciarNivel() {
	personaje = new Personaje(315, 314, 10, 12, 0, 0, "Sprite1.png", 0, 0, 0);
	arregloDiscos = new ArregloDisco();
	generarDisco = 0;
	choque = false;
	IniciarMenu = false;
}
bool Nivel::getIniciarMenu() {
	return IniciarMenu;
}
Nivel::~Nivel()
{
	delete personaje;
	delete marco;
	delete mapa;
	delete arregloDiscos;
}
