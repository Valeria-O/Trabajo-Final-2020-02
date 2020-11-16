#pragma once
#include "Laberinto.h"

ref class Imagen  {
protected:
	Rectangle area;
	Bitmap^ imagen;
	bool img_propia;
public:
	Imagen(String^ ruta, Rectangle area) {
		this->area = area;
		img_propia = true;
		this->imagen = gcnew Bitmap(ruta);
	}
	Imagen(Bitmap^ img, Rectangle area) {
		this->area = area;
		img_propia = false;
		this->imagen = img;
	}
	~Imagen() {
		if (img_propia)
			delete this->imagen;
	}
	virtual void Dibujar(Graphics^ graficador) {
		graficador->DrawImage(this->imagen, this->area);
	}
	Rectangle GetArea() {
		return this->area;
	}
};
enum Direccion { Abajo, Arriba, Derecha, Izquierda, Ninguna};

ref class Sprite : public Imagen {
private:
	Rectangle recorte;
	short ancho, alto;
	short filas, columnas;
	short IDx;
	Direccion accion;
	Direccion ultima;
protected:
	short dx, dy;
public:
	Sprite(String^ruta,Rectangle area, short c, short f)
		: Imagen(ruta, area), columnas(c), filas(f), accion(Ninguna),IDx(0) {
		this->ultima = Ninguna;
		this->ancho = this->imagen->Width / this->columnas;
		this->alto = this->imagen->Height / this->filas;
		this->dx = 0;
		this->dy = 0;
	}
	void Dibujar(Graphics^ g) override {
		if (ultima == Ninguna)
		{
			accion = Derecha;
			IDx = 0;
		}
		else
			IDx = (IDx + 1) % columnas;
		
		recorte = Rectangle(IDx * ancho, accion * alto, this->ancho, this->alto);
		g->DrawImage(imagen, this->area, this->recorte, GraphicsUnit::Pixel);
		g->DrawRectangle(Pens::Blue, NextArea());
		g->DrawRectangle(Pens::Red, GetArea());
		
	}
	Rectangle NextArea() {
		return Rectangle(area.X + dx, area.Y + dy, 35, 35);
	}
	void SetAccion(Direccion a) {
		accion = a;
    }
	Direccion GetAccion() {
		return accion;
	}

	void SetUltima(Direccion a) {
		ultima = a;
	}
	
	virtual void Mover() {
		this->area.X += dx;
		this->area.Y += dy;
	}
	short GetX() { return area.X; }
	short GetY() { return area.Y; }
	short GetDX() { return dx; }
	short GetDY() { return dy; }
	void SetDX(int n) { dx = n; }
	void SetDY(int n) { dy = n; }
};

ref class Principal : public Sprite {

public:
	Principal(): Sprite("Recursos\\Sprites\\king.png",Rectangle(60,105, 35, 35),4,4)
	{
	}	
};

ref class Corrupt : public Sprite {
	short x, y;
public:
	Corrupt(Laberinto*l): Sprite("Recursos\\Sprites\\pig.png", l->PosicionVacia(),4, 4) {
		srand(time(NULL));
	}
	void MoverSiguiendo(int x, int y) {
	
		if (x < area.X) {

			this->dx = -10;

			if (y < area.Y) {
				this->dy = -10;
			}
			else if (y > area.Y) {
				this->dy = 10;
			}
		}
		else if (x > area.X) {
			this->dy = 10;

			if (y < area.Y) {
				this->dy = -10;
			}
			else if (y > area.Y) {
				this->dy = 10;
			}
		}			
	}
};

ref class Aliado :public Sprite {
public:
	Aliado(Laberinto* l) : Sprite("Recursos\\Sprites\\goat_aliado.png", l->PosicionVacia(), 4, 4) {
		srand(time(NULL));
	}
	void MoverAleatorio() {
		if (rand() % 2) {
			dy = -10;
		}
		else dy = 10;
	}

};
ref class Asesino :public Sprite {
public:
	Asesino(Laberinto* l) : Sprite("Recursos\\Sprites\\bunny_aliado.png", l->PosicionVacia(), 4, 4) {
		srand(time(NULL));
	}
	void MoverAleatorio() {
		if (rand() % 2) {
			dx = -10;
		}
		else dx = 10;
	}
};