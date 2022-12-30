#include <stdio.h>
#include <stdlib.h>



typedef unsigned char ubyte;

/* BMP 파일의 헤더를 분석해서 원하는 정보를 얻기 위한 함수 */
extern int readBmp(char *filename, ubyte **pData, int *cols, int *rows, int *color);

/* BGR 이미지 데이터를 그레이 스케일로 변환하는 함수 */
void cvtBGR2Gray(ubyte *dest, ubyte *src, int n)
{
	for(int i =0; i<n; i++){
		int b = *src++;
		int g = *src++;
		int r = *src++;

		/* 그레이 스케일 이미지로 변환 */
		int y = (r*77)+(g*151)+(b*28);
		*dest++ = (y>>8);
		*dest++ = (y>>8);
		*dest++ = (y>>8);


	}
}


int main(int argc, char **argv)
{

	int cols, rows, color = 24;
	ubyte r, g, b, a = 255;
	ubyte *pData, *pBmpData, *pImageData, *pFbMap;
	struct fb_var_screeninfo vinfo;

	pData = (ubyte*)malloc(vinfo.xres*vinfo.yres*sizeof(ubyte)*color/8);
	pImageData = (ubyte*)malloc(vinfo.xres*vinfo.yres*sizeof(ubyte)*color/8);

	/* 프레임 버퍼에 대한 메모리 맵을 수행 */

	/* BMP 파일에서 헤더 정보를 가져옴 */
	if(readBmp(argv[1], &pImageData, &cols, &rows, &color)<0){
		perror("readBmp()");
		return -1;


	}

cvtBGR2Gray(pData, pImageData, vinfo.xres*vinfo.yres);

/* BMP 이미지 데이터를 프레임 버퍼 데이터로 변경 */



}
