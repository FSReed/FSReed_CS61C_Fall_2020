/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
	FILE *fp = fopen(filename, "r");
	char buff[20];
	uint32_t column, row;
	uint8_t pixel;
	fscanf(fp, "%s", buff);
	fscanf(fp, "%u %u", &column, &row);
	fscanf(fp, "%hhu", &pixel);
	
	// Now we're going to get the image data.
	Image* image = (Image*) malloc(sizeof(Image));
	image->rows = row;
	image->cols = column;
	image->image = (Color**) malloc(sizeof(Color*) * image->rows);
	int i, j;
	uint32_t R, G, B;
	for (i = 0; i < image->rows; i++) {

		// Forget this line at first, which causes Segmentation Fault.
		image->image[i] = (Color*) malloc(sizeof(Color) * image->cols);
		
		for (j = 0; j < image->cols; j++) {
			fscanf(fp, "%u %u %u", &R, &G, &B);
			Color* tmp = &image->image[i][j];
			tmp->R = (uint8_t)R;
			tmp->G = (uint8_t)G;
			tmp->B = (uint8_t)B;
		}
	}
	// Close the file.
	fclose(fp);

	return image;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
	printf("P3\n");
	printf("%d %d\n", image->cols, image->rows);
	printf("%d\n", 255);
	int i, j;
	for (i = 0; i < image->rows; i++) {
		for (j = 0; j <image->cols; j++) {
			Color* tmp = &(image->image[i][j]);
			printf("%3d %3d %3d", tmp->R, tmp->G, tmp->B);
			if (j != image->cols - 1) {
				printf("   ");
			}
		}
		printf("\n");
	}
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	int i;
	for (i = 0; i < image->rows; i++) {
		free(image->image[i]);
	}
	free(image->image);
	free(image);
}
