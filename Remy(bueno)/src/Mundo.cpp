#include"Mundo.h"
#include "ETSIDI.h"
#include <math.h>
#include <conio.h>
#include <string.h>




void Mundo::RotarOjo()
{
	float dist=sqrtf(x_ojo*x_ojo+z_ojo*z_ojo);
	float ang=atan2(z_ojo,x_ojo);
	ang+=0.05f;
	x_ojo=dist*cos(ang);
	z_ojo=dist*sin(ang);
}

bool Mundo::CargarNivel()
{
	nivel++;
	remy.SetPosicion(-10, 50);
	remy.SetVelocidad(0, 0);
	gatitos.destruirContenido();
	escenario.bombas.destruirContenido();
	escenario.plataformas.destruirContenido();
	escenario.quesos.destruirContenido();
	escenario.vidas.destruirContenido();
	remy.SetQuesos(5);
	remy.SetVida(3);

	if (nivel == 1)
	{
		Gatitos* auxg = new Gatitos(20, 0);
		gatitos.agregar(auxg);
		escenario.SetLvl1();
	}
	if (nivel == 2)
	{
		escenario.SetLvl2();
	}
	if (nivel == 3)
	{
		escenario.SetLvl3();
	}
	if (nivel == 4)
	{
		escenario.SetLvl4();
	}
	if (nivel <= 4)
	{
		return true;
	}
	return false;
}

void Mundo::Dibuja()
{
	x_ojo = remy.GetXPosicion();

	gluLookAt(x_ojo, y_ojo, z_ojo,  // posicion del ojo
		x_ojo, 40, 0.0,      // hacia que punto mira  (0,0,0)
		0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)    

		//aqui es donde hay que poner el codigo de dibujo

	remy.Pintar();
	disparos.Dibuja();
	gatitos.Dibuja();

	if (nivel == 1)
	{
		escenario.PintarLvl1();
	}
	if (nivel == 2)
	{
		escenario.PintarLvl2();
	}
	if (nivel == 3)
	{
		escenario.PintarLvl3();
	}
	if (nivel == 4)
	{
		escenario.PintarLvl4();
	}
}

void Mundo::Mueve()
{
	escenario.Mueve(0.025f);
	disparos.Mueve(0.025f);
	//disparos.Rebote(gatitos);
	disparos.Rebote(escenario.plataformas);


	gatitos.Mueve(0.025f);
	//gatitos.Rebote();
	gatitos.Rebote(remy);
	//gatitos.Rebote(disparos);

	remy.Mover(0.025f);
	Interaccion::rebote(remy);

	Interaccion::rebote(remy, escenario);

	for (int i = 0; i < gatitos.GetNumero(); i++)
	{
		Interaccion::rebote(*gatitos[i]);
		for (int j = 0; j < disparos.GetNumero(); j++)
		{
			if (Interaccion::rebote(*disparos[i], *gatitos[i]))
			{
				//Falta poner un sprite de muerte del gato
				gatitos.Eliminar(gatitos[i]);
				disparos.Eliminar(disparos[i]);
			}
		}
	}

}

void Mundo::Inicializa()
{
	x_ojo=0;
	y_ojo=45;
	z_ojo=120;


	remy.SetPosicion(-10, 50);
	remy.SetVelocidad(0, 0);
	remy.SetVida(3);

	nivel = 0;
	CargarNivel();

	/*escenario.SetPlataformas();
	
	Gatitos* auxg = new Gatitos(20, 0);
	gatitos.agregar(auxg);*/
}

int Mundo::GetVida()
{
	return remy.GetVida();
}

void Mundo::Tecla(unsigned char key)
{
	switch (key)
	{
	case' ':
		if (remy.GetXVelocidad() >= 0)
		{
			if (disparos.GetNumero() == 0)
				ETSIDI::play("sonidos/espada.mp3");
			Disparo* aux = new Disparo(remy.GetXPosicion(), remy.GetYPosicion() + 7.5);
			disparos.agregar(aux);
		}
		else
		{
			if (disparos.GetNumero() == 0)
				ETSIDI::play("sonidos/espada.mp3");
			Disparo* aux = new Disparo(remy.GetXPosicion(), remy.GetYPosicion() + 7.5, -50);
			disparos.agregar(aux);
		}
		break;
	}
}

void Mundo::teclaEspecial(unsigned char _key) {
	
	switch (_key)
	{
	case GLUT_KEY_LEFT:
		remy.SetVelocidad(-65.0f, remy.GetYVelocidad());
		break;
	case GLUT_KEY_RIGHT:
		remy.SetVelocidad(65.0f, remy.GetYVelocidad());
		break;
	case GLUT_KEY_UP:
		if ((remy.GetYPosicion() == 0) || remy.GetYPosicion() == 21 || remy.GetYPosicion() == 41 || remy.GetYPosicion() == 61)
			remy.SetVelocidad(remy.GetXVelocidad(), 68);
		break;
	}
}

void Mundo::teclaArriba(unsigned char _key)
{
	switch (_key)
	{
	case GLUT_KEY_LEFT:
		
		remy.SetVelocidad(0, remy.GetYVelocidad());
		break;
	case GLUT_KEY_RIGHT:
		
			remy.SetVelocidad(0, remy.GetYVelocidad());
		break;
	}
}
