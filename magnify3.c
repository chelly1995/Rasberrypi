#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmpHeader.h"

#define BYTE unsigned char

#define widthbytes(bits)(((bits)+31)/32*4)


int main(int argc, char**argv){
	FILE *fp;
	RGBQUAD palrgb[256];

	unsigned int imagesize;
	char input[128], output[128];

	int i,j,size;
	int xFactor=2,yFactor=2;
	float srcX, srcY;
	int index;
	float r,g,b,gray;
	int graysize;
	int index2;
	int elemSize;
	int x,y,z;

	unsigned char *grayimg, *inimg, *outimg;

	

