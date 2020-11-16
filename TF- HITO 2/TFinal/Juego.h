#pragma once
#include "Imagen.h"
#include "Laberinto.h"
ref class Juego {
	Bitmap^ pared;

	Imagen^ escenario;
	Laberinto* laberinto;
	Principal^ jugador;
	Corrupt^ corrupto;
	Aliado^ aliado;
	Asesino^ asesino;

public:
	Juego(System::Drawing::Rectangle area, Graphics^g) {
		pared = gcnew Bitmap("Recursos\\pared.png");

		this->escenario = gcnew Imagen("Recursos\\Imagenes\\escenario.png", area);
		this->laberinto = new Laberinto(17,35);
		jugador = gcnew Principal();
		corrupto = gcnew Corrupt(laberinto);
		aliado = gcnew Aliado(laberinto);
		asesino = gcnew Asesino(laberinto);

		Renderizar(g);
	}
	~Juego() {
		delete this->escenario;
		delete this->laberinto;
		delete this->pared;
		delete this->jugador;
		delete this->corrupto;
		delete this->aliado;
		delete this->asesino;
	}
	bool Jugar(Graphics^ g) {
		this->Renderizar(g);
		this->Mover();
		return true;
	}
	void MoverJugador(bool accion, Keys key)
	{
		if (accion == true)
		{
			if (key == Keys::Up)
			{
				jugador->SetDY(-10);
				jugador->SetAccion(Arriba);
				jugador->SetUltima(Arriba);
			}
			else if (key == Keys::Down)
			{
				jugador->SetDY(10);
				jugador->SetAccion(Abajo);
				jugador->SetUltima(Abajo);
			}
			else if (key == Keys::Left)
			{
				jugador->SetDX(-10);
				jugador->SetAccion(Izquierda);
				jugador->SetUltima(Izquierda);
			}
			else if (key == Keys::Right)
			{
				jugador->SetDX(10);
				jugador->SetAccion(Derecha);
				jugador->SetUltima(Derecha);
			}
		}
		else
		{
			jugador->SetUltima(Ninguna);
			if (key == Keys::Up)
				jugador->SetDY(0);
			else if (key == Keys::Down)
				jugador->SetDY(0);
			else if (key == Keys::Left)
				jugador->SetDX(0);
			else if (key == Keys::Right)
				jugador->SetDX(0);

		}
	}
private:
	void Renderizar(Graphics^ g) {
		this->escenario->Dibujar(g);
		this->laberinto->Mostrar(g, pared);
		this->jugador->Dibujar(g);
		this->corrupto->Dibujar(g);
		this->aliado->Dibujar(g);
		this->asesino->Dibujar(g);
	}
	void Mover() {
		if (!(laberinto->Colision(jugador->NextArea())))
		{
			jugador->Mover();
		}
		if (!(laberinto->Colision(corrupto->NextArea())))
		{
			corrupto->Mover();
		}
		if (!(laberinto->Colision(asesino->NextArea())))
		{
			asesino->Mover();
		}
		if (!(laberinto->Colision(aliado->NextArea())))
		{
			aliado->Mover();
		}
		corrupto->MoverSiguiendo(jugador->GetX(), jugador->GetY());
		asesino->MoverAleatorio();
		aliado->MoverAleatorio();
	}

	
};