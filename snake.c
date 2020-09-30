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
#define FOOD 20
#define TAB 6

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

//Posiciona o cursor na tela, diacordo com as cordenadas X,Y
void gotoxy(int x, int y)
{

   //Esse tipo e varï¿½vel
   COORD c;
   //X e Y sï¿½o "atributos" do Tipo COORD
   c.X = x;
   c.Y = y;
   //Posiciona o curso diacordo com c.x e c.y
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//IMPREME A ESTRUTURA passada por parametro  (ESSA FUNï¿½ï¿½O E CHAMADA PELA FUNï¿½ï¿½O ANDA_COBRA)
void imprime_cobra (queue cobra)
{
   //Atribuia a i o valor do inicio da estrutura
   int i = cobra.start;
   //Enquando i for diferente do fim (Com isso pecorremos toda a estrutura)
   while (i != cobra.end)
   {

      //Incrementa (Jï¿½ que no inicio nï¿½o temos dados)
      i++;

      //Se i maior que tamanho da fila - 1
      if (i > QUEUESIZE - 1)
         /*Entï¿½o i serï¿½ 0 (Nesse caso se o i chegar no fim e ainda nï¿½o for igual 
             ao end ï¿½ porque temos que ler os dados que estï¿½o no incio da fila, jï¿½
             que a fila ï¿½ ciclica
            */
         i = 0;

      //Passa as cordenadas do elemento para a funï¿½ï¿½o que posiciona o cursor para a impressï¿½o
      gotoxy(cobra.items[i].x, cobra.items[i].y);
      //se a variavel cabelï¿½a do itens for 1
      if (cobra.items[i].cabeca)
         //impima a carinha, pela tabela ASCII '1'
         printf(" ");
      else
         //Se nï¿½o, imprima o quadrado, pela TABELA ASCII 256
         printf("%c", 254);
   }
}

//INICIALIZA A COBRA (coloca a cabeï¿½a e o corpo)
void inicializa_cobra (queue *cobra)
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

      // Coloa o curso no canto esquerdo superior
      elems[i].x = i;
      //Y = 0 , logo elas estï¿½ "deitada"
      elems[i].y = 0;

      //Empilhando o elems na pilha;
      enqueue(cobra, elems[i]);
   }
   //Imprimindo a cobra
   imprime_cobra(*cobra);
}

//Essa funï¿½ï¿½o coloca randomicamente as cordenadas das comida
void inicializa_comida(comida *comida)
{

   int i;

   for (i = 0; i < FOOD; i++)
   {

      //recebe valor de 0 a 79
      comida->items[i].x = rand() % 80;
      //recebe valor de 0 a 23;
      comida->items[i].y = rand() % 24;
      //atribui o valor 1(comida = true)
      comida->items[i].cabeca = 1;
   }
}

//Imprime as comidas na tela
void imprime_comida(comida comida)
{

   int i;

   //Pecorre toda a estrutura
   for (i = 0; i < FOOD; i++)
   {

      //pocisiona o cursor de acordo com os numero sorteado
      gotoxy(comida.items[i].x, comida.items[i].y);

      //imprime a comida
      printf("%c", 1);
   }
}

//verifica se a cabeï¿½a da cobra tocou no corpo
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

//verifica se acabou a comida, logo o jogador venceu
int verifica_comida(comida Comida)
{

   int i, retorno = 1;

   for (i = 0; i < FOOD; i++)
      if (Comida.items[i].cabeca == 1)
         retorno = 0;

   return retorno;
}

//Verifica se a posiï¿½ï¿½o que a cobra estï¿½ ï¿½ de uma comida, se sim a cobra cresce
void cobra_come(queue *cobra, comida *Comida, corpo elem)
{

   int i;
   //De i=0 atï¿½ quantidade de comidas
   for (i = 0; i < FOOD; i++)
   {

      //Se a cordenada x e y ï¿½ iguala a cordenada de alguma comida
      if ((cobra->items[cobra->end].x == Comida->items[i].x) &&
          (cobra->items[cobra->end].y == Comida->items[i].y) && (Comida->items[i].cabeca))
      {

         //apaga a cabeï¿½a, pois o elem jï¿½ veio incrementado
         cobra->items[cobra->end].cabeca = 0;
         //colocar o elem cabeï¿½a na pilha
         enqueue(cobra, elem);
         //atribui 0(false) ao alimento que jï¿½ foi comido
         Comida->items[i].cabeca = 0;
         //incrementa a quantidade de alimento comido
         _comida++;
      }
   }
   //se a quantidade de alimento comido estï¿½ ente 1/5 e 1/2, velocidade igual a 30
   if ((_comida > FOOD / 5) && (_comida < FOOD / 2))
      _speed = 30;
   //Se maior que 1/2  e menor que quantidade da comida -1, velocidade iguala 20
   else if ((_comida >= FOOD / 2) && (_comida < FOOD - 1))
      _speed = 20;
   //se temos apenas uma comida na tela, velocidade de 10;
   else if ((_comida == FOOD - 1))
      _speed = 10;
}

//funï¿½ï¿½o para a tela fiinal do jogo
void tela_fim(int num)
{

   //se a msg estiver no canto, inicia novamente
   if (_x > 79)
      _x = 0;

   //apaga tela para escrever em outra cord
   system("cls");

   //seta o curso (incrementando o x)
   gotoxy(++_x, 10);

   //se o parametro num = 1 venceu
   if (num == 1)
   {
      system("color 60");
      printf("FIM DE JOGO: VOCE GANHOU");

      //se igual a 2 perdeu
   }
   else if (num == 2)
   {
      system("color C0");
      printf("FIM DE JOGO VOCE PERDEU");
   }

   //delay
   Sleep(300);
   menu();
   //recusividade
   //tela_fim(num);
}

//FUNï¿½ï¿½O PARA A COBRA ANDAR, recebe a estrutura e a direï¿½ï¿½o (a varaiï¿½vel c na main)
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

   //Variï¿½vel do tipo interio, mas que simula uma boolean (1=verdade, 0=falso);
   int andou = 0;

   //Coloca o valor 1 (verdadeiro), na variavel cabeï¿½a da estrutura elem (tipo CORPO)
   elem.cabeca = 1;

   //insere no final da estrutura na variavel cabeï¿½a o valor 0 (falso)
   cobra->items[cobra->end].cabeca = 0;

   //Essa sequï¿½ncia de ifs usa o parameto dir (variï¿½vel c na main)

   //SE DIR IGUALA A l
   if (dir == 'd')
   {

      //andou igual a 1(verdade);
      andou = 1;

      //Atribui o valor de x na estutura elem (tipo CORPO) INCEMENTADO, logo ele vai para a direira
      elem.x = cobra->items[cobra->end].x + 1;
      elem2.x = elem.x + 1;

      //Atribui o valor de y na estrutura elem (tipo CORPO), logo ele vai permanecer com o mesmo y
      elem.y = cobra->items[cobra->end].y;

      elem2.y = elem.y;

      //Se elem.x (que acabamos que atribuir) for maior que 79 (limite a direita da tela)
      if (elem.x > 79)

         //Entï¿½o ele serï¿½ iguala a 0 (do outro lado da tela)
         elem.x = 0;

      //SE DIR IGUAL A j
   }
   else if (dir == 'a')
   {

      //andou igual a 1(verdade);
      andou = 1;

      //Atribui o valor de x na estutura elem (tipo CORPO) DECEMENTADO, logo ele vai para a esquerda
      elem.x = cobra->items[cobra->end].x - 1;

      // essa variï¿½vel ï¿½ incrementada ou decrementada durante esse trecho, pois ï¿½ justamente a proxima posiï¿½ï¿½o que a cobra deve estar se comer
      elem2.x = elem.x - 1;
      //Atribui o valor de y na estrutura elem (tipo CORPO), logo ele vai permanecer com o mesmo y

      elem.y = cobra->items[cobra->end].y;

      elem2.y = elem.y;
      //Se elem.x for menor que 0 (limite a esquerda da tela)
      if (elem.x < 0)

         //Ele serï¿½ iguala a 79 (do outro lado da tela)
         elem.x = 79;

      //SE DIR IGUALA A i
   }
   else if (dir == 'w')
   {

      //andou igual a 1(verdade);
      andou = 1;

      //Atribui o valor de x na estrutura elem (tipo CORPO), logo ele vai permanecer com o mesmo x
      elem.x = cobra->items[cobra->end].x;

      elem2.x = elem.x;
      //Atribui o valor de y na estrutura elem (tipo CORPO) DECREMENTADO, logo ele vai subir
      elem.y = cobra->items[cobra->end].y - 1;

      elem2.y = elem.y - 1;
      //Se elem.y menor que 0 (limite superior da tela)
      if (elem.y < 0)

         //ele serï¿½ igual a  23 (outro lado da tela)
         elem.y = 23;
   }
   else if (dir == 's')
   {

      //andou igual a 1(verdade);
      andou = 1;

      //Atribui o valor de x na estrutura elem (tipo CORPO), logo ele vai permanecer com o mesmo x
      elem.x = cobra->items[cobra->end].x;
      elem2.x = elem.x;
      //Atribui o valor de y na estrutura elem (tipo CORPO) DECREMENTADO, logo ele vai descer
      elem.y = cobra->items[cobra->end].y + 1;
      elem2.y = elem.y + 1;
      //Se elem.y maior que 23 (limite inferior da tela)
      if (elem.y > 23)

         //Ele serï¿½ iguala a 0 (Outro lado da tela)
         elem.y = 0;
   }

   //Observe que se foi presionada uma tecla vï¿½lida(j,i,k,l) andou ï¿½ 1(verdade) senï¿½o ele ï¿½ 0(falso)
   if (andou)
   {

      //Inserindo na fila o elem
      enqueue(cobra, elem);

      //Atribuindo na variï¿½vel rasto o que ï¿½ retirado da fila
      rastro = dequeue(cobra);

      //Posiciona o curso do mouse na rasto (ultimo elemento da cobra- o rabo -)
      gotoxy(rastro.x, rastro.y);

      //Apaga o rasto remanecente na tela
      printf(" ");

      //passando elem2 e nï¿½o elem, caso a cobra a cabeï¿½a tem que estï¿½ na proxima cord de acordo a direï¿½ï¿½o.
      cobra_come(cobra, &Comida, elem2);

      //Imprimindo cobra
      imprime_cobra(*cobra);
   }
}

void menu()
{
   system("color A0");
   system("cls");
   int position = 1;
   int keyPressed = 0;

   while (keyPressed != 13)
   {
      system("cls");
      arrowHere(1, position);
      printf("INICIAR\n");
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

      //Variï¿½vel do tipo char receberï¿½ a direï¿½ï¿½o da funï¿½ï¿½o getchar();
      char c;
      //Essa variï¿½vel ï¿½ do tipo long para suportar o nï¿½mero "10.000.000"
      long i;

      //Inicializa a fila (Ou seja a coloca em situaï¿½ï¿½o vazia)
      inicializa_queue(&cobra);
      //Insere os elementos da cobra (corpo e cabeï¿½a) na fila
      inicializa_cobra(&cobra);

      do
      {

         //kbhit ï¿½ uma funï¿½ï¿½o da biblioteca conio.h, retorna nï¿½o 0 se foi pressionada uma tecla, e 0 se nï¿½o
         if (kbhit()) // Alocandi um caracter em c
            c = getch();

         // Faz a fila (cobra) andar de acordo com a direï¿½ï¿½o(c)
         anda_cobra(&cobra, c);

         //Imprementado por Luis Gustavo

         if (verifica_jogo(&cobra) == 1)
         {
            tela_fim(2);
         }
         else if (verifica_comida(Comida) == 1)
         {
            tela_fim(1);
         }

         //Essa estrutura de repetiï¿½ï¿½o serve para dar um delay a cada interaï¿½ï¿½o
         Sleep(100);

         //Essas instruï¿½ï¿½es se repetiram atï¿½ que c seja igual a "27"
      } while (1);
   }
   else if(position == 2){
      system("cls");
      exit(0);
   }
}

int main()
{
   //system("Music.mp3");
   //Funcï¿½o da biblioteca <time.h> permite a implataï¿½ï¿½o do ramdom usado na inicializa_comida
   srand(time(NULL));

   menu();
}