/*
 Copyright (c) 2011 Martin Abente Lahaye. - martin.abente.lahaye@gmail.com

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 MA 02110-1301 USA.
*/

#ifndef PGM_H
#define PGM_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"

#define TRUE 1
#define FALSE 0
#define BUFFER_SIZE 1024

#define PGM_SIZE(image) (image->width*image->height)
#define PGM_PIXEL_FIRST(image) (image->pixels[0][0])
#define PGM_PIXEL_LAST(image) (image->pixels[image->height-1][image->width-1])
#define PGM_PIXEL_GREATER(f_image, s_image, h, w, s) (s ? (f_image->pixels[h][w] > s_image->pixels[h][w]) : (f_image->pixels[h][w] >= s_image->pixels[h][w]))
#define PGM_PIXEL_LESSER(f_image, s_image, h, w, s) (s ? (f_image->pixels[h][w] < s_image->pixels[h][w]) : (f_image->pixels[h][w] <= s_image->pixels[h][w]))
#define PGM_PIXEL_MAX(f_image, s_image, h, w) ( f_image->pixels[h][w] >= s_image->pixels[h][w] ? f_image->pixels[h][w] : s_image->pixels[h][w])
#define PGM_PIXEL_MIN(f_image, s_image, h, w) ( f_image->pixels[h][w] <= s_image->pixels[h][w] ? f_image->pixels[h][w] : s_image->pixels[h][w])
#define PGM_PIXEL_WITHIN(image, h, w, min, max) ( (image->pixels[h][w] >= min && image->pixels[h][w] <= max ) ? image->depth : 0 )
#define PGM_PIXEL_SUB(f_image, s_image, h, w) ( f_image->pixels[h][w] <= s_image->pixels[h][w] ? 0 : f_image->pixels[h][w] - s_image->pixels[h][w])
#define PGM_PIXEL_NORM(image, h, w, min, max) ( (unsigned char)((float)(image->pixels[h][w] - min) * ((float)image->depth / (float)(max - min))))
#define PGM_HEIGHT_FITS(image, h) ((h >= 0 && h < image->height) ? 1 : 0)
#define PGM_WIDTH_FITS(image, w) ((w >= 0 && w < image->width) ? 1 : 0)

#define PGM_PIXEL_SAFE_MAX(image, h, w) ((PGM_HEIGHT_FITS(image, h) && PGM_WIDTH_FITS(image, w)) ? image->pixels[h][w] : 0)
#define PGM_VALUE_MAX(value1, value2) (value1 >= value2 ? value1 : value2)
#define PGM_MAX_3X3(image, h, w) (PGM_VALUE_MAX(PGM_VALUE_MAX(PGM_VALUE_MAX(PGM_VALUE_MAX(PGM_PIXEL_SAFE_MAX(image, h-1, w-1), PGM_PIXEL_SAFE_MAX(image, h-1, w)),PGM_VALUE_MAX(PGM_PIXEL_SAFE_MAX(image, h-1, w+1), PGM_PIXEL_SAFE_MAX(image, h, w-1))),PGM_VALUE_MAX(PGM_VALUE_MAX(PGM_PIXEL_SAFE_MAX(image, h, w), PGM_PIXEL_SAFE_MAX(image, h, w+1)),PGM_VALUE_MAX(PGM_PIXEL_SAFE_MAX(image, h+1, w-1), PGM_PIXEL_SAFE_MAX(image, h+1, w)))),PGM_PIXEL_SAFE_MAX(image, h+1, w+1)))

#define PGM_PIXEL_SAFE_MIN(image, h, w) ((PGM_HEIGHT_FITS(image, h) && PGM_WIDTH_FITS(image, w)) ? image->pixels[h][w] : image->depth)
#define PGM_VALUE_MIN(value1, value2) (value1 <= value2 ? value1 : value2)
#define PGM_MIN_3X3(image, h, w) (PGM_VALUE_MIN(PGM_VALUE_MIN(PGM_VALUE_MIN(PGM_VALUE_MIN(PGM_PIXEL_SAFE_MIN(image, h-1, w-1), PGM_PIXEL_SAFE_MIN(image, h-1, w)),PGM_VALUE_MIN(PGM_PIXEL_SAFE_MIN(image, h-1, w+1), PGM_PIXEL_SAFE_MIN(image, h, w-1))),PGM_VALUE_MIN(PGM_VALUE_MIN(PGM_PIXEL_SAFE_MIN(image, h, w), PGM_PIXEL_SAFE_MIN(image, h, w+1)),PGM_VALUE_MIN(PGM_PIXEL_SAFE_MIN(image, h+1, w-1), PGM_PIXEL_SAFE_MIN(image, h+1, w)))),PGM_PIXEL_SAFE_MIN(image, h+1, w+1)))

#define PGM_SUPREME 1
#define PGM_INFIMUM 0
#define PGM_EROTION 1
#define PGM_DILATION 0
#define PGM_OPENING 1
#define PGM_CLOSING 0
#define PGM_OPENING_CLOSING 1
#define PGM_CLOSING_OPENING 0
#define PGM_BOOL_TO_STR(boolean) (boolean ? "TRUE" : "FALSE")

typedef unsigned char PGM_PIXEL;
typedef unsigned int PGM_VALUE;
typedef unsigned int PGM_BOOL;

typedef struct
{
  PGM_VALUE version;
  PGM_VALUE width;
  PGM_VALUE height;
  PGM_VALUE depth;
  PGM_PIXEL **pixels;
} PGMImage;

void PGMImage_free(PGMImage *image);
PGM_BOOL PGMImage_compatible_format(PGMImage *first_image, PGMImage *second_image);
PGMImage *PGMImage_clone_format(PGMImage *image);
void PGMImage_empty(PGMImage *image);
PGMImage *PGMImage_from_file(char *filepath);
void PGMImage_to_file(PGMImage *image, char *filepath);
PGM_PIXEL PGMImage_max_depth(PGMImage *image);
PGM_PIXEL PGMImage_min_depth(PGMImage *image);
void PGMImage_binarize(PGMImage *image, PGM_PIXEL value);
PGMImage *PGMImage_binarize_within(PGMImage *image, PGM_PIXEL range_min, PGM_PIXEL range_max);
PGMImage *PGMImage_binarize_equal(PGMImage *image, PGM_PIXEL value);
PGM_BOOL PGMImage_are_equal(PGMImage *image, PGMImage *image_cmp);
PGM_BOOL PGMImage_is_greater_than(PGMImage *first_image, PGMImage *second_image, PGM_BOOL strictly);
PGM_BOOL PGMImage_is_lesser_than(PGMImage *first_image, PGMImage *second_image, PGM_BOOL strictly);
PGMImage *PGMImage_supreme(PGMImage *first_image, PGMImage *second_image);
PGMImage *PGMImage_infimum(PGMImage *first_image, PGMImage *second_image);
PGMImage *PGMImage_erosion_base(PGMImage *image);
PGMImage *PGMImage_dilation_base(PGMImage *image);
PGMImage *PGMImage_erosion(PGMImage *image, PGM_VALUE size);
PGMImage *PGMImage_dilation(PGMImage *image, PGM_VALUE size);
PGMImage *PGMImage_opening(PGMImage *image, PGM_VALUE size);
PGMImage *PGMImage_closing(PGMImage *image, PGM_VALUE size);
PGMImage *PGMImage_inverse(PGMImage *image);
PGMImage *PGMImage_opening_closing(PGMImage *image, PGM_VALUE size);
PGMImage *PGMImage_closing_opening(PGMImage *image, PGM_VALUE size);
PGMImage *PGMImage_addition(PGMImage *first_image, PGMImage *second_image);
PGMImage *PGMImage_subtraction(PGMImage *first_image, PGMImage *second_image);
PGMImage *PGMImage_gradient(PGMImage *image, PGM_VALUE size);
PGMImage *PGMImage_normalize(PGMImage *image);
PGMImage *PGMImage_flatzone(PGMImage *image, PGM_VALUE height, PGM_VALUE width);
#endif
