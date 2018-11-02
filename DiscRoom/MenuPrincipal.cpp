#include "MenuPrincipal.h"



MenuPrincipal::MenuPrincipal()
{
	selectMenu1 = 1;
	selectMenu2 = 1;
	estado = 0;
	IniciarNivel = 0;
}
void MenuPrincipal::Mostrar(System::Drawing::Graphics ^gr){
	gr->FillRectangle(System::Drawing::Brushes::Black, 0, 0, 640, 640);
	System::Drawing::Font ^f = gcnew System::Drawing::Font("Agency FB", 20);
	System::Drawing::Font ^f2 = gcnew System::Drawing::Font("Agency FB", 26,System::Drawing::FontStyle::Bold);
	System::Drawing::Font ^f3 = gcnew System::Drawing::Font("Agency FB", 15, System::Drawing::FontStyle::Bold);


	/*BRUSH ROSADO*/ System::Drawing::Brush ^b = gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(243, 65, 118));
	
	if (estado == 0) {
		//MENU INICIAL
		gr->FillRectangle(System::Drawing::Brushes::White, 60, 320, 170, 30);
		gr->FillRectangle(System::Drawing::Brushes::White, 235, 320, 170, 30);
		gr->FillRectangle(System::Drawing::Brushes::White, 410, 320, 170, 30);
		/*Animacion de seleccion*/int mar1 = 0, mar2 = 0, mar3 = 0;
		if (selectMenu1 != 1) {
			gr->FillRectangle(b, 57, 317, 170, 30);
			mar1 = 3;
		}
		if (selectMenu1 != 2) {
			gr->FillRectangle(b, 232, 317, 170, 30);
			mar2 = 3;
		}
		if (selectMenu1 != 3) {
			gr->FillRectangle(b, 407, 317, 170, 30);
			mar3 = 3;
		}
		gr->DrawString("PLAY", f, System::Drawing::Brushes::Black, 60 - mar1, 320 - mar1);
		gr->DrawString("HELP", f, System::Drawing::Brushes::Black, 235 - mar2, 320 - mar2);
		gr->DrawString("EXIT", f, System::Drawing::Brushes::Black, 410 - mar3, 320 - mar3);
		gr->DrawString("DISC ROOM", f2, System::Drawing::Brushes::White, 50, 380);
		gr->DrawString("GAME BY VALERIA COLLAZOS ", f3, System::Drawing::Brushes::White, 53, 420);
		gr->DrawString("& JESARELA HIJAR ", f3, System::Drawing::Brushes::White, 53, 440);
	}
	else if (estado == 1) {
		//NIVELES
		gr->DrawString("BASICS", f, System::Drawing::Brushes::White, 285, 40);
		for (int i = 0; i < 5; i++)
		{
			DibujarOpcionNivel(gr, i); // DIBUJAR NIVELES PARA SELECCIONAR
		}
	}
	else if (estado == 2) {
		//INSTRUCCIONES
		gr->DrawString("ARROW KEYS", f, b, 198, 180);
		gr->DrawString("MOVE", f,System::Drawing::Brushes::White, 330, 180);

		gr->DrawString("X", f, b, 290, 220);
		gr->DrawString("SLOW TIME", f, System::Drawing::Brushes::White, 330, 220);

		gr->DrawString("ESC", f, b, 270, 300);
		gr->DrawString("BACK", f, System::Drawing::Brushes::White, 330, 300);

		gr->DrawString("A", f, b, 290, 340);
		gr->DrawString("RETRY", f, System::Drawing::Brushes::White, 330, 340);

		gr->DrawString("YOU DON'T HAVE TO DIE! YOU CAN LIVE!", f, System::Drawing::Brushes::White, 160, 420);

	}
}
void MenuPrincipal::setIniciarNivel(int value) {
	IniciarNivel = value;
}
void MenuPrincipal::DibujarOpcionNivel(System::Drawing::Graphics ^gr, int nive) {
	// DIBUJAR OPCION DE NIVEL EN EL MENU DE NIVELES
	System::Drawing::Brush ^b = gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(243, 65, 118));

	array<System::Drawing::Point> ^points1 = gcnew array<System::Drawing::Point>(selectMenu2 != nive + 1?4:3);

	{
		System::Drawing::Point point1 = System::Drawing::Point(((selectMenu2 != nive + 1)?197:194) + (nive*(70)), 97);
		System::Drawing::Point point2 = System::Drawing::Point(210 + (nive*(70)), 97);
		System::Drawing::Point point3 = System::Drawing::Point(210 + (nive*(70)), 110);
		System::Drawing::Point point4;
		if (selectMenu2 != nive + 1) point4 = System::Drawing::Point(207 + (nive*(70)), 107);
		
		points1[0] = point1; points1[1] = point2; points1[2] = point3;  
		if (selectMenu2 != nive + 1) points1[3] = point4;
		
	}
	gr->FillRectangle(System::Drawing::Brushes::White, 150+(nive*(70)), 100, 60, 60);
	int mar1 = 0;
	if (selectMenu2 != nive+1) {
		gr->FillRectangle(b, 147 + (nive*(70)), 97, 60, 60);
		gr->FillPolygon(System::Drawing::Brushes::Black, points1);
		mar1 = 5;
	}else{
		gr->FillPolygon(System::Drawing::Brushes::Black, points1);
	}
	
	System::Drawing::Font ^f = gcnew System::Drawing::Font("Agency FB", 23);

	gr->DrawString((nive+1)+"", f, System::Drawing::Brushes::Black, 170 + (nive*(70))-mar1, 110-mar1);
}
int MenuPrincipal::getIniciarNivel() {
	return IniciarNivel;
}
void MenuPrincipal::ProcesarTick(System::Drawing::Graphics ^gr) {
	Mostrar(gr);
}
void MenuPrincipal::ProcesarKeyDown(System::Windows::Forms::Keys e) {
}
void MenuPrincipal::ProcesarKeyUp(System::Windows::Forms::Keys e) {
	if (estado == 0) {
		//PLAY - HELP - EXIT
		switch (e) {
		case System::Windows::Forms::Keys::Left:
			selectMenu1 = selectMenu1 == 1 ? 3 : selectMenu1 - 1;
			break;
		case System::Windows::Forms::Keys::Right:
			selectMenu1 = selectMenu1 == 3 ? 1 : selectMenu1 + 1;
			break;
		case System::Windows::Forms::Keys::Enter:
			selectMenu1 == 1 ? estado = 1 : selectMenu1 == 2 ? estado = 2:estado=3;
			break;
		default:
			break;
		}
	}
	else if (estado == 1) {
		//Nivel1 - Nivel2 - Nivel3 - Nivel4 - Nivel5
		switch (e) {
		case System::Windows::Forms::Keys::Left:
			selectMenu2 = selectMenu2 == 1 ? 5 : selectMenu2 - 1;
			break;
		case System::Windows::Forms::Keys::Right:
			selectMenu2 = selectMenu2 == 5 ? 1 : selectMenu2 + 1;
			break;
		case System::Windows::Forms::Keys::Enter:
			IniciarNivel = selectMenu2;
			break;
		case System::Windows::Forms::Keys::Escape:
			estado = 0;
			break;
		default:
			break;
		}
	}
	else if (estado ==2) {
		// INSTRUCCIONES
		switch (e) {
		case System::Windows::Forms::Keys::Escape:
			estado = 0;
			break;
		default:
			break;
		}
	}
}
MenuPrincipal::~MenuPrincipal()
{
}
