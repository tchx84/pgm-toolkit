# pgm-toolkit
pgm-toolkit is a P5-PGM (8-bits binary Portable Gray Map) image files manipulation
library, includes basic parsing, filtering and manipulation operators.

## PGM specifications
File format description can be found at http://en.wikipedia.org/wiki/Netpbm_format
More information about MM (Mathematical Morphology) can be found at
http://en.wikipedia.org/wiki/Mathematical_morphology

## Parsing
- from_file
- to_file

## Manipulation
- max_depth
- min_depth
- compatible_format
- clone_format
- empty
- are_equal
- is_greater_than
- is_lesser_than
- supreme
- infimum
- addition
- subtraction
- gradient
- normalize
- flatzone (with high-speed queue)
- binarize
- binarize_within
- binarize_equal
- inverse

## Filters
- erosion
- dilation
- opening
- closing
- opening_closing
- closing_opening

## Documentation and examples
I am really sorry for the lack of documentation, if you feel like using
this library just take look at the exercises directory, it should be
enlightening.

