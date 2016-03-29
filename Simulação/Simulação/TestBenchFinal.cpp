#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <conio.h>
#include <string>


int Binario_para_decimal(int e[5])
{
    int dec=0,d=1;
    int i= 0;

    for(i = 0; i < 5; i++)
        printf("%d", e[i]);

    for(i = 4; i >= 0; i--)
    {
        dec = dec+e[i]*d;
        d = d*2;
    }
    return dec;
}

int soma(int a[11], int b[11], int resultado[11]);
void imprimir(int *v, int tam);
void shift(int v[11], int deslocamento);
void somaExpoente(int v[5], int normalizado);
void saida(int sinal, int expoente[5], int resultado[10], int out[16]);
void complemento(int v[11]);
void separar_dado(int reg_in[48],int in1[16], int in2[16], int comparar_resultado[16]);
int validacao(int resultado[16], int comparar_resultado[16]);
void parser(char *v, int *e, int tam);

int parserNormalExp(char *v, int *e, int tam);
void parserExp(char *v, int *e, int tam);
void parserExpNegativo(char *v, int *e, int tam);

int main()
{
    FILE *entrada;
    int reg_in[48];
    char reg_temp[48];

    int in1[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //2.640625 - 0100000101001000
    int in2[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //2.640625 - 0100000101001000
    int comparar_resultado[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

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
    int expoente_int_result = 0;
    int sinal_result = 0;


    //Verificar se é Infinito ou Zero
    int qtd1 = 0;
    int qtd0 = 0;

    //Validação dos Dados
    int qtd_arredondamento_zero = 0;
    int qtd_arredondamento_infinito = 0;
    int ok = 0;
    int erro = 0;
    int numero_interacao = 0;


    entrada = fopen("estimulos.txt", "r");

    if (entrada == NULL)
    {
        printf("O arquivo não pôde ser aberto!\n");
    }

    while(!feof(entrada))
    {

        fscanf (entrada, "%s ", reg_temp);

        parser(reg_temp, reg_in, 48);
        printf("\n");
        imprimir(reg_in, 48);

        separar_dado(reg_in, in1, in2, comparar_resultado);

        printf("\nDados de entrada: \n");
        imprimir(in1, 16);
        imprimir(in2, 16);

        sinal_a = in1[0];
        sinal_b = in2[0];

        /****CALCULO DO EXPOENTE A e B*********/
        i = 0;
        for(j = 1; j <= 5; j++)
        {
            expoente_binario_a[i] = in1[j];
            i++;
        }
        expoente_a = Binario_para_decimal(expoente_binario_a);
        printf ("Expoente A: %d\n", expoente_a);

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

        /****COMPLEMENTO, CALCULO DO EXPOENTE PARA DESLOCAMENTO*********/
        if(sinal_b == 1 && sinal_a == 0)
            complemento(b);
        else if(sinal_a == 1 && sinal_b == 0)
            complemento(a);

        imprimir(a, 11);
        imprimir(b, 11);

        deslocamento = expoente_a - expoente_b;

        if(deslocamento > 0)
        {
            shift(b, deslocamento);
            printf("\nDado Deslocado: ");
            imprimir(b, 11);
        }
        else if(deslocamento < 0)
        {
            shift(a, deslocamento);
            printf("\nDado Deslocado: ");
            imprimir(a, 11);
        }

        /*************************************************/


        /****SOMA E NORMALIZAÇÃO*********/

        normalizar = soma(a,b,result);
        printf ("\nResultado da soma: ");
        imprimir(result, 11);
        printf("\n");
        printf("\nNormalizar: %d\n", normalizar);

        if(expoente_a >= expoente_b)
        {
            if(sinal_a == 1)
            {
                expoente_int_result = expoente_b;
                for(i = 0; i < 5; i++)
                    expoente_result[i] = expoente_binario_b[i];
            }
            else
            {
                expoente_int_result = expoente_a;
                for(i = 0; i < 5; i++)
                    expoente_result[i] = expoente_binario_a[i];
            }
        }
        else
        {
            if(sinal_b == 1)
            {
                expoente_int_result = expoente_a;
                for(i = 0; i < 5; i++)
                    expoente_result[i] = expoente_binario_a[i];
            }
            else
            {
                expoente_int_result = expoente_b;
                for(i = 0; i < 5; i++)
                    expoente_result[i] = expoente_binario_b[i];
            }
        }

        char temp[5];
        if(normalizar)
        {
            if(sinal_a == 0 && sinal_b == 0 || sinal_a == 1 && sinal_b == 1)
                somaExpoente(expoente_result, normalizar);
        }

        if((sinal_a == 1 && sinal_b == 0 || sinal_a == 0 && sinal_b == 1) && expoente_int_result > 15)
        {
            if(deslocamento > 1)
            {
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
            }
            else
            {
                 expoente_int_result = expoente_int_result - 1;
            itoa(expoente_int_result, temp, 2);

            if(expoente_int_result == 15)
                parserExp(temp, expoente_result, 4);
            else if(expoente_int_result < 15)
                parserExpNegativo(temp, expoente_result, 5);
            else
                parser(temp, expoente_result, 5);
            }
        }


        if(expoente_int_result == 14)
            j = 2;
        else if(result[0] == 1 && normalizar == 0)
            j = 1;
        else
            j = 0;


        for(i = 0; i < 10; i++)
        {
            formato_saida[i] = result[j];
            if(j < 10)
                j++;
        }

        if(expoente_a >= expoente_b)
            sinal_result = sinal_a;
        else    sinal_result = sinal_b;

        printf("\nExpoente Result: ");
        imprimir(expoente_result, 5);
        /*************************************************/

        /*************VERIFICAR INFINITO OU ZERO**********/
        for(i = 0; i < 5; i++)
        {
            if(expoente_result[i])
                qtd1++;
            else
                qtd0++;
        }

        if(qtd1 == 5)
        {
            qtd_arredondamento_infinito++;
            out[0] = 0;
            for(i = 1; i < 6; i++)
                out[i] = 1;

            for(i = 6; i < 16; i++)
                out[i] = 0;
        }
        else if (qtd0 == 5)
        {
            qtd_arredondamento_zero++;
            for(i = 0; i < 16; i++)
                out[i] = 0;
        }
        else
        {
            /****************SAIDA NORMALIZADA*****************/
            saida(sinal_result, expoente_result, formato_saida, out);
        }

        printf("\nOut: ");
        imprimir(out, 16);

        printf("\nGer: ");
        imprimir(comparar_resultado, 16);
        /*************************************************/

        /****************VALIDAÇÃO DOS DADOS*****************/

        if(validacao(out, comparar_resultado))
            ok++;
        else
            erro++;

        numero_interacao++;
    }

    printf("\nNumero de interacoes: %d", numero_interacao);
    printf("\nQuantidade de operacoes corretas: %d", ok);
    printf("\nQuantidade Erros: %d", erro);
    printf("\nQuantidade de arredondamentos zero: %d", qtd_arredondamento_zero);
    printf("\nQuantidade de arredondamentos infinito: %d", qtd_arredondamento_infinito);

    fclose(entrada);

    return 0;
}

int soma (int a[11], int b[11], int result[11])
{
    int temp = 0;
    int i = 0, j = 0, k = 0;
    int over = 0;
    int soma[11] = {0,0,0,0,0,0,0,0,0,0,0};

    for(i = 10; i >= 0; i--)
    {
        temp = (a[i] + b[i]) + over;
        printf("\nTemp %d: %d", i, temp);
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
        printf("\nSoma %d: %d", i, soma[i]);
    }
    /*
        if(over == 1)
        {
            result[0] = 1;
            j = 0;
            for(i = 1; i < 11; i++)
            {
                result[i] = soma[j];
                j++;
            }
        }
        else {
            for(i = 0; i < 11; i++)
                result[i] = soma[i];
        }*/

    for(i = 0; i < 11; i++)
        result[i] = soma[i];

    if(over == 1)
        return 1;
    else return 0;
}

void shift(int v[11], int deslocamento)
{
    int i = 0, d = 0, j = 0;
    int temp[11];

    if(deslocamento < 0)
        d = deslocamento * -1;
    else
        d = deslocamento;

    for(i = 0; i < 11; i++)
        temp[i] = 0;

    for(i = d; i < 11; i ++)
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

    printf("\nResultado:");
    for(i = 0; i < 10; i++)
        printf("%d", resultado[i]);
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

    printf("\nValor de V: ");
    for(i = 0; i < 11; i++)
        printf("%d", v[i]);
    printf("\n");

}

void separar_dado(int reg_in[48],int in1[16], int in2[16], int comparar_resultado[16])
{
    int i = 0, j = 0, aux = 0;

    for(i = 0; i < 16; i++)
    {
        in1[i] = reg_in[i];
        aux++;
    }


    for(i = aux; i < 32; i++)
    {
        in2[j] = reg_in[i];
        aux++;
        j++;
    }

    j = 0;
    for(i = aux; i < 48; i++)
    {
        comparar_resultado[j] = reg_in[i];
        aux++;
        j++;
    }
}

int validacao(int resultado[16], int comparar_resultado[16])
{
    int erro = 0;
    int i = 0;

    for (i = 1; i < 16; i++)
    {
        if(resultado[i] != comparar_resultado[i])
            erro++;
    }

    if(erro != 0)
        return 0;
    else return 1;
}

void parser(char *v, int *e, int tam)
{
    int i = 0, j = 0;
    int temp;

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
}

int parserNormalExp(char *v, int *e, int tam)
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


void imprimir(int *v, int tam)
{
    int i = 0;

    for(i = 0; i < tam; i++)
        printf("%d", v[i]);

    printf("\n");

}

