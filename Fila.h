#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define QUEUESIZE 1600
#define COBRASIZE 2
#define FOOD 20

typedef struct
{
   int x, y;
   int cabeca;
} corpo;

typedef struct
{
   int start, end;
   corpo items[QUEUESIZE];
} queue;

typedef struct
{
   corpo items[FOOD];
} comida;

queue cobra;

comida Comida;

void inicializa_queue(queue *fila)
{
   fila->start = QUEUESIZE - 1;
   fila->end = QUEUESIZE - 1;
}

int empty(queue fila)
{
   return fila.start == fila.end;
}

corpo remove(queue *fila)
{
   if (empty(*fila))
   {
      printf("Fila vazia");
   }
   else
   {
      if (fila->start == QUEUESIZE - 1)
         fila->start = 0;
      else
         fila->start++;
      return fila->items[fila->start];
   }
}

void insere(queue *fila, corpo elem)
{

   int endtemp = fila->end;

   if (fila->end == QUEUESIZE - 1)
      fila->end = 0;
   else
      fila->end++;

   if (fila->start == fila->end)
   {
      printf("Fila cheia");
      fila->end = endtemp;
   }
   else
      fila->items[fila->end] = elem;
}
