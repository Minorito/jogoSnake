#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "Fila.h"
#define QUEUESIZE 1600
#define COBRASIZE 2
#define FOOD 10
void arrowHere(int realPosition, int arrowPosition);
void gotoxy(int x, int y);
void imprime_cobra(queue cobra);
void inicializa_cobra(queue *cobra);
void inicializa_cobra(queue *cobra);
void inicializa_comida(comida *comida);
void imprime_comida(comida comida);
int verifica_jogo(queue *cobra);
int verifica_comida(comida Comida);
void cobra_come(queue *cobra, comida *Comida, corpo elem);
void tela_fim(int num);
void anda_cobra(queue *cobra, char dir);
void menu();


int _comida = 0;
long _speed = 40;
int _dirD = 1, _dirA = 0, _dirW = 0, _dirS = 0, _x = 0, _jogar = 1;

void arrowHere(int realPosition, int arrowPosition)
{
   if (realPosition == arrowPosition)
   {
      printf(">>");
   }
   else
   {
      printf("  ");
   }
}

void gotoxy(int x, int y)
{
   COORD c;
   c.X = x;
   c.Y = y;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void imprime_cobra(queue cobra)
{
   int i = cobra.start;
   while (i != cobra.end)
   {
      i++;
      if (i > QUEUESIZE - 1)
         i = 0;
      gotoxy(cobra.items[i].x, cobra.items[i].y);
      if (cobra.items[i].cabeca)
         printf(" ");
      else
         printf("%c", 254);
   }
}

void inicializa_cobra(queue *cobra)
{
   corpo elems[COBRASIZE];
   int i;

   for (i = 0; i < COBRASIZE; i++)
   {
      gotoxy(i, 0);

      if (i == COBRASIZE - 1)
         elems[i].cabeca = 1;
      else
         elems[i].cabeca = 0;

      elems[i].x = i;
      elems[i].y = 0;

      enqueue(cobra, elems[i]);
   }
   imprime_cobra(*cobra);
}

void inicializa_comida(comida *comida)
{
   int i;
   for (i = 0; i < FOOD; i++)
   {
      comida->items[i].x = rand() % 80;
      comida->items[i].y = rand() % 24;
      comida->items[i].cabeca = 1;
   }
}

void imprime_comida(comida comida)
{
   int i;

   for (i = 0; i < FOOD; i++)
   {
      gotoxy(comida.items[i].x, comida.items[i].y);
      printf("%c", 1);
   }
}

int verifica_jogo(queue *cobra)
{
   int i, retorno = 0;

   for (i = cobra->start + 1; i < cobra->end; i++)
   {
      if ((cobra->items[i].x == cobra->items[cobra->end].x) && (cobra->items[i].y == cobra->items[cobra->end].y))
      {
         retorno = 1;
      }
   }
   return retorno;
}

int verifica_comida(comida Comida)
{
   int i, retorno = 1;

   for (i = 0; i < FOOD; i++)
      if (Comida.items[i].cabeca == 1)
         retorno = 0;
   return retorno;
}

void cobra_come(queue *cobra, comida *Comida, corpo elem)
{
   int i;
   for (i = 0; i < FOOD; i++)
   {

      if ((cobra->items[cobra->end].x == Comida->items[i].x) &&
          (cobra->items[cobra->end].y == Comida->items[i].y) && (Comida->items[i].cabeca))
      {
         cobra->items[cobra->end].cabeca = 0;
         enqueue(cobra, elem);
         Comida->items[i].cabeca = 0;
         _comida++;
      }
   }
   if ((_comida > FOOD / 5) && (_comida < FOOD / 2))
      _speed = 30;
   else if ((_comida >= FOOD / 2) && (_comida < FOOD - 1))
      _speed = 20;
   else if ((_comida == FOOD - 1))
      _speed = 10;
}

void tela_fim(int num)
{
   char volta=0;

   if (_x > 79)
      _x = 0;

   system("cls");
   gotoxy(++_x, 10);

   if (num == 1)
   {
      system("color 60");
      printf("FIM DE JOGO: VOCE GANHOU");
   }
   else if (num == 2)
   {
      system("color C0");
      printf("FIM DE JOGO VOCE PERDEU");
   }
   printf("\n\n\n\nPressione a tecla Enter para retornar ao menu...");
   volta = getch();
   fflush(stdin);
   if(volta == 13)
      menu();
}

void anda_cobra(queue *cobra, char dir)
{
   corpo elem, elem2, rastro;

   if (dir == 'd')
   {

      _dirS = 1;
      _dirW = 0;
      _dirS = 0;
   }
   else if (dir == 'a')
   {

      _dirA = 1;
      _dirW = 0;
      _dirS = 0;
   }
   else if (dir == 'w')
   {

      _dirW = 1;
      _dirD = 0;
      _dirA = 0;
   }
   else if (dir == 's')
   {

      _dirS = 1;
      _dirD = 0;
      _dirA = 0;
   }

   if ((dir == 'a') && (_dirD == 1))
      dir = 'd';
   else if ((dir == 'd') && (_dirA == 1))
      dir = 'a';
   else if ((dir == 's') && (_dirW == 1))
      dir = 'a';
   else if ((dir == 'w') && (_dirS == 1))
      dir = 's';

   int andou = 0;

   elem.cabeca = 1;

   cobra->items[cobra->end].cabeca = 0;

   if (dir == 'd')
   {
      andou = 1;
      elem.x = cobra->items[cobra->end].x + 1;
      elem2.x = elem.x + 1;
      elem.y = cobra->items[cobra->end].y;
      elem2.y = elem.y;
      if (elem.x > 79)
         elem.x = 0;
   }
   else if (dir == 'a')
   {
      andou = 1;

      elem.x = cobra->items[cobra->end].x - 1;
      elem2.x = elem.x - 1;
      elem.y = cobra->items[cobra->end].y;
      elem2.y = elem.y;
      if (elem.x < 0)
         elem.x = 79;
   }
   else if (dir == 'w')
   {
      andou = 1;

      elem.x = cobra->items[cobra->end].x;
      elem2.x = elem.x;
      elem.y = cobra->items[cobra->end].y - 1;
      elem2.y = elem.y - 1;
      if (elem.y < 0)
         elem.y = 23;
   }
   else if (dir == 's')
   {
      andou = 1;

      elem.x = cobra->items[cobra->end].x;
      elem2.x = elem.x;
      elem.y = cobra->items[cobra->end].y + 1;
      elem2.y = elem.y + 1;
      if (elem.y > 23)
         elem.y = 0;
   }

   if (andou)
   {
      enqueue(cobra, elem);
      rastro = dequeue(cobra);
      gotoxy(rastro.x, rastro.y);
      printf(" ");
      cobra_come(cobra, &Comida, elem2);
      imprime_cobra(*cobra);
   }
}

void menu()
{
   int position = 1;
   int keyPressed = 0;
   char c;
   long i;

   system("color A0");

   while (keyPressed != 13)
   {

      system("cls");
      printf("\n    _(_)(_)(_)(_)_      (_) _       (_)           _(_)_           (_)       _ (_)      (_)(_)(_)(_)(_)   \n");
      printf("   (_)          (_)     (_)(_)_     (_)         _(_) (_)_         (_)    _ (_)         (_)               \n");
      printf("   (_)_  _  _  _        (_)  (_)_   (_)       _(_)     (_)_       (_) _ (_)            (_) _  _          \n");
      printf("     (_)(_)(_)(_)_      (_)    (_)_ (_)      (_) _  _  _ (_)      (_)(_) _             (_)(_)(_)         \n");
      printf("    _           (_)     (_)      (_)(_)      (_)(_)(_)(_)(_)      (_)   (_) _          (_)               \n");
      printf("   (_)_  _  _  _(_)     (_)         (_)      (_)         (_)      (_)      (_) _       (_) _  _  _  _    \n");
      printf("     (_)(_)(_)(_)       (_)         (_)      (_)         (_)      (_)         (_)      (_)(_)(_)(_)(_)   \n\n");
      printf("                                                                   Daniel Minoru Amaro Takabaishi  &  Samuel Piasecki\n\n");
      arrowHere(1, position);
      printf("INICIAR\n\n");
      arrowHere(2, position);
      printf("SAIR DO JOGO\n");
      keyPressed = getch();
      fflush(stdin);

      if (keyPressed == 80 && position != 2)
      {
         position++;
      }
      else if (keyPressed == 72 && position != 1)
      {
         position--;
      }
      else
      {
         position = position;
      }
   }
   if (position == 1)
   {
      system("cls");
      inicializa_comida(&Comida);
      imprime_comida(Comida);

      inicializa_queue(&cobra);
      inicializa_cobra(&cobra);

      do
      {
         if (kbhit())
            c = getch();

         anda_cobra(&cobra, c);

         if (verifica_jogo(&cobra) == 1)
         {
            tela_fim(2);
         }
         else if (verifica_comida(Comida) == 1)
         {
            tela_fim(1);
         }

         Sleep(100);

      } while (1);
   }
   else if (position == 2)
   {
      system("cls");
      system("PAUSE");
      exit(0);
   }
}

int main()
{
   system("Music.mp3");
   srand(time(NULL));
   menu();
}
