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

#include "queue.h"

Queue *Queue_new(void)
{
  Queue *queue;

  queue = (Queue*)malloc(sizeof(Queue));
  queue->top = NULL;
  queue->last = NULL;

  return queue;
}

void Queue_push(Queue *queue, unsigned int height, unsigned int width)
{
  Item *item;

  item = (Item*)malloc(sizeof(Item));
  item->height = height;
  item->width = width;
  item->previous = NULL;

  if (!queue->top)
  {
    queue->top = item;
    queue->last = item;
    return;
  }

  queue->last->previous = item;
  queue->last = item;
}

Item *Queue_pop(Queue *queue)
{
  Item *item;

  item = queue->top;
  if (item)
  {
    queue->top = item->previous;
    //if (!queue->top) { queue->last = NULL; } //Not necessary, when the next item goes in it will be rewriten.
  }

  return item;
}

