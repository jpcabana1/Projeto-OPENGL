#include "Nave.h"
#include <corecrt_malloc.h>

//Usar quando quiser mover para CIMA/DIREITA
void MoverPlus(float* coord, float accel) {
	if (*coord < 1)
	{
		*coord = *coord + accel;
	}
	else {
		*coord = 1;
	}
	
}
//Usar quando quiser mover para BAIXO/ESQUERDA
void MoverMinus(float* coord, float accel) {
	if (*coord > -1)
	{
		*coord = *coord - accel;
	}
	else {
		*coord = -1;
	};
}
