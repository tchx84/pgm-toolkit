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

#ifndef QUEUE_H
#define QUEUE_H
#include <stdlib.h>

struct Item_struct
{
  unsigned int height;
  unsigned int width;
  struct Item_struct *previous;
} typedef Item;

typedef struct
{
  Item *top;
  Item *last;
} Queue;

Queue *Queue_new(void);
void Queue_push(Queue *queue, unsigned int height, unsigned int width);
Item *Queue_pop(Queue *queue);
#endif

