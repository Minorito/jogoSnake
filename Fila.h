#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#define QUEUESIZE 1600
#define COBRASIZE 2
#define FOOD 20

typedef struct{
       //coordenadas do corpo;
       int x, y; 
       // 0 - se � corpo  1 - se � cabe�a
       int cabeca; 
}corpo;

typedef struct {
       int start, end;
       corpo items[QUEUESIZE];
}queue;


typedef struct {
       
      corpo items[FOOD];
}comida;

//Declarando a estutura cobra (Global)
queue cobra;

comida Comida;

//____________________________________FIM___________________________________





//INCIALIZA A FILA
void inicializa_queue(queue *fila){
     fila->start = QUEUESIZE - 1;
     fila->end = QUEUESIZE - 1;
}


//VERIFICA SE FILA VAZIA
int empty(queue fila) {
    return fila.start == fila.end;
}

//RETIRA NA FILA
 corpo dequeue(queue *fila){
    if (empty(*fila)){
       printf("Fila vazia");
    } else {
       if (fila->start == QUEUESIZE - 1)
          fila->start = 0;
       else
          fila->start++;
       return fila->items[fila->start];
    }
}


//INSERE NA FILA
void enqueue(queue *fila, corpo elem){
    
    int endtemp = fila->end;

    if (fila->end == QUEUESIZE - 1)
       fila->end = 0;
    else
       fila->end++;

    if (fila->start == fila->end){
       printf("Fila cheia");
       fila->end = endtemp;
    } else
       fila->items[fila->end] = elem;
}

//____________________________FIM_________________________________

