#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "modox.h"
#include "tipos.h"


struct ImagenBMP *GetImagen(char *);
void EnlazarImagen(struct ImagenBMP *, struct Animacion **);
void drawBitmap(char **bitmap, unsigned char width, unsigned char height, unsigned int x, unsigned int y, int maskcolor);

Color **globalPalette = NULL;

/* Abre una imagen BMP y la retorna */
struct ImagenBMP *GetImagen(char *NombreArchivo)
{
	FILE *fp = NULL;
	struct ImagenBMP *nuevo = NULL;
	char *id = (char *)calloc(3, 1);
	int padding = 0, y;

	fp = fopen(NombreArchivo, "rb");

	if (fp == NULL)
	{ /* Error de lectura o el archivo no esta disponbile */
		printf("\nError, el archivo no existe!");
		return NULL;
	}
	else
	{
		printf("\nAbriendo %s ", NombreArchivo);
	}

	nuevo = (struct ImagenBMP *)calloc(1, sizeof(struct ImagenBMP));
	nuevo->Paleta = (struct Color **)calloc(255, sizeof(struct Color *));

	if (nuevo == NULL)
	{
		/* Si por algun motivo no se pudo crear la imagen */
		return NULL;
	}

	fread(id, 2, 1, fp);

	if (strcmp(id, "BM") != 0)
	{
		/* El archivo es invalido no se crea la imagen */
		printf("\nArchivo invalido!");
		free(nuevo);
		return NULL;
	}

	strncpy(nuevo->fh.ID, id, 2);

	fread(&(nuevo->fh), 12, 1, fp);
	fread(&(nuevo->ih), 40, 1, fp);

	printf("[ X : %ld, Y : %ld ]", nuevo->ih.X, nuevo->ih.Y);

	/* Lectura de paleta */

	fread((nuevo->Paleta), 1024, 1, fp);

	/* Lectura de imagen */

	nuevo->imagen = (char **)malloc(sizeof(char *) * nuevo->ih.Y);

	if (nuevo->imagen == NULL)
	{
		printf("\nNo se pudo dimensionar la imagen Y");
		return 0;
	}

	/* Ajuste de paridad del ancho de la imagen */
	while ((nuevo->ih.X + padding) % 4 != 0)
	{
		padding++;
	};

	for (y = nuevo->ih.Y - 1; y >= 0; y--)
	{
		nuevo->imagen[y] = (char *)malloc(sizeof(char) * nuevo->ih.X);
		if (nuevo->imagen[y] == NULL)
		{
			printf("\nNo se pudo dimensionar la imagen en el eje X, Iteracion : %d", y);
			return 0;
		}
		else
		{
			fread(nuevo->imagen[y], nuevo->ih.X + padding, 1, fp);
		}
	}

	globalPalette = (nuevo->Paleta);

	free(id);
	fclose(fp);

	printf("\t...Lectura OK");

	return nuevo;
}

void EnlazarImagen(struct ImagenBMP *nuevo, struct Animacion **anm)
{
	struct Secuencia *nuevaSec = NULL;
	struct Secuencia *rec = (*anm)->head;

	if (nuevo == NULL)
	{
		return;
	}

	if ((*anm) == NULL)
	{
		(*anm) = (struct Animacion *)calloc(1, sizeof(struct Animacion));
		(*anm)->head = NULL;
	}

	if ((*anm)->Paleta == NULL)
	{
		/* Si no hay paleta simplemente se copia la de la imagen a agregar */
		(*anm)->Paleta = nuevo->Paleta;
	}

	/* Secuencia = Mapa de bits de imagen */
	/* Dimension de nueva secuencia a agregar */
	nuevaSec = (struct Secuencia *)malloc(sizeof(struct Secuencia));
	nuevaSec->ant = nuevaSec->sig = NULL;
	nuevaSec->imagen = nuevo->imagen;
	nuevaSec->width = nuevo->ih.X,
	nuevaSec->height = nuevo->ih.Y;

	if ((*anm)->head == NULL)
	{
		(*anm)->head = nuevaSec;
	}
	else
	{

		while (rec != NULL)
		{
			if (rec->sig == NULL)
			{
				rec->sig = nuevaSec;
				rec->sig->ant = rec;
				rec = nuevaSec;
			}
			rec = rec->sig;
		}
	}
	printf("...Enlazado OK");
}

/* This will draw an image on the screen*/

void drawBitmap(char **bitmap, unsigned char width, unsigned char height, unsigned int x, unsigned int y, int maskcolor){
	long i,j;
	unsigned char color = NULL;
	char *bmp = *bitmap;

	if(bmp != NULL){
		for(i=0; i < width; i++){
			for(j=0;j < height; j++){
				color = bitmap[j][i];
				if(color != maskcolor){
					PutPixelX(i + x, j + y, color);
				}
			}
		}	
	}
}

void drawList(Secuencia **head){
	Secuencia *node = *head;

	while(node != NULL){
		drawBitmap((node->imagen), node->width, node->height ,0, 0, 255);
		node = node->sig;
	}

	return;
}

void setPalette(Color **palette){
	int i;

	for(i=0;i<256;i++){
		SetPal(i, (*palette)[i].r >> 2, (*palette)[i].g >> 2, (*palette)[i].b >> 2);
	}
}

//////////////////////////////////////////////////////////////////////
//     MAIN
//////////////////////////////////*///////////////////////////////////

int main()
{
	struct Animacion *anmtest = NULL;

	clrscr();

	EnlazarImagen(GetImagen(".\\jumptest\\frame1.bmp"), &anmtest);
	EnlazarImagen(GetImagen(".\\jumptest\\frame2.bmp"), &anmtest);
	EnlazarImagen(GetImagen(".\\jumptest\\frame3.bmp"), &anmtest);
	EnlazarImagen(GetImagen(".\\jumptest\\frame4.bmp"), &anmtest);
	EnlazarImagen(GetImagen(".\\jumptest\\frame5.bmp"), &anmtest);
	//EnlazarImagen(GetImagen(".\\jumptest\\frame6.bmp"), &anmtest);
	//nlazarImagen(GetImagen(".\\jumptest\\frame7.bmp"), &anmtest);
	//EnlazarImagen(GetImagen(".\\jumptest\\frame8.bmp"), &anmtest);
	//EnlazarImagen(GetImagen(".\\jumptest\\frame9.bmp"), &anmtest);
	//EnlazarImagen(GetImagen(".\\jumptest\\frame10.bmp"), &anmtest);
	//EnlazarImagen(GetImagen(".\\jumptest\\frame11.bmp"), &anmtest);
	//EnlazarImagen(GetImagen(".\\jumptest\\frame12.bmp"), &anmtest);
	//EnlazarImagen(GetImagen(".\\jumptest\\frame13.bmp"), &anmtest);
	//EnlazarImagen(GetImagen(".\\jumptest\\frame14.bmp"), &anmtest);
	//EnlazarImagen(GetImagen(".\\jumptest\\frame15.bmp"), &anmtest);

	getch();

	Set_320x200X();

	setPalette(&globalPalette);
	drawList(&(anmtest->head));
	//drawBitmap(anmtest->head->imagen, anmtest->head->width, anmtest->head->height ,0, 0, 0);

	getch();

	TXTModo();

	return 0;
}
