
#include<stdio.h>
#include<iostream>
#include <stdlib.h>
#include<math.h>
#include <vector>

using namespace std;

int parser(char *v, int *e, int tam);

int parserBin(char *v, int *e, int tam);

void imprimir(int *v, int tam)
{
    int i = 0;

    for(i = 0; i < tam; i++)
        printf("%d", v[i]);

    printf("\n");

}



int main()
{

    float numero;
    double parteInteira, fracao;
    char binInt[16], binFrac[16];
    int binParteInteira[16], binParteFrac[16];
    int i = 0, j = 0;
    double conversao = 0;
    int temp = 0;

    int out[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    char expoente_char[5];
    int expoente[5];
    int sinal;
    int e = 0;
    int qtd_int = 0, qtd_frac = 0; //Gambiarra

    FILE *saida;

    saida = fopen("estimulos.txt", "w");


    cout << "Digite um numero: " << endl;
    cin >> numero;

    fracao = modf(numero, &parteInteira);

    cout << "" << parteInteira << " e " << fracao << endl;



    itoa(parteInteira,binInt,2);
    printf("O numero %.0f em binario e: %s\n",parteInteira, binInt);

    qtd_int = parserBin(binInt, binParteInteira, 16);
    imprimir(binParteInteira, 16);


    if(fracao != 0)
    {
        i = 0;
        conversao = fracao;
        printf("Conversao: %f\n", conversao);
        do
        {
            temp = conversao * 2;
            conversao = conversao * 2;

            if(temp == 1)
            {
                binFrac[i] = '1';
                conversao = conversao - 1;
            }
            else
            {
                binFrac[i] = '0';
            }

            i++;
        }
        while(conversao != 0);
    }
    binFrac[i] = '\0';
    printf("A fracao %f em binario e: %s\n", fracao, binFrac);

    qtd_frac = parser(binFrac, binParteFrac, 16);
    imprimir(binParteFrac, 16);

    if(qtd_int != 1)
        e = qtd_int-1;
    else e = qtd_int;

    e = e + 15;

    itoa(e, expoente_char, 2);
    printf("expoente: %d em binario e: %s\n", e, expoente_char);
    parser(expoente_char, expoente, 5);

    for(i = 0; i < 5; i++)
        printf("%d", expoente[i]);

    printf("\n");

    out[0] = rand() % 2;

    j = 0;
    for(i = 1; i < 6; i++)
    {
        out[i] = expoente[j];
        j++;
    }

    j = 16 - qtd_int;
    for(i = 6; i < qtd_int + 6; i++)
    {
        out[i] = binParteInteira[j];
        j++;
    }

    j = 0;

    for(i = qtd_int + 6; i < 16; i++)
    {
        out[i] = binParteFrac[j];
        j++;
    }

    imprimir(out, 16);


    for(i = 0; i < 16; i++)
        fprintf(saida, "%d", out[i]);

    fclose(saida);


    return 0;
}

int parserBin(char *v, int *e, int tam)
{
    int i = 0, j = 0;
    int temp, qtd = 0;
    int deslocamento;

    for(i = 0; v[i] != '\0'; i++)
        qtd++;

    deslocamento = qtd;

    for(i = tam; i >= 0; i--)
    {
        temp = v[qtd];
        if(temp == 48)
            e[i] = 0;
        else if(temp == 49)
            e[i] = 1;
        else e[i] = 0;
        qtd--;
    }


    return deslocamento;
}

parser(char *v, int *e, int tam)
{
    int i = 0, j = 0;
    int temp;
    int qtd = 0;

    for(i = 0; v[i] != '\0'; i++)
        qtd++;

    for(i = 0; i < tam; i++)
    {
        temp = v[i];
        if(temp == 48)
            e[j] = 0;
        else if(temp == 49)
            e[j] = 1;
        else e[j] = 0;
        j++;
    }

    return qtd;
}

