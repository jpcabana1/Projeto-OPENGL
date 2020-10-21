#pragma once
#define true 1
#define false 0
#define ACELERACAO 0.02

typedef struct S_Nave
{
	int index;
	float *posicao;
	float x;
	float y;
}Nave;

void MoverPlus(float* coord, float accel);
void MoverMinus(float* coord, float accel);
