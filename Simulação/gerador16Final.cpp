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

void conversor_float_binario(float numero, int out[16]);



int main()
{

    float numeroA, numeroB, resultado;
    int out1[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int out2[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int result[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int i = 0;
    int qtd = 0;

    FILE *saida;

    saida = fopen("estimulos.txt", "w");

    while (qtd != 1000)
    {
        numeroA = rand();
        numeroA = numeroA/1000;
        conversor_float_binario(numeroA, out1);
        if(out1[0] == 1)
            numeroA = numeroA * -1;

        numeroB = rand();
        numeroB = numeroB/1000;
        conversor_float_binario(numeroB, out2);
        if(out2[0] == 1)
            numeroB = numeroB * -1;

        resultado = numeroA + numeroB;
        printf("\n%f", resultado);
        resultado = rand();
        resultado = resultado/1000;
        conversor_float_binario(resultado, result);

        for(i = 0; i < 16; i++)
            fprintf(saida, "%d", out1[i]);

        for(i = 0; i < 16; i++)
            fprintf(saida, "%d", out2[i]);

        for(i = 0; i < 16; i++)
            fprintf(saida, "%d", result[i]);

        qtd++;
        fprintf(saida, "\n");
    }


    fclose(saida);


    return 0;
}

void conversor_float_binario(float numero, int out[16])
{

    double parteInteira, fracao;
    char binInt[16], binFrac[16];
    int binParteInteira[16], binParteFrac[16];
    int i = 0, j = 0;
    double conversao = 0;
    int temp = 0;

    char expoente_char[5];
    int expoente[5];
    int sinal;
    int e = 0;
    int qtd_int = 0, qtd_frac = 0; //Gambiarra


    fracao = modf(numero, &parteInteira);

    itoa(parteInteira,binInt,2);
    qtd_int = parserBin(binInt, binParteInteira, 16);

    if(fracao != 0)
    {
        i = 0;
        conversao = fracao;
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

    qtd_frac = parser(binFrac, binParteFrac, 16);

    if(qtd_int != 1)
        e = qtd_int-1;
    else e = qtd_int;

    e = e + 15;

    itoa(e, expoente_char, 2);
    parser(expoente_char, expoente, 5);

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

int parser(char *v, int *e, int tam)
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

