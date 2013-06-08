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

#include "exercises.h"

/*
  EXERCISES
*/

void exercise1(int argc, char *argv[])
{
  PGMImage *image;

  if (argc != 3)
  {
    printf("USAGE:\n%s 1 <image path>", argv[0]);
    return;
  }

  image = PGMImage_from_file(argv[2]);
  if (!image)
  {
    printf("FATAL ERROR: can't find image %s\n", argv[2]);
    return;
  }

  printf("EXERCISE 1\n");
  printf("Highest pixel value is %d\n", PGMImage_max_depth(image));
  printf("Lowest pixel value is %d\n", PGMImage_min_depth(image));
  PGMImage_free(image);
}

void exercise2(int argc, char *argv[])
{
  PGM_PIXEL value;
  PGMImage *image;

  if (argc != 4)
  {
    printf("USAGE:\n%s 2 <image path> <threshold value>");
    return;
  }

  image = PGMImage_from_file(argv[2]);
  value = (PGM_PIXEL)atoi(argv[3]);

  if (!image)
  {
    printf("FATAL ERROR: can't find image %s\n", argv[2]);
    return;
  }

  printf("EXERCISE 2\n");
  PGMImage_binarize(image, value);
  PGMImage_to_file(image, "output.pgm");
  PGMImage_free(image);
  printf("Binarized image %s with threshold %d to output.pgm\n", argv[2], value);
}

void exercise3(int argc, char *argv[])
{
  PGMImage *first_image, *second_image;

  if (argc != 4)
  {
    printf("USAGE:\n%s 3 <first image path> <second image path>", argv[0]);
    return;
  }

  first_image = PGMImage_from_file(argv[2]);
  second_image = PGMImage_from_file(argv[3]);
  if (!(first_image && second_image))
  {
    printf("FATAL ERROR: Images can't be found\n");
    PGMImage_free(first_image);
    PGMImage_free(second_image);
    return;
  }

  printf("EXERCISE 3\n");
  if (PGMImage_are_equal(first_image, second_image))
  {
    printf("The images ARE equal\n");
  }
  else
  {
    printf("The images ARE NOT equal\n");
  }

  PGMImage_free(first_image);
  PGMImage_free(second_image);
}

void exercise45(int argc, char *argv[], PGM_BOOL mode)
{
  PGMImage *first_image, *second_image, *output;

  if (argc != 4)
  {
    printf("USAGE:\n%s 4 <first image path> <second image path>", argv[0]);
    return;
  }

  first_image = PGMImage_from_file(argv[2]);
  second_image = PGMImage_from_file(argv[3]);

  if (!(first_image && second_image))
  {
    printf("FATAL ERROR: Images can't be found\n");
    PGMImage_free(first_image);
    PGMImage_free(second_image);
    return;
  }

  if (!PGMImage_compatible_format(first_image, second_image))
  {
    printf("FATAL ERROR: Images doesn't have the same format\n");
    PGMImage_free(first_image);
    PGMImage_free(second_image);
    return;
  }

  printf("EXERCISE %s\n", (mode ? "4" : "5"));
  output = (mode == PGM_SUPREME) ? PGMImage_supreme(first_image, second_image) : PGMImage_infimum(first_image, second_image);
  PGMImage_to_file(output, "output.pgm");
  PGMImage_free(first_image);
  PGMImage_free(second_image);
  PGMImage_free(output);
  printf("Saved %s of %s and %s as output.pgm\n", (mode ? "supreme" : "infimum"), argv[2], argv[3]);
}

void exercise67(int argc, char *argv[], PGM_BOOL mode)
{
  PGMImage *image, *output;

  if (argc != 3)
  {
    printf("USAGE:\n%s %s <image path>\n", argv[0], argv[1]);
    return;
  }

  image = PGMImage_from_file(argv[2]);
  if (!image)
  {
    printf("FATAL ERROR: Image %s can't be found\n", argv[2]);
    PGMImage_free(image);
    return;
  }

  printf("EXERCISE %s\n", argv[1]);
  if (mode)
  {
    output = PGMImage_erosion_base(image);
  }
  else
  {
    output = PGMImage_dilation_base(image);
  }

  PGMImage_to_file(output, "output.pgm");
  PGMImage_free(image);
  PGMImage_free(output);
  printf("Saved %s version of %s as output.pgm\n", (mode ? "erotion" : "dilation"), argv[2]);
}

void exercise8(int argc, char *argv[])
{
  PGMImage *first_image, *second_image;

  if (argc != 4)
  {
    printf("USAGE:\n%s 8 <first image path> <second image path>\n", argv[0]);
    return;
  }

  first_image = PGMImage_from_file(argv[2]);
  second_image = PGMImage_from_file(argv[3]);
  if (!(first_image && second_image))
  {
    printf("FATAL ERROR: Images can't be found\n");
    PGMImage_free(first_image);
    PGMImage_free(second_image);
    return;
  }

  if (!PGMImage_compatible_format(first_image, second_image))
  {
    printf("FATAL ERROR: Images doesn't have the same format\n");
    PGMImage_free(first_image);
    PGMImage_free(second_image);
    return;
  }

  printf("EXERCISE 8\n");
  printf("Comparison between %s and %s:\n", argv[2], argv[3]);
  printf("greater: %s\n", PGM_BOOL_TO_STR(PGMImage_is_greater_than(first_image, second_image, FALSE)));
  printf("greater (strictly): %s\n", PGM_BOOL_TO_STR(PGMImage_is_greater_than(first_image, second_image, TRUE)));
  printf("lesser: %s\n", PGM_BOOL_TO_STR(PGMImage_is_lesser_than(first_image, second_image, FALSE)));
  printf("lesser (strictly): %s\n", PGM_BOOL_TO_STR(PGMImage_is_lesser_than(first_image, second_image, TRUE)));
  PGMImage_free(first_image);
  PGMImage_free(second_image);
}

void exercise910(int argc, char *argv[], PGM_BOOL mode)
{
  PGM_VALUE size;
  PGMImage *image, *output;

  if (argc != 4)
  {
    printf("USAGE:\n%s %s <image path> <size>\n", argv[0], argv[1]);
    return;
  }

  image = PGMImage_from_file(argv[2]);
  size = (PGM_VALUE)atoi(argv[3]);

  if (!image)
  {
    printf("FATAL ERROR: Image %s can't be found\n", argv[2]);
    PGMImage_free(image);
    return;
  }

  printf("EXERCISE %s\n", argv[1]);
  if (mode)
  {
    output = PGMImage_erosion(image, size);
  }
  else
  {
    output = PGMImage_dilation(image, size);
  }

  PGMImage_to_file(output, "output.pgm");
  PGMImage_free(image);
  PGMImage_free(output);
  printf("Saved %s version of %s (size %d) as output.pgm\n", (mode ? "erotion" : "dilation"), argv[2], size);
}

void exercise1112(int argc, char *argv[], PGM_BOOL mode)
{
  PGM_VALUE size;
  PGMImage *image, *output;

  if (argc != 4)
  {
    printf("USAGE:\n%s %s <image path> <size>\n", argv[0], argv[1]);
    return;
  }

  image = PGMImage_from_file(argv[2]);
  size = (PGM_VALUE)atoi(argv[3]);

  if (!image)
  {
    printf("FATAL ERROR: Image %s can't be found\n", argv[2]);
    PGMImage_free(image);
    return;
  }

  printf("EXERCISE %s\n", argv[1]);
  if (mode)
  {
    output = PGMImage_opening(image, size);
  }
  else
  {
    output = PGMImage_closing(image, size);
  }

  PGMImage_to_file(output, "output.pgm");
  PGMImage_free(image);
  PGMImage_free(output);
  printf("Saved %s version of %s (size %d) as output.pgm\n", (mode ? "opening" : "closing"), argv[2], size);
}

void exercise13(int argc, char *argv[])
{
  PGMImage *image, *inversed;

  if (argc != 3)
  {
    printf("USAGE:\n%s 13 <image path>\n", argv[0]);
    return;
  }

  image = PGMImage_from_file(argv[2]);
  if (!image)
  {
    printf("FATAL ERROR: can't find image %s\n", argv[2]);
    return;
  }

  printf("EXERCISE 13\n");
  inversed = PGMImage_inverse(image);
  PGMImage_to_file(inversed, "output.pgm");
  printf("Saved inversed version of %s as output\n", argv[2]);
  PGMImage_free(inversed);
  PGMImage_free(image);
}

void exercise14(int argc, char *argv[])
{
  PGMImage *image, *opening, *closing, *closing_opening, *opening_closing;

  if (argc != 3)
  {
    printf("USAGE:\n%s 14 <image path>\n", argv[0]);
    return;
  }

  image = PGMImage_from_file(argv[2]);
  if (!image)
  {
    printf("FATAL ERROR: can't find image %s\n", argv[2]);
    return;
  }

  printf("EXERCISE 14\n");
  opening = PGMImage_opening(image, 1);
  closing = PGMImage_closing(image, 1);
  closing_opening = PGMImage_closing(opening, 1);
  opening_closing = PGMImage_opening(closing, 1);

  PGMImage_to_file(opening, "outputs/opening.pgm");
  PGMImage_to_file(closing, "outputs/closing.pgm");
  PGMImage_to_file(closing_opening, "outputs/closing_opening.pgm"); 
  PGMImage_to_file(opening_closing, "outputs/opening_closing.pgm");
  printf("Saved filtered versions of %s at the outputs directory\n", argv[2]);

  PGMImage_free(opening);
  PGMImage_free(closing);
  PGMImage_free(closing_opening);
  PGMImage_free(opening_closing);
  PGMImage_free(image);
}

void exercise1516(int argc, char *argv[], PGM_BOOL mode)
{
  PGM_VALUE size;
  PGMImage *image, *output;

  if (argc != 4)
  {
    printf("USAGE:\n%s %s <image path> <size>\n", argv[0], argv[1]);
    return;
  }

  image = PGMImage_from_file(argv[2]);
  size = atoi(argv[3]);

  if (!image)
  {
    printf("FATAL ERROR: can't find image %s\n", argv[2]);
    return;
  }

  printf("EXERCISE %s\n", argv[1]);
  if (mode)
  {
    output = PGMImage_opening_closing(image, size);
  }
  else
  {
    output = PGMImage_closing_opening(image, size);
  }

  PGMImage_to_file(output, "output.pgm");
  printf("Saved %s version of %s (size %d) as output\n", (mode ? "opening(closing)" : "closing(opening)"), argv[2], size);
  PGMImage_free(output);
  PGMImage_free(image);
}

void exercise17(int argc, char *argv[])
{
  PGM_VALUE range_min, range_max;
  PGMImage *image, *binary;

  if (argc != 5)
  {
    printf("USAGE:\n%s 17 <image path> <range_min> <range_max>\n", argv[0]);
    return;
  }

  image = PGMImage_from_file(argv[2]);
  range_min = atoi(argv[3]);
  range_max = atoi(argv[4]);

  if (!image)
  {
    printf("FATAL ERROR: can't find image %s\n", argv[2]);
    return;
  }

  printf("EXERCISE 17\n");
  binary = PGMImage_binarize_within(image, range_min, range_max);
  PGMImage_to_file(binary, "output.pgm");
  printf("Saved binarized (within [%d, %d]) version of %s as output\n", range_min, range_max, argv[2]);
  PGMImage_free(binary);
  PGMImage_free(image);
}

void exercise1920(int argc, char *argv[], PGM_BOOL is_addition)
{
  PGMImage *first_image, *second_image, *output;

  if (argc != 4)
  {
    printf("USAGE:\n%s %s <first_image path> <second_image_path>\n", argv[0], argv[1]);
    return;
  }

  first_image = PGMImage_from_file(argv[2]);
  second_image = PGMImage_from_file(argv[3]);

  if (!(first_image && second_image))
  {
    printf("FATAL ERROR: Images can't be found\n");
    PGMImage_free(first_image);
    PGMImage_free(second_image);
    return;
  }

  if (!PGMImage_compatible_format(first_image, second_image))
  {
    printf("FATAL ERROR: Images doesn't have the same format\n");
    PGMImage_free(first_image);
    PGMImage_free(second_image);
    return;
  }

  printf("EXERCISE %s\n", argv[1]);
  if (is_addition)
  {
    output = PGMImage_addition(first_image, second_image);
  }
  else
  {
    output = PGMImage_subtraction(first_image, second_image);
  }

  PGMImage_to_file(output, "output.pgm");
  printf("Saved %s version of %s plus %s as output\n", (is_addition ? "addition" : "subtraction"), argv[2], argv[3]);
  PGMImage_free(first_image);
  PGMImage_free(second_image);
  PGMImage_free(output);
}

void exercise21(int argc, char *argv[])
{
  PGM_VALUE size;
  PGMImage *image, *output;

  if (argc != 4)
  {
    printf("USAGE:\n%s 21 <image path> <size>\n", argv[0]);
    return;
  }

  image = PGMImage_from_file(argv[2]);
  size = atoi(argv[3]);

  if (!image)
  {
    printf("FATAL ERROR: can't find image %s\n", argv[2]);
    return;
  }

  printf("EXERCISE 21\n");
  output = PGMImage_gradient(image, size);
  PGMImage_to_file(output, "output.pgm");
  printf("Saved grandient version of %s (size %s) as output\n", argv[2], argv[3]);
  PGMImage_free(output);
  PGMImage_free(image);
}

void exercise22(int argc, char *argv[])
{
  PGMImage *image, *output;

  if (argc != 3)
  {
    printf("USAGE:\n%s 22 <image path>\n", argv[0]);
    return;
  }

  image = PGMImage_from_file(argv[2]);
  if (!image)
  {
    printf("FATAL ERROR: can't find image %s\n", argv[2]);
    return;
  }

  printf("EXERCISE 22\n");
  output = PGMImage_normalize(image);
  PGMImage_to_file(output, "output.pgm");
  printf("Saved normalized version of %s as output\n", argv[2]);
  PGMImage_free(output);
  PGMImage_free(image);
}

void exercise23(int argc, char *argv[])
{
  PGM_VALUE height, width;
  PGMImage *image, *output;

  if (argc != 5)
  {
    printf("USAGE:\n%s 23 <image path> <height> <width>\n", argv[0]);
    return;
  }

  image = PGMImage_from_file(argv[2]);
  height = atoi(argv[3]);
  width = atoi(argv[4]);

  if (!image)
  {
    printf("FATAL ERROR: can't find image %s\n", argv[2]);
    return;
  }

  printf("EXERCISE 23\n");
  output = PGMImage_flatzone(image, height, width);
  PGMImage_to_file(output, "output.pgm");
  printf("Saved flatzone version of %s (at %s, %s) as output\n", argv[2], argv[3], argv[4]);
  PGMImage_free(output);
  PGMImage_free(image);
}

void exercise2425(int argc, char *argv[], PGM_BOOL mode)
{
  PGMImage *image, *output;

  if (argc != 3)
  {
    printf("USAGE:\n%s %s <image path>\n", argv[0], argv[1]);
    return;
  }

  image = PGMImage_from_file(argv[2]);
  if (!image)
  {
    printf("FATAL ERROR: Image %s can't be found\n", argv[2]);
    PGMImage_free(image);
    return;
  }

  printf("EXERCISE %s\n", argv[1]);
  if (mode)
  {
    // WARNING: memory leak
    output = PGMImage_inverse(image);
    output = PGMImage_dilation_base(output);
    output = PGMImage_inverse(output);
  }
  else
  {
    // WARNING: memory leak
    output = PGMImage_inverse(image);
    output = PGMImage_erosion_base(output);
    output = PGMImage_inverse(output);
  }

  PGMImage_to_file(output, "output.pgm");
  PGMImage_free(image);
  PGMImage_free(output);
  printf("Saved %s version (by inversion) of %s as output.pgm\n", (mode ? "erotion" : "dilation"), argv[2]);
}

/*
  MAIN
*/

/*
  TODO
  Move every exercise to a different source file
*/

int main(int argc, char *argv[])
{

  if (argc < 2)
  {
    printf("USAGE:\n%s <exercise number> ...\n", argv[0]);
    exit(-1);
  }

  switch(atoi(argv[1]))
  {
    case 1:
      exercise1(argc, argv);
      break;

    case 2:
      exercise2(argc, argv);
      break;

    case 3:
      exercise3(argc, argv);
      break;

    case 4:
      exercise45(argc, argv, PGM_SUPREME);
      break;

    case 5:
      exercise45(argc, argv, PGM_INFIMUM);
      break;

    case 6:
      exercise67(argc, argv, PGM_EROTION);
      break;

    case 7:
      exercise67(argc, argv, PGM_DILATION);
      break;

    case 8:
      exercise8(argc, argv);
      break;

    case 9:
      exercise910(argc, argv, PGM_EROTION);
      break;

    case 10:
      exercise910(argc, argv, PGM_DILATION);
      break;

    case 11:
      exercise1112(argc, argv, PGM_OPENING);
      break;

    case 12:
      exercise1112(argc, argv, PGM_CLOSING);
      break;

    case 13:
      exercise13(argc, argv);
      break;

    case 14:
      exercise14(argc, argv);
      break;

    case 15:
      exercise1516(argc, argv, PGM_OPENING_CLOSING);
      break;

    case 16:
      exercise1516(argc, argv, PGM_CLOSING_OPENING);
      break;

    case 17:
      exercise17(argc, argv);
      break;

    case 19:
      exercise1920(argc, argv, TRUE);
      break;

    case 20:
      exercise1920(argc, argv, FALSE);
      break;

    case 21:
      exercise21(argc, argv);
      break;

    case 22:
      exercise22(argc, argv);
      break;

    case 23:
      exercise23(argc, argv);
      break;

    case 24:
      exercise2425(argc, argv, PGM_EROTION);
      break;

    case 25:
      exercise2425(argc, argv, PGM_DILATION);
      break;
  }

  return 0;
}

