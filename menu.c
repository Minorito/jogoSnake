#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#define MAX 2
#define MIN 1

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

void menu()
{
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

        if (keyPressed == 80 && position != MAX)
        {
            position++;
        }
        else if (keyPressed == 72 && position != MIN)
        {
            position--;
        }
        else
        {
            position = position;
        }
    }
    if(position == 2){
        system("cls");
        exit(0);
    }
}

int main()
{

    menu();
    return 0;
}