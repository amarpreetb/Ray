#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//#define _CRT_SECURE_NO_WARNINGS

typedef char unsigned u8;
typedef short unsigned u16;
typedef int unsigned u32;
typedef char s8;
typedef short s16;
typedef int s32;
typedef float f32;


struct bitmap_header
{
	u16 FileType;
	u32 FileSize;
	u32 BitmapOffset;
	u32 Size;
	s32 Width;
	s32 Height;
	u16 Planes;
	u16 BitsPerPixel;
	u32 Compression;
	u32 SizeOfBitmap;
	s32 HorzResolution;
	s32 VerResolution;
	u32 ColorUsed;
	u32 ColorImportant;
};


int main(int ArgCount, char **Args)
{
	printf("Hello\n");

	u32 OutputWidth = 1280;
	u32 OutputHeight = 720;

	u32 OutputPixelSize = sizeof(u32)*OutputWidth*OutputHeight;

	u32 *OutputPixels = (u32 *)malloc(OutputPixelSize);
	u32 *Out = OutputPixels;

	for (u32 Y = 0; Y < OutputHeight; ++Y)
	{
		for (u32 X = 0; X < OutputWidth; ++X)
		{
			*Out++ = (Y < 32) ? 0xFFFF0000 : 0xFF0000FF;
		}

	}

	/*
	Bitmap Heder
	*/
	bitmap_header Header = {};
	Header.FileType = 0x4d42;
	Header.FileSize = sizeof(Header) + OutputPixelSize;
	Header.BitmapOffset = sizeof(Header);
	Header.Size = sizeof(Header) - 14;
	Header.Width = OutputWidth;
	Header.Height = -(s32)OutputHeight;
	Header.Planes = 1;
	Header.BitsPerPixel = 32;
	Header.Compression = 0;
	Header.SizeOfBitmap = OutputPixelSize;
	Header.HorzResolution = 0;
	Header.VerResolution = 0;
	Header.ColorUsed = 0;
	Header.ColorImportant = 0;

	/*
	Header.RedMast = 0x00FF0000;
	Header.GreenMask = 0x0000FF00;
	Header.BlueMask = 0x000000FF;
	*/
	
	char *OutputFileName = "test.bmp";
	FILE *OutFile = fopen(OutputFileName, "wb");
	if (OutFile)
	{
		fwrite(&Header, sizeof(Header), 1, OutFile);
		fwrite(OutputPixels, OutputPixelSize, 1, OutFile);
		fclose(OutFile);
	}
	else
	{
		fprintf(stderr, "Error!! Cannot open the file %s.\n", OutputFileName);
	}

	return (0);
}