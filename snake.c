#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "Fila.h"
#define QUEUESIZE 1600
#define COBRASIZE 2
#define FOOD 20


int _comida=0;
long _speed=40;
int _dirL=1, _dirJ=0, _dirI=0, _dirK=0,_x=0,_jogar=1;

//Posiciona o cursor na tela, diacordo com as cordenadas X,Y
void gotoxy(int x, int y) { 
   
   //Esse tipo e var�vel
   COORD c;

   //X e Y s�o "atributos" do Tipo COORD
   c.X = x;
   c.Y = y;
   
   //Posiciona o curso diacordo com c.x e c.y  
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


//IMPREME A ESTRUTURA passada por parametro  (ESSA FUN��O E CHAMADA PELA FUN��O ANDA_COBRA)
void imprime_cobra(struct queue cobra){
     
     //Atribuia a i o valor do inicio da estrutura
     int i = cobra.start;
     
     //Enquando i for diferente do fim (Com isso pecorremos toda a estrutura)
     while (i != cobra.end){
         
         //Incrementa (J� que no inicio n�o temos dados)  
         i++;
         
         //Se i maior que tamanho da fila - 1
         if (i > QUEUESIZE - 1)
            /*Ent�o i ser� 0 (Nesse caso se o i chegar no fim e ainda n�o for igual 
             ao end � porque temos que ler os dados que est�o no incio da fila, j�
             que a fila � ciclica
            */
            i = 0;
         
         //Passa as cordenadas do elemento para a fun��o que posiciona o cursor para a impress�o   
         gotoxy(cobra.items[i].x, cobra.items[i].y);
         //se a variavel cabel�a do itens for 1
         if (cobra.items[i].cabeca)
         //impima a carinha, pela tabela ASCII '1'
            printf("%c",1);
         else
         //Se n�o, imprima o quadrado, pela TABELA ASCII 256
            printf("%c",254);
     }
}



//INICIALIZA A COBRA (coloca a cabe�a e o corpo)
void inicializa_cobra(struct queue *cobra){
    
    struct corpo elems[COBRASIZE];
    int i;
    
    for (i = 0; i<COBRASIZE; i++){
       gotoxy(i, 0);
       
       if (i == COBRASIZE - 1)
          elems[i].cabeca = 1;
       else
          elems[i].cabeca = 0;
       
       
       // Coloa o curso no canto esquerdo superior 
       elems[i].x = i;
       //Y = 0 , logo elas est� "deitada"
       elems[i].y = 0;
       
       //Empilhando o elems na pilha;
       enqueue(cobra, elems[i]);       
    }
    //Imprimindo a cobra
    imprime_cobra(*cobra);
}



//Essa fun��o coloca randomicamente as cordenadas das comida
void inicializa_comida(struct comida *comida){
           
int i;

  for (i=0;i<FOOD;i++){
    
    
   //recebe valor de 0 a 79 
   comida->items[i].x=rand()%80;
   //recebe valor de 0 a 23;
   comida->items[i].y=rand()%24;
   //atribui o valor 1(comida = true)
   comida->items[i].cabeca=1;

 }
           
           
}


//Imprime as comidas na tela
void imprime_comida(struct comida comida){

int i;

   //Pecorre toda a estrutura
   for (i=0;i<FOOD;i++){
  
      //pocisiona o cursor de acordo com os numero sorteado 
      gotoxy(comida.items[i].x, comida.items[i].y);

      //imprime a comida
      printf("+");
   }


}



//verifica se a cabe�a da cobra tocou no corpo
int verifica_jogo(struct queue *cobra){

  int i,retorno=0;
    
  for(i=cobra->start+1;i<cobra->end;i++){

 
    if (  (cobra->items[i].x == cobra->items[cobra->end].x ) && (cobra->items[i].y == cobra->items[cobra->end].y) ){  
            
               retorno=1;       
       } 
    }
  
  
   return retorno; 
}



//verifica se acabou a comida, logo o jogador venceu
int verifica_comida(struct comida comida){
                  
int i,retorno=1;
 
  for (i=0; i<FOOD;i++)
    if(comida.items[i].cabeca == 1)
       retorno=0;
       
     return retorno;     
    
}


//Verifica se a posi��o que a cobra est� � de uma comida, se sim a cobra cresce
void cobra_come(struct queue *cobra, struct comida *comida, struct corpo elem){
     
        int i;
          //De i=0 at� quantidade de comidas
          for (i=0;i<FOOD;i++){
               
            //Se a cordenada x e y � iguala a cordenada de alguma comida 
              if( ( cobra->items[cobra->end].x == comida->items[i].x) && 
              ( cobra->items[cobra->end].y == comida->items[i].y) && (comida->items[i].cabeca)){
                       
                      //apaga a cabe�a, pois o elem j� veio incrementado
                      cobra->items[cobra->end].cabeca=0;
                      //colocar o elem cabe�a na pilha
                      enqueue(cobra,elem);  
                      //atribui 0(false) ao alimento que j� foi comido
                      comida->items[i].cabeca=0;
                      //incrementa a quantidade de alimento comido
                      _comida++;
              }
           }
        
        
        
       //se a quantidade de alimento comido est� ente 1/5 e 1/2, velocidade igual a 30 
       if (  (_comida > FOOD/5) && (_comida < FOOD/2) )
                    _speed=30;
        //Se maior que 1/2  e menor que quantidade da comida -1, velocidade iguala 20         
       else if (   (_comida >= FOOD/2) && (_comida < FOOD-1) )
                  _speed=20;
        //se temos apenas uma comida na tela, velocidade de 10;          
       else if ( (_comida == FOOD-1) )
                  _speed=10; 
        
    


}



//fun��o para a tela fiinal do jogo
void tela_fim(int num){
  
  //se a msg estiver no canto, inicia novamente   
  if(_x>79)
    _x=0; 
  
  //apaga tela para escrever em outra cord  
 system("cls");
 
 //seta o curso (incrementando o x)
 gotoxy(++_x,10);        
 
 
 //se o parametro num = 1 venceu
 if(num==1){      
       printf("FIM DE JOGO: VOCE GANHOU");    

//se igual a 2 perdeu
}else if(num==2){                      
        printf("FIM DE JOGO VOCE PERDEU");     
}   
 
 //delay
 _sleep(50); 

//recusividade
tela_fim(num);
 
}
//____________________________________Fim____________________________________



//FUN��O PARA A COBRA ANDAR, recebe a estrutura e a dire��o (a varai�vel c na main)
void anda_cobra(struct queue *cobra, char dir){
        

//IMPLEMENTADA POR LUIS GUSTAVO

// esse trecho do codigo permite que a cobra n�o volte de onde veio, se sobrepondo

 if(dir=='d') {
   
      _dirL=1;
      _dirI=0;
      _dirK=0;
      
 }
 else if (dir=='a') {
      
      _dirJ=1;
      _dirI=0;
      _dirK=0;
       
}
 else if(dir=='w') {
      
      _dirI=1;
      _dirL=0;
      _dirJ=0;
}     
 else if(dir=='s') {
      
      _dirK=1;
      _dirL=0;
      _dirJ=0;
}     
  
  if( (dir=='a') && (_dirL==1)  )
     dir='d';      
  else if ( (dir=='d') && (_dirJ==1) )
     dir='a';      
  else if((dir=='s') && (_dirI==1))
     dir='a';
  else if((dir=='w') && (_dirK==1))
       dir='s';
          
    
    
    
//___________________________Fim__________________________________
    
    
    
    
    
    
    
    
    
     /*Declara uma fila do tipo CORPO, as manipula��es de inser��o na fila
     ser�o feitas nessa estrutura e posteriormente inseridas na estrutura da COBRA
     passada por parametro     
     */
     struct corpo elem, elem2, rastro;
     
     //Vari�vel do tipo interio, mas que simula uma boolean (1=verdade, 0=falso);
     int andou = 0;

     //Coloca o valor 1 (verdadeiro), na variavel cabe�a da estrutura elem (tipo CORPO)
     elem.cabeca = 1;
     
     //insere no final da estrutura na variavel cabe�a o valor 0 (falso) 
     cobra->items[cobra->end].cabeca = 0;
     
     //Essa sequ�ncia de ifs usa o parameto dir (vari�vel c na main) 
     
    //SE DIR IGUALA A l
    if (dir == 'd'){
        
        //andou igual a 1(verdade);     
        andou = 1;
        
        //Atribui o valor de x na estutura elem (tipo CORPO) INCEMENTADO, logo ele vai para a direira
        elem.x = cobra->items[cobra->end].x + 1;
        elem2.x =elem.x+1;
        
        //Atribui o valor de y na estrutura elem (tipo CORPO), logo ele vai permanecer com o mesmo y
        elem.y = cobra->items[cobra->end].y;
        
        elem2.y=elem.y;
        
        
        //Se elem.x (que acabamos que atribuir) for maior que 79 (limite a direita da tela)
        if (elem.x > 79)
        
        //Ent�o ele ser� iguala a 0 (do outro lado da tela)
           elem.x = 0;
           
     
     //SE DIR IGUAL A j
     } else if (dir == 'a') {
        
        //andou igual a 1(verdade);     
        andou = 1;
        
        //Atribui o valor de x na estutura elem (tipo CORPO) DECEMENTADO, logo ele vai para a esquerda
        elem.x = cobra->items[cobra->end].x - 1;
        
        // essa vari�vel � incrementada ou decrementada durante esse trecho, pois � justamente a proxima posi��o que a cobra deve estar se comer
        elem2.x =elem.x-1;
        //Atribui o valor de y na estrutura elem (tipo CORPO), logo ele vai permanecer com o mesmo y 
        
        elem.y = cobra->items[cobra->end].y;
        
        elem2.y=elem.y;
        //Se elem.x for menor que 0 (limite a esquerda da tela)
        if (elem.x < 0)
        
           //Ele ser� iguala a 79 (do outro lado da tela) 
           elem.x = 79;
     
     //SE DIR IGUALA A i
     } else if (dir == 'w') {
         
         //andou igual a 1(verdade);     
        andou = 1;
        
         //Atribui o valor de x na estrutura elem (tipo CORPO), logo ele vai permanecer com o mesmo x
        elem.x = cobra->items[cobra->end].x;
        
        elem2.x =elem.x;
        //Atribui o valor de y na estrutura elem (tipo CORPO) DECREMENTADO, logo ele vai subir 
        elem.y = cobra->items[cobra->end].y - 1;
        
        elem2.y=elem.y-1;
        //Se elem.y menor que 0 (limite superior da tela)
        if (elem.y < 0)
        
          //ele ser� igual a  23 (outro lado da tela)
           elem.y = 23;
     
     } else if (dir == 's') {
        
        //andou igual a 1(verdade);     
        andou = 1;
        
        //Atribui o valor de x na estrutura elem (tipo CORPO), logo ele vai permanecer com o mesmo x 
        elem.x = cobra->items[cobra->end].x;
        elem2.x=elem.x;
        //Atribui o valor de y na estrutura elem (tipo CORPO) DECREMENTADO, logo ele vai descer
        elem.y = cobra->items[cobra->end].y + 1;
        elem2.y=elem.y+1;
        //Se elem.y maior que 23 (limite inferior da tela)
        if (elem.y > 23)
        
        //Ele ser� iguala a 0 (Outro lado da tela)
           elem.y = 0;
     }



//Observe que se foi presionada uma tecla v�lida(j,i,k,l) andou � 1(verdade) sen�o ele � 0(falso)
     if (andou){
        
        //Inserindo na fila o elem       
        enqueue(cobra, elem);
        
        //Atribuindo na vari�vel rasto o que � retirado da fila
        rastro = dequeue(cobra);
        
        //Posiciona o curso do mouse na rasto (ultimo elemento da cobra- o rabo -)
        gotoxy(rastro.x, rastro.y);
        
        //Apaga o rasto remanecente na tela
        printf(" ");
       
       //passando elem2 e n�o elem, caso a cobra a cabe�a tem que est� na proxima cord de acordo a dire��o. 
       cobra_come(cobra,&comida,elem2); 
   
        
        
        //Imprimindo cobra
        imprime_cobra(*cobra);
     }

}

int main(){
    
    
    //Func�o da biblioteca <time.h> permite a implata��o do ramdom usado na inicializa_comida
    srand(time(NULL));
    
     inicializa_comida(&comida);
     imprime_comida(comida);

    
    //Vari�vel do tipo char receber� a dire��o da fun��o getchar();
    char c;
    //Essa vari�vel � do tipo long para suportar o n�mero "10.000.000" 
    long i;
    
    //Inicializa a fila (Ou seja a coloca em situa��o vazia)
    inicializa_queue(&cobra);
    //Insere os elementos da cobra (corpo e cabe�a) na fila
    inicializa_cobra(&cobra);
    
    do {
        
       //kbhit � uma fun��o da biblioteca conio.h, retorna n�o 0 se foi pressionada uma tecla, e 0 se n�o
       if (kbhit()) // Alocandi um caracter em c 
          c = getch();
       
       // Faz a fila (cobra) andar de acordo com a dire��o(c)   
       anda_cobra(&cobra,c);      
      
     
      //Imprementado por Luis Gustavo
      
      if(verifica_jogo(&cobra)==1){
          tela_fim(2);
                    
      }else if(verifica_comida(comida)==1){
         tela_fim(1); 
              
      }
      
      //Essa estrutura de repeti��o serve para dar um delay a cada intera��o
      _sleep(100);
    
    //Essas instru��es se repetiram at� que c seja igual a "27"
    } while (1);
        
}
