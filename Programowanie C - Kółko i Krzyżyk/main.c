#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

char board[3][3];
const char GRACZ = 'X';
const char KOMPUTER = 'O';

void resetBoard();
void printBoard();
int checkFreeSpaces();
void ruchGracza();
void ruchKomputera();
char sprawdzZwyciezce();
void printZwyciezca(char);

int main()
{
    char zwyciezca = ' ';
    char odpowiedz = ' ';

    do
    {
        zwyciezca = ' ';
        odpowiedz = ' ';
        resetBoard();

        while (zwyciezca == ' ' && checkFreeSpaces() != 0)
        {
            printBoard();

            ruchGracza();
            zwyciezca = sprawdzZwyciezce();
            if (zwyciezca != ' ' || checkFreeSpaces() == 0)
            {
                break;
            }

            ruchKomputera();
            zwyciezca = sprawdzZwyciezce();
            if (zwyciezca != ' ' || checkFreeSpaces() == 0)
            {
                break;
            }
        }

        printBoard();
        printZwyciezca(zwyciezca);

        printf("\nCzy chcesz zagrać ponownie? (T/N): ");
        scanf(" %c", &odpowiedz);
        odpowiedz = toupper(odpowiedz);
    } while (odpowiedz == 'T');

    printf("Dziękujemy za grę!");

    return 0;
}

void resetBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

void printBoard()
{
    printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

int checkFreeSpaces()
{
    int wolneMiejsca = 9;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != ' ')
            {
                wolneMiejsca--;
            }
        }
    }
    return wolneMiejsca;
}

void ruchGracza()
{
    int x;
    int y;

    do
    {
        printf("Podaj numer wiersza (1-3): ");
        scanf("%d", &x);
        x--;
        printf("Podaj numer kolumny (1-3): ");
        scanf("%d", &y);
        y--;

        if (board[x][y] != ' ')
        {
            printf("Nieprawidłowy ruch!\n");
        }
        else
        {
            board[x][y] = GRACZ;
            break;
        }
    } while (board[x][y] != ' ');
}

void ruchKomputera()
{
    srand(time(0));
    int x;
    int y;

    if (checkFreeSpaces() > 0)
    {
        do
        {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');

        board[x][y] = KOMPUTER;
    }
    else
    {
        printZwyciezca(' ');
    }
}

char sprawdzZwyciezce()
{
    // Sprawdź wiersze
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
        {
            return board[i][0];
        }
    }

    // Sprawdź kolumny
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
        {
            return board[0][i];
        }
    }

    // Sprawdź przekątne
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
    {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
    {
        return board[0][2];
    }
    return ' ';
}

void printZwyciezca(char zwyciezca)
{
    if (zwyciezca == GRACZ)
    {
        printf("WYGRAŁEŚ!");
    }
    else if (zwyciezca == KOMPUTER)
    {
        printf("PRZEGRAŁEŚ!");
    }
    else
    {
        printf("REMIS!");
    }
}

