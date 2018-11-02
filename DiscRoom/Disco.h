#pragma once
#include "Sprite.h"
#include "Personaje.h"
#include <math.h>
#include <stdlib.h>
class Disco :
	public Sprite
{
private:
	int retrasoCambioSprite; // Demora para cambiar IndiceSprite
	int tipo; //1: Disco normal - 2 : Disco lateral - 3 : Disco persecutor
	bool estaCerca; //(Disco persecutor) true: Disco esta cerca del personaje, lo perseguira - false: No esta cerca al personaje, no lo perseguira
public:
	Disco();
	Disco(int pPosX, int pPosY, int pAncho, int pAlto, int pDeltaX, int pDeltaY, char* pNombreArchivo, int pIndiceSpriteX, int pIndiceSpriteY, int pDeltaSpriteX,int pTipo);
	void CambiarSprite();
	void DistanciaPerseguir(Personaje* temp);
	void Mostrar(System::Drawing::Graphics ^gr);
	void Mover();
	~Disco();
};

