
#include<stdio.h>
#include<iostream>
#include <stdlib.h>
#include<math.h>
#include <vector>

using namespace std;

int parser(char *v, int *e, int tam);

int parserBin(char *v, int *e, int tam);

void parserExp(char *v, int *e, int tam);

void parserExpNegativo(char *v, int *e, int tam);

void conversor_float_binario(float numero, int out[16]);

void imprimir(int *v, int tam)
{
    int i = 0;

    for(i = 0; i < tam; i++)
        printf("%d", v[i]);

    printf("\n");

}



int main()
{

    float numeroA, numeroB, resultado;
    int out1[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int out2[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int result[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int sinal_result = 0;
    int i = 0;

    int interacao = 0;
    FILE *saida;

    saida = fopen("estimulos.txt", "w");

    while(interacao != 1) /*************VMUDA AQUI A QUANTIDADE DE VEZES**********/
    {
        cout << "Digite o numero A: " << endl;
        cin >> numeroA;

        conversor_float_binario(numeroA, out1);
        out1[0] = 0; /*************MUDAR O SINAL DE A**********/
        if(out1[0] == 1)
            numeroA = numeroA * -1;

        imprimir(out1, 16);

        cout << "Digite o numero B: " << endl;
        cin >> numeroB;

        conversor_float_binario(numeroB, out2);
        out2[0] = 0; /*************MUDAR O SINAL DE B**********/
        if(out2[0] == 1)
            numeroB = numeroB * -1;

        imprimir(out2, 16);

        resultado = numeroA + numeroB;
        if(resultado < 0)
        {
            resultado = resultado * -1;
            sinal_result = 1;
        }
        else sinal_result = 0;

        printf("\n%.3f\n", resultado);

        conversor_float_binario(resultado, result);
        result[0] = sinal_result;
        imprimir(result, 16);

        for(i = 0; i < 16; i++)
            fprintf(saida, "%d", out1[i]);

        for(i = 0; i < 16; i++)
            fprintf(saida, "%d", out2[i]);

        for(i = 0; i < 16; i++)
            fprintf(saida, "%d", result[i]);

        interacao++;
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

    cout << "" << parteInteira << " e " << fracao << endl;



    itoa(parteInteira,binInt,2);
    printf("O numero %.0f em binario e: %s\n",parteInteira, binInt);

    qtd_int = parserBin(binInt, binParteInteira, 15);
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

    e = qtd_int-1;
    e = e + 15;

    itoa(e, expoente_char, 2);
    if(e == 15)
        parserExp(expoente_char, expoente, 4);
    else if(e < 15)
        parserExpNegativo(expoente_char, expoente, 5);
    else
        parser(expoente_char, expoente, 5);

    printf("expoente: %d em binario e: %s\n", e, expoente_char);


    for(i = 0; i < 5; i++)
        printf("%d", expoente[i]);

    printf("\n");

    //out[0] = rand() % 2;

    out[0] = 0;
    j = 0;
    for(i = 1; i < 6; i++)
    {
        out[i] = expoente[j];
        j++;
    }

    j = 17 - qtd_int;

    while(i < (qtd_int + 5))
    {
        out[i] = binParteInteira[j];
        if(j <= 15)
            j++;
        i++;
    }

    if(qtd_frac == 1 && qtd_int == 0)
        j = 1;
    else
        j = 0;
    while(i < 16)
    {
        out[i] = binParteFrac[j];
        j++;
        i++;
    }
    printf("\n");
    //imprimir(out, 16);
}

int parserBin(char *v, int *e, int tam)
{
    int i = 0, j = 0;
    int temp, qtd = 0;
    int deslocamento;

    for(i = 0; v[i] != '\0'; i++)
        qtd++;


    if(qtd == 1 && v[0] == '0')
        qtd = 0;


    deslocamento = qtd;
    for(i = tam; i >= 0; i--)
    {
        temp = v[qtd-1];
        if(temp == 48)
            e[i] = 0;
        else if(temp == 49)
            e[i] = 1;
        else e[i] = 0;
        qtd--;
        if(qtd == 0)
            e[i] = 0;
    }


    printf("\n");
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
            e[i] = 0;
        else if(temp == 49)
            e[i] = 1;
        else e[i] = 0;
    }

    return qtd;
}

void parserExp(char *v, int *e, int tam)
{
    int i = 0, j = 0;
    int temp;


    for(i = tam; i >= 0; i--)
    {
        temp = v[i];
        if(temp == 48)
            e[j] = 0;
        else if(temp == 49)
            e[j] = 1;
        else e[j] = 0;
        j++;
    }

}

void parserExpNegativo(char *v, int *e, int tam)
{
    int i = 0, j = 0;
    int temp;
    char aux[5];

    aux[0] = '0';

    for(i = 1; i < 5; i++)
    {
        aux[i] = v[j];
        j++;
    }
    j = 0;
    for(i = 0; i < tam; i++)
    {
        temp = aux[i];
        if(temp == 48)
            e[j] = 0;
        else if(temp == 49)
            e[j] = 1;
        else e[j] = 0;
        j++;
    }
}

