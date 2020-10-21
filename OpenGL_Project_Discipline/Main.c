//#include <stdio.h> 
//#include <corecrt_malloc.h>
//#include <conio.h>
//#include "Nave.h"
//
//
//void Render(Nave* p);
//
//int main()
//{
//	Nave* p = NULL;
//	int size = 5;
//	
//	p = (Nave*)malloc(sizeof(Nave));
//
//	p->posicao = (float*)malloc(sizeof(float) * size);
//	p->x = 0;
//	p->y = 0;
//
//	for (int i = 0; i < size; i++)
//		p->posicao[i] = i + 1.0;
//
//	printf("\n");
//	Render(p);
//	printf("\n");
//	
//	free(p->posicao);
//	free(p);
//
//	return 0;
//}
//
//void Render(Nave* p) {
//	int ExecutarLoop = true;
//
//	while (ExecutarLoop)
//	{
//		switch (toupper(getch()))
//		{
//		case 'A':
//			MoverMinus(&p->x, ACELERACAO);
//			break;
//		case 'D':
//			MoverPlus(&p->x, ACELERACAO);
//			break;
//		case 'W':
//			MoverPlus(&p->y, ACELERACAO);
//			break;
//		case 'S':
//			MoverPlus(&p->y, ACELERACAO);
//			break;
//		case 'P':
//			ExecutarLoop = false;
//			break;
//		default:
//			break;
//		}
//		printf("(%.2f, %.2f)\n", p->x, p->y);
//	}
//}
