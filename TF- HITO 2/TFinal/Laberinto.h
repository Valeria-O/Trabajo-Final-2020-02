#pragma once
#include "Biblioteca.h"
enum Direction { norte, sur, este, oeste, cerrado };

 class Celda 
{
private:
    bool visitado;
    bool pared;
public:
    Celda(bool pared, bool visitado)
    {
        this->visitado = visitado;
        this->pared = pared;
    }
    ~Celda() {}
    void Cavar()
    {
        visitado = true;
        pared = false;
    }
    bool GetPared()
    {
        return pared;
    }
    bool GetVisitado()
    {
        return visitado;
    }
};

class Laberinto
{
    vector<vector <Celda> > celdas;
    const short lado = 35;
public:
    Laberinto(int alto, int ancho)
    {
        srand(time(NULL));
        for (int i = 0; i < ancho; i++)
        {
            vector<Celda> colum;
            for (int j = 0; j < alto; j++)
            {
                colum.push_back(DeterminaTipoNodo(i, j, ancho, alto));
            }
            celdas.push_back(colum);
        }
        CavarParedes(5, 5);
    }
    ~Laberinto() {}
    void Mostrar(Graphics^ g, Bitmap^ img)
    {
        for (short i = 0; i < celdas.size(); i++)
        {
            for (short j = 0; j < celdas[i].size(); j++)
            {
                if (celdas[i][j].GetPared()) {
                    g->DrawRectangle(Pens::Black,Rectangle(25 + (i * lado), 70 + (j * lado), lado, lado));
                    g->DrawImage(img, Rectangle(25 + (i * lado), 70 + (j * lado), lado, lado));
                }
            }
        }
    }
    bool Colision(Rectangle area)
    {
        Rectangle rec;
        for (short i = 0; i < celdas.size(); i++)
        {
            for (short j = 0; j < celdas[i].size(); j++)
            {
                if (celdas[i][j].GetPared()) {
                    rec = Rectangle(25 + (i * lado), 70 + (j * lado), lado, lado);
                    if (rec.IntersectsWith(area))
                        return true;
                }
            }
        }

        return false;
    }
    Rectangle PosicionVacia() {
        int i, j;
        do {
            i = rand() % 34 + 1;
            j = rand() % 16 + 1;
        } while (GetEsPared(i, j));
        return Rectangle(25 + (i* lado), 70 + (j * lado), lado, lado);
    }
    void CavarParedes(int x, int y) //accepts only inputs with at least one even number
    {
        celdas[x][y].Cavar();
        Direction direction = Direccion_a_moverse(x, y); //obtiene una dirección válida para ir a la siguiente
        if (direction == cerrado) //si no se encontró ninguna dirección, retrocedemos un paso en la recursividad
        {
            return;
        }
        else if (direction == este)
        {
            celdas[x + 1][y].Cavar();
            CavarParedes(x + 2, y);
        }
        else if (direction == oeste)
        {
            celdas[x - 1][y].Cavar();
            CavarParedes(x - 2, y);
        }
        else if (direction == norte)
        {
            celdas[x][y - 1].Cavar();
            CavarParedes(x, y - 2);
        }
        else if (direction == sur)
        {
            celdas[x][y + 1].Cavar();
            CavarParedes(x, y + 2);
        }
        CavarParedes(x, y); //Esto es necesario al retroceder para comenzar a tallar nuevamente después de quedar atrapado en un callejón sin salida.
    }
    bool GetEsPared(int i, int j) {
        return celdas[i][j].GetPared();
    }

private:
    Celda DeterminaTipoNodo(int i, int j, int alto, int ancho)
    {
        if (i == 0 || j == 0)
        {
            return Celda(true, true); // es borde del laberinto
        }
        if (i == alto - 1 || j == ancho - 1)
        {
            return Celda(true, true); // es borde del laberinto
        }
        if (i % 2 == 0 || j % 2 == 0)
        {
            return Celda(true, false); //es una pared que puede removerse
        }
        else
        {
            return Celda(false, false); //es el camino
        }
    }
    Direction Direccion_a_moverse(int x, int y)
    {
        vector<Direction> temp; //direcciones elegibles en un vector

        if (!celdas[x + 1][y].GetVisitado() && !celdas[x + 2][y].GetVisitado())
            temp.push_back(este);
        if (!celdas[x - 1][y].GetVisitado() && !celdas[x - 2][y].GetVisitado())
            temp.push_back(oeste);
        if (!celdas[x][y + 1].GetVisitado() && !celdas[x][y + 2].GetVisitado())
            temp.push_back(sur);
        if (!celdas[x][y - 1].GetVisitado() && !celdas[x][y - 2].GetVisitado())
            temp.push_back(norte);

        if (temp.size() != 0) { // direccion aleatorio del vector
            return temp[rand() % temp.size()];
        }

        else //Si no tiene direccion a la que moverse esta cerrado
            return cerrado;
    }
};