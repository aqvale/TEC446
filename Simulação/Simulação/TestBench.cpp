
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <conio.h>
#include <string>


int Binario_para_decimal(int e[5])
{
    int dec=0,d=1;
    int i= 0;

    for(i = 4; i >= 0; i--)
    {
        dec = dec+e[i]*d;
        d = d*2;
    }

    printf("\n O numero em decimal e %d\n",dec);
    return dec;
}

/*
void Decimal_para_binario()
{
int a;
char b[8];

printf("Digite um numero em decimal:");
scanf("%d",&a);
itoa(a,b,2);
printf("O numero %d em binario e: %s",a,b);
getch();
}
*/

int soma(int a[11], int b[11], int resultado[16]);
void imprimir(int *v, int tam);
void shift(int v[11], int deslocamento);
void somaExpoente(int v[5], int normalizado);
void saida(int sinal, int expoente[5], int resultado[10], int out[16]);
void complemento(int v[11]);

int main()
{


    int in1[16] = {0,1,0,0,0,0,0,1,0,1,0,0,1,0,0,0}; //2.640625 - 0100000101001000
    int in2[16] = {1,1,0,0,0,0,0,1,0,1,0,0,1,0,0,0}; //2.640625 - 0100000101001000

    int out[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    int i = 0, j = 0, k = 0;

    //Variaveis e A
    int a[11] = {1,0,0,0,0,0,0,0,0,0,0};
    int expoente_binario_a[5];
    int expoente_a = 0;
    int sinal_a = 0;

    //Variaveis de B
    int b[11] = {1,0,0,0,0,0,0,0,0,0,0};
    int expoente_binario_b[5];
    int expoente_b = 0;
    int sinal_b = 0;

    int deslocamento = 0;
    int normalizar = 0;

    int result[11] = {0,0,0,0,0,0,0,0,0};
    int formato_saida[10] = {0,0,0,0,0,0,0,0};
    int expoente_result[5];
    int sinal_result = 0;

    //Verificar se é Infinito ou Zero
    int qtd1 = 0;
    int qtd0 = 0;


    sinal_a = in1[0];
    sinal_b = in2[0];

    /****CALCULO DO EXPOENTE A e B*********/
    for(j = 1; j <= 5; j++)
    {
        expoente_binario_a[i] = in1[j];
        i++;
    }
    expoente_a = Binario_para_decimal(expoente_binario_a);
    printf ("Expoente A: %d", expoente_a);

    i = 0;
    for(j = 1; j <= 5; j++)
    {
        expoente_binario_b[i] = in2[j];
        i++;
    }
    expoente_b = Binario_para_decimal(expoente_binario_b);
    printf ("Expoente B: %d\n", expoente_b);
    /****************************************/

    /****SEPARANDO OS DADOS DE ENTRADA PARA A E B*********/
    i = 1;
    for(j = 6; j <= 15; j++)
    {
        a[i] = in1[j];
        i++;
    }
    printf ("Dado a: ");
    imprimir(a, 11);

    i = 1;
    for(j = 6; j <= 15; j++)
    {
        b[i] = in2[j];
        i++;
    }
    printf ("Dado b: ");
    imprimir(b,11);
    /***************************************************/

    /****CALCULO DO EXPOENTE PARA DESLOCAMENTO*********/
    deslocamento = expoente_a - expoente_b;

    if(deslocamento > 0)
        shift(b, deslocamento);
    else if(deslocamento < 0)
        shift(a, deslocamento);
    /*************************************************/


    /****COMPLEMENTO, SOMA E NORMALIZAÇÃO*********/
    if(sinal_b == 1)
        complemento(b);

    printf("\nComplemento de B: ");
    imprimir(b, 11);
    normalizar = soma(a,b,result);
    printf("\nNoraliza: %d\n", normalizar);

    printf ("Resultado da soma: ");
    imprimir(result, 11);

    printf("\n");

    if(expoente_a >= expoente_b)
    {
        for(i = 0; i < 5; i++)
            expoente_result[i] = expoente_binario_a[i];
    }
    else
    {
        for(i = 0; i < 5; i++)
            expoente_result[i] = expoente_binario_b[i];
    }

    if(normalizar)
        somaExpoente(expoente_result, normalizar);


    j = 1;
    for(i = 0; i < 10; i++)
    {
        formato_saida[i] = result[j];
        j++;
    }

    if(sinal_a == sinal_b)
        sinal_result = sinal_a;
    else    sinal_result = 1;


    printf("\nExpoente Result: ");
    imprimir(expoente_result, 5);
    /*************************************************/

    /*************VERIFICAR INFINITO OU ZERO**********/
    for(i = 0; i < 10; i++)
    {
        if(formato_saida[i] == 0)
            qtd0++;
    }

    if(qtd0 == 10)
    {
        for(i = 0; i < 5; i++)
            if(expoente_result[i])
                qtd1++;

        if(qtd1 == 5)
            printf("Infinito");
        else printf("0");
    } /*************************************************/
    else
    {
    /****************SAIDA NORMALIZADA*****************/
    saida(sinal_result, expoente_result, formato_saida, out);

    printf("\nOut: ");
    imprimir(out, 16);
    }/*************************************************/





    return 0;
}

int soma (int a[11], int b[11], int result[16])
{
    int temp = 0;
    int i = 0, j = 0, k = 0;
    int over = 0;
    int soma[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

    for(i = 10; i >= 0; i--)
    {
        temp = (a[i] + b[i]) + over;

        if(temp == 2)
        {
            soma[i] = 0;
            over = 1;
        }
        else if (temp == 3)
        {
            soma[i] = 1;
            over = 1;
        }
        else if (temp == 1)
        {
            soma[i] = 1;
            over = 0;
        }
        else
        {
            soma[i] = 0;
            over = 0;
        }

        if(i == 0 && over == 1)
        {
            j = 1;
            for(k = 0; k < 12; k++)
            {
                result[j] = soma[k];
                j++;
            }
            result[i] = 1;
        }
    }

    if(over == 1)
        return 1;
    else return 0;
}

void shift(int v[11], int deslocamento)
{
    int i = 0, d = deslocamento, j = 0;

    int temp[11];

    for(i = 0; i < 11; i++)
        temp[i] = 0;

    for(i = deslocamento; i < 11; i ++)
    {
        temp[i] = v[j];
        j++;
    }

    for(i = 0; i < 11; i++)
        v[i] = temp[i];
}

void saida(int sinal, int expoente[5], int resultado[10], int out[16])
{
    int i = 0, j = 0;
    out[0] = sinal;

    for(i = 1; i < 6; i++)
    {
        out[i] = expoente[j];
        j++;
    }

    j = 0;
    for(i = 6; i < 16; i++)
    {
        out[i] = resultado[j];
        j++;
    }
}

void somaExpoente(int v[5], int normalizado)
{
    int temp = 0;
    int i = 4;
    int over = 0;

    do
    {
        temp = (v[i] + normalizado) + over;
        normalizado = 0;
        if(temp == 2)
        {
            v[i] = 0;
            over = 1;
        }
        else if (temp == 1)
        {
            v[i] = 1;
            over = 0;
        }
        i--;
    }
    while(over);

}

void complemento(int v[11])
{
    int i = 0;
    int over = 0;
    int temp = 0;
    int soma[11];

    for(i = 0; i < 11; i++)
    {
        if(v[i] == 0)
            v[i] = 1;
        else v[i] = 0;
    }

    for (i = 10; i >= 0; i--)
    {
        if(i == 10)
            temp = v[i] + 1;
        else temp = v[i] + over;
        if(temp == 2)
        {
            soma[i] = 0;
            over = 1;
        }
        else if(temp == 1)
        {
            soma[i] = 1;
            over = 0;
        }
        else
        {
            soma[i] = 0;
            over = 0;
        }
    }

    for(i = 0; i < 11; i++)
        v[i] = soma[i];

}

void imprimir(int *v, int tam)
{
    int i = 0;

    for(i = 0; i < tam; i++)
        printf("%d", v[i]);

    printf("\n");

}

