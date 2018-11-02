#include "Disco.h"

Disco::Disco(){
}

Disco::Disco(int pPosX, int pPosY, int pAncho, int pAlto, int pDeltaX, int pDeltaY, char* pNombreArchivo, int pIndiceSpriteX, int pIndiceSpriteY, int pDeltaSpriteX, int pTipo) {
	PosX = pPosX;
	PosY = pPosY;
	Ancho = pAncho;
	Alto = pAlto;
	DeltaX = pDeltaX;
	DeltaY = pDeltaY;
	NombreArchivo = new char[100];
	strcpy(NombreArchivo, pNombreArchivo);
	IndiceSpriteX = pIndiceSpriteX;
	IndiceSpriteY = pIndiceSpriteY;
	DeltaSpriteX = pDeltaSpriteX;
	tipo = pTipo; 
	retrasoCambioSprite = 0;
	estaCerca = false;
}
void Disco::CambiarSprite() {
	DeltaSpriteX = 1;
	IndiceSpriteX = IndiceSpriteX <= 1 ? IndiceSpriteX + DeltaSpriteX : 0;
}
void Disco::Mostrar(System::Drawing::Graphics ^gr) {
	System::Drawing::Bitmap ^bmp = gcnew System::Drawing::Bitmap(gcnew System::String(NombreArchivo));
	System::Drawing::Rectangle porcion = System::Drawing::Rectangle(Ancho*IndiceSpriteX, Alto*IndiceSpriteY, Ancho, Alto);
	System::Drawing::Rectangle destino = System::Drawing::Rectangle(PosX, PosY, Ancho * 2, Alto * 2);
	bmp->MakeTransparent(bmp->GetPixel(1, 1));
	gr->DrawImage(bmp, destino, porcion, System::Drawing::GraphicsUnit::Pixel);
	delete bmp;
}
void Disco::Mover() {
	int PosX2;
	int PosY2; 
	if(tipo==1 || tipo==3){
		PosX2 = PosX + DeltaX * 2;
		PosY2 = PosY + DeltaY * 2;
		if (PosX2 < 64 || PosX2 +(Ancho*2)>576) {
			DeltaX *= -1;
			PosX2 = PosX + DeltaX * 2;
		}
		if (PosY2 < 64 || PosY2 +(Alto*2)>576) {
			DeltaY *= -1;
			PosY2 = PosY + DeltaY * 2;
		}
	}
	else if (tipo == 2) {
		PosX2 = PosX + DeltaX * 8;
		PosY2 = PosY + DeltaY * 8;
		if (PosX2 == 64 - Ancho && PosY2 == 64 - Alto) { DeltaX = 1; DeltaY = 0;}
		if (PosX2 == 64 - Ancho && PosY2 == 576 - Alto) { DeltaX = 0; DeltaY = -1; }
		if (PosX2 == 576 - Ancho && PosY2 == 64 - Alto) { DeltaX = 0; DeltaY = 1; }
		if (PosX2 == 576 - Ancho && PosY2 == 576 - Alto) { DeltaX = -1; DeltaY = 0; }
	}
	PosX = PosX2;
	PosY = PosY2;
	if (retrasoCambioSprite == 2) {
		CambiarSprite();
		retrasoCambioSprite = 0;
	}
	retrasoCambioSprite++;
}
void Disco::DistanciaPerseguir(Personaje* temp) {
	
	if (tipo == 3) {
		int tposx = PosX + Ancho;
		int tposy = PosY + Alto;

		int pposx = temp->GetPosX() + temp->GetAncho();
		int pposy = temp->GetPosY() + temp->GetAlto();

		double distance = sqrt(pow(tposx - pposx, 2) + pow(tposy - pposy, 2));
		
		if (distance < 150) {
			if (tposx > pposx) DeltaX = -1;
			if (tposx < pposx) DeltaX = 1;
			if (tposy > pposy) DeltaY = -1;
			if (tposy < pposy) DeltaY = 1;
			estaCerca = true;
		}
		else if (estaCerca) {
			do { DeltaX = rand() % 7 - 3; } while (DeltaX == 0);
			do { DeltaY = rand() % 7 - 3; } while (DeltaY == 0);

			estaCerca = false;
		}
	}
}
Disco::~Disco()
{
}
