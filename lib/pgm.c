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

#include "pgm.h"

void PGMImage_free(PGMImage *image)
{
  PGM_VALUE height;
  
  if (!image)
  {
    printf("WARNING: trying to release NULL image\n");
    return;
  }

  for (height = 0;  height < image->height; height++)
  {
    free(image->pixels[height]);
  }

  free(image->pixels);
  free(image);
}

PGM_BOOL PGMImage_compatible_format(PGMImage *first_image, PGMImage *second_image)
{
  if (first_image->version != second_image->version)
  {
    return FALSE;
  }

  if (first_image->height != second_image->height)
  {
    return FALSE;
  }

  if (first_image->width != second_image->width)
  {
    return FALSE;
  }

  if (first_image->depth != second_image->depth)
  {
    return FALSE;
  }

  return TRUE;
}

PGMImage *PGMImage_clone_format(PGMImage *image)
{
  PGM_VALUE height;
  PGMImage *clone;

  clone = (PGMImage*)malloc(sizeof(PGMImage));
  clone->version = image->version;
  clone->width = image->width;
  clone->height = image->height;
  clone->depth = image->depth;
  clone->pixels = (PGM_PIXEL**)malloc(sizeof(PGM_PIXEL*) * image->height);
  for (height = 0; height < image->height; height++)
  {
    clone->pixels[height] = (PGM_PIXEL*)malloc(sizeof(PGM_PIXEL) * image->width); 
  }

  return clone;
}

void PGMImage_empty(PGMImage *image)
{
  PGM_VALUE height;

  for(height = 0; height < image->height; height++)
  {
      memset(image->pixels[height], 0, image->width);
  }
}

PGMImage *PGMImage_from_file(char *filepath)
{
  int size, read, height;
  PGM_PIXEL pixel;
  char buffer[BUFFER_SIZE];
  FILE *file;
  PGMImage *image;

  printf("\nLoading image %s\n", filepath);

  file = fopen(filepath, "r");
  if (!file)
  {
    printf("Can't find pgm file %s\n", filepath);
    close(file);
    return NULL;
  }

  // magic number
  fscanf(file, "%s\n", buffer);
  if (strcmp(buffer, "P5"))
  {
    printf("file %s is not an pgm file\n", filepath);
    close(file);
    return NULL;
  }
  
  image = (PGMImage*) malloc(sizeof(PGMImage));
  if (!image)
  {
    printf("Could not malloc for file %s\n");
    close(file);
    return NULL;
  }

  // version
  image->version = atoi(&buffer[1]);
  printf("%d\n", image->version);

  // separator
  fgets(buffer, BUFFER_SIZE, file);
  printf("%s", buffer);

  // dimensions
  fscanf(file, "%d %d\n", &image->width, &image->height);
  printf("%d %d\n", image->width, image->height);

  // depth
  fscanf(file, "%d\n", &image->depth);
  printf("%d\n", image->depth);

  // pixels
  read = 0;
  image->pixels = (PGM_PIXEL**)malloc(sizeof(PGM_PIXEL*) * image->height);
  for (height = 0; height < image->height; height++)
  {
    image->pixels[height] = (PGM_PIXEL*)malloc(sizeof(PGM_PIXEL) * image->width);
    read += fread(image->pixels[height], sizeof(PGM_PIXEL), image->width, file);
  }

  size = PGM_SIZE(image);
  if (read != size)
  {
    printf("FATAL ERROR: it should have %d pixels but only has %d\n", size, read);
    PGMImage_free(image);
    close(file);
    return NULL;
  }

  printf("first pixel is %d and last pixel is %d\n\n", PGM_PIXEL_FIRST(image), PGM_PIXEL_LAST(image));

  close(file);
  return image;
}

void PGMImage_to_file(PGMImage *image, char *filepath)
{
  PGM_VALUE height;
  FILE *file;

  file = fopen(filepath, "w");
  if (!file)
  {
    printf("Could not save file %s", filepath);
    return;
  }

  fprintf(file, "P%d\n", image->version);
  fprintf(file, "# altered by martin.abente.lahaye@gmail.com\n");
  fprintf(file, "%d %d\n", image->width, image->height);
  fprintf(file, "%d\n", image->depth);
  for (height = 0; height < image->height; height++)
  {
    fwrite(image->pixels[height], sizeof(PGM_PIXEL), image->width, file);
  }
  fprintf(file, "\n");

  close(file);
}

PGM_PIXEL PGMImage_max_depth(PGMImage *image)
{
  PGM_VALUE height, width;
  PGM_PIXEL max_depth;
  
  max_depth = 0;
  for (height = 0; height < image->height; height++)
  {
    for (width = 0; width < image->width; width++)
    {
      if (image->pixels[height][width] > max_depth)
      {
        max_depth = image->pixels[height][width];
      }
    }
  }

  return max_depth;
}

PGM_PIXEL PGMImage_min_depth(PGMImage *image)
{
  PGM_VALUE height, width;
  PGM_PIXEL min_depth;
  
  min_depth = image->depth;
  for (height = 0; height < image->height; height++)
  {
    for (width = 0; width < image->width; width++)
    {
      if (image->pixels[height][width] < min_depth)
      {
        min_depth = image->pixels[height][width];
      }
    }
  }

  return min_depth;
}

void PGMImage_binarize(PGMImage *image, PGM_PIXEL value)
{
  PGM_VALUE height, width;

  for (height = 0; height < image->height; height++)
  {
    for (width = 0; width < image->width; width++)
    {
      image->pixels[height][width] = (PGM_PIXEL)(image->pixels[height][width] >= value ? image->depth : 0);
    }
  }
}

PGMImage *PGMImage_binarize_within(PGMImage *image, PGM_PIXEL range_min, PGM_PIXEL range_max)
{
  PGM_VALUE height, width;
  PGMImage *binary;

  binary = PGMImage_clone_format(image);
  for(height = 0; height < image->height; height++)
  {
    for(width = 0; width < image->width;  width++)
    {
      binary->pixels[height][width] = PGM_PIXEL_WITHIN(image, height, width, range_min, range_max);
    }
  }

  return binary;
}

PGMImage *PGMImage_binarize_equal(PGMImage *image, PGM_PIXEL value)
{
  return PGMImage_binarize_within(image, value, value);
}

PGM_BOOL PGMImage_are_equal(PGMImage *image, PGMImage *image_cmp)
{
  PGM_VALUE height, width;
  
  if (image->height != image_cmp->height)
  {
    return FALSE;
  }

  if (image->width != image_cmp->width)
  {
    return FALSE;
  }

  for (height = 0; height < image->height; height++)
  {
    for (width = 0; width < image->width; width++)
    {
      if (image->pixels[height][width] != image_cmp->pixels[height][width])
      {
        return FALSE;
      }
    }
  }

  return TRUE;
}

PGM_BOOL PGMImage_is_greater_than(PGMImage *first_image, PGMImage *second_image, PGM_BOOL strictly)
{
  PGM_VALUE height, width;

  for(height = 0; height < first_image->height; height++)
  {
    for(width = 0; width < first_image->width; width++)
    {
      if (!PGM_PIXEL_GREATER(first_image, second_image, height, width, strictly))
      {
        return FALSE;
      }
    }
  }

  return TRUE;
}

PGM_BOOL PGMImage_is_lesser_than(PGMImage *first_image, PGMImage *second_image, PGM_BOOL strictly)
{
  PGM_VALUE height, width;

  for(height = 0; height < first_image->height; height++)
  {
    for(width = 0; width < first_image->width; width++)
    {
      if (!PGM_PIXEL_LESSER(first_image, second_image, height, width, strictly))
      {
        return FALSE;
      }
    }
  }

  return TRUE;
}

PGMImage *PGMImage_supreme(PGMImage *first_image, PGMImage *second_image)
{
  PGM_VALUE height, width;
  PGMImage *supreme;

  supreme = PGMImage_clone_format(first_image);

  for (height = 0; height < first_image->height; height++)
  {
    for (width = 0; width < first_image->width; width++)
    {
      supreme->pixels[height][width] =  PGM_PIXEL_MAX(first_image, second_image, height, width);
    }
  }

  return supreme;
}

PGMImage *PGMImage_infimum(PGMImage *first_image, PGMImage *second_image)
{
  PGM_VALUE height, width;
  PGMImage *infimum;

  infimum = PGMImage_clone_format(first_image);

  for (height = 0; height < first_image->height; height++)
  {
    for (width = 0; width < first_image->width; width++)
    {
      infimum->pixels[height][width] =  PGM_PIXEL_MIN(first_image, second_image, height, width);
    }
  }

  return infimum;
}

PGMImage *PGMImage_erosion_base(PGMImage *image)
{
  PGMImage *erosion;
  PGM_VALUE height, width;

  erosion = PGMImage_clone_format(image);
  for (height = 0; height < image->height; height++)
  {
    for (width = 0; width < image->width; width++)
    {
      erosion->pixels[height][width] = PGM_MIN_3X3(image, height, width);
    }
  }

  return erosion;
}

PGMImage *PGMImage_dilation_base(PGMImage *image)
{
  PGMImage *dilation;
  PGM_VALUE height, width;

  dilation = PGMImage_clone_format(image);
  for (height = 0; height < image->height; height++)
  {
    for (width = 0; width < image->width; width++)
    {
      dilation->pixels[height][width] = PGM_MAX_3X3(image, height, width);
    }
  }

  return dilation;
}

PGMImage *PGMImage_erosion(PGMImage *image, PGM_VALUE size)
{
  PGMImage *erosion, *last_erosion;
  PGM_VALUE current_size;

  erosion = PGMImage_erosion_base(image);
  for (current_size = 2; current_size <= size; current_size++)
  {
    last_erosion = PGMImage_erosion_base(erosion);
    PGMImage_free(erosion);
    erosion = last_erosion;
  }

  return erosion;
}

PGMImage *PGMImage_dilation(PGMImage *image, PGM_VALUE size)
{
  PGMImage *dilation, *last_dilation;
  PGM_VALUE current_size;

  dilation = PGMImage_dilation_base(image);
  for (current_size = 2; current_size <= size; current_size++)
  {
    last_dilation = PGMImage_dilation_base(dilation);
    PGMImage_free(dilation);
    dilation = last_dilation;
  }

  return dilation;
}

PGMImage *PGMImage_opening(PGMImage *image, PGM_VALUE size)
{
  PGMImage *erosion, *opening;

  erosion = PGMImage_erosion(image, size);
  opening = PGMImage_dilation(erosion, size);
  PGMImage_free(erosion);

  return opening;
}

PGMImage *PGMImage_closing(PGMImage *image, PGM_VALUE size)
{
  PGMImage *dilation, *closing;

  dilation = PGMImage_dilation(image, size);
  closing = PGMImage_erosion(dilation, size);
  PGMImage_free(dilation);

  return closing;
}

PGMImage *PGMImage_inverse(PGMImage *image)
{
  PGM_VALUE height, width;
  PGMImage *inverse;

  inverse = PGMImage_clone_format(image);
  for (height = 0; height < image->height; height++)
  {
    for (width = 0; width < image->width; width++)
    {
      inverse->pixels[height][width] = image->depth - image->pixels[height][width];
    }
  }

  return inverse;
}

PGMImage *PGMImage_opening_closing(PGMImage *image, PGM_VALUE size)
{
  PGMImage *closing, *opening_closing;
  
  closing = PGMImage_closing(image, size);
  opening_closing = PGMImage_opening(closing, size);
  PGMImage_free(closing);

  return opening_closing;
}

PGMImage *PGMImage_closing_opening(PGMImage *image, PGM_VALUE size)
{
  PGMImage *opening, *closing_opening;
  
  opening = PGMImage_opening(image, size);
  closing_opening = PGMImage_closing(opening, size);
  PGMImage_free(opening);

  return closing_opening;
}

PGMImage *PGMImage_addition(PGMImage *first_image, PGMImage *second_image)
{
  PGM_VALUE height, width, result;
  PGMImage *addition;

  addition = PGMImage_clone_format(first_image);
  for(height = 0; height < first_image->height; height++)
  {
    for(width = 0; width < first_image->width;  width++)
    {
      result = first_image->pixels[height][width] + second_image->pixels[height][width];
      addition->pixels[height][width] = (result > first_image->depth ? first_image->depth : result);
    }
  }

  return addition;
}

PGMImage *PGMImage_subtraction(PGMImage *first_image, PGMImage *second_image)
{
  PGM_VALUE height, width, result;
  PGMImage *subtraction;

  subtraction = PGMImage_clone_format(first_image);
  for(height = 0; height < first_image->height; height++)
  {
    for(width = 0; width < first_image->width; width++)
    {
      subtraction->pixels[height][width] = PGM_PIXEL_SUB(first_image, second_image, height, width);
    }
  }

  return subtraction;
}

PGMImage *PGMImage_gradient(PGMImage *image, PGM_VALUE size)
{
  PGMImage *gradient, *dilation, *erosion;

  dilation = PGMImage_dilation(image, size);
  erosion = PGMImage_erosion(image, size);
  gradient = PGMImage_subtraction(dilation, erosion);

  PGMImage_free(dilation);
  PGMImage_free(erosion);
  return gradient;
}

PGMImage *PGMImage_normalize(PGMImage *image)
{
  PGM_VALUE height, width;
  PGM_PIXEL pixel_max, pixel_min;
  PGMImage *normalized;

  pixel_max = PGMImage_max_depth(image);
  pixel_min = PGMImage_min_depth(image);
  normalized = PGMImage_clone_format(image);

  for(height = 0; height < image->height; height++)
  {
    for(width = 0; width < image->width; width++)
    {
      normalized->pixels[height][width] = PGM_PIXEL_NORM(image, height, width, pixel_min, pixel_max); 
    }
  }

  return normalized;
}

PGMImage *PGMImage_flatzone(PGMImage *image, PGM_VALUE height, PGM_VALUE width)
{
  Item *item;
  Queue *queue;
  PGMImage *flatzone;
  int neighbor, neighbor_height, neighbor_width;
  int position[4][2] = {          {-1, 0},
                        { 0, -1},          { 0, 1},
                                  { 1, 0}        };
  queue = Queue_new();
  Queue_push(queue, height, width);

  flatzone = PGMImage_clone_format(image);
  PGMImage_empty(flatzone);
  flatzone->pixels[height][width] = image->depth;

  while((item = Queue_pop(queue)))
  {
    for (neighbor = 0; neighbor < 4; neighbor++)
    {
      neighbor_height = item->height + position[neighbor][0];
      neighbor_width = item->width + position[neighbor][1];

      if (!(PGM_HEIGHT_FITS(image, neighbor_height) && PGM_WIDTH_FITS(image, neighbor_width)))
      {
        continue;
      }

      if (image->pixels[neighbor_height][neighbor_width] != image->pixels[height][width])
      {
        continue;
      }

      if (flatzone->pixels[neighbor_height][neighbor_width] == image->depth)
      {
        continue;
      }

      flatzone->pixels[neighbor_height][neighbor_width] = image->depth;
      Queue_push(queue, neighbor_height, neighbor_width);
    }

    free(item);
  }

  free(queue);
  return flatzone;
}

