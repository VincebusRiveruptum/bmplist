struct FileHeader{
	unsigned char ID[2];
	long Size;
	int Res1[2];
	long Offset;	/* Offset de la imagen donde se encuentra */
};

struct InfoHeader{
	/* Header tipo W3.0 */
	long Hsize;
	long X;
	long Y;
	int NumColorPlanes;
	int BitsPerPixel;
	long CompressionMethod;
	long ImgSize;
	long ResX;
	long ResY;
	long NumColors;
	long NumImportantColors;
};

struct Color{
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char i;
};

struct ImagenBMP{
	struct FileHeader fh;
	struct InfoHeader ih;
	struct Color **Paleta;          // struct Color Paleta[255];
	char **imagen;
};

struct Secuencia{
	char **imagen;
	unsigned char width;
	unsigned char height;
	struct Secuencia *ant, *sig;
};


struct Animacion{
	int numFrames;
	struct Color **Paleta;		// struct Color Paleta[255];
	struct Secuencia *head;
};

/////}

typedef struct ImagenBMP ImagenBMP;
typedef struct Secuencia Secuencia;
typedef struct Color Color;