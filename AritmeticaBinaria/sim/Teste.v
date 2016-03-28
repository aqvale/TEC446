/* 	FIZ A SOMA DE  9,75 + 0,5625 E FUNCIONOU, FALTA FAZER A PARTE DA NORMALIZAÇÃO E AJUSTE DOS EXPOENTES E
TRATAR OS CASOS ESPECIAIS COMO INFINITO E ZERO, SE A GENTE FAZER FUNCIONAR NESSE ARQUIVO, PASSAR PARA OS MÓDULOS
VAI SER FÁCIL DEPOIS */
	
module teste();
reg [63:0] entrada;
reg [31:0] A, B, aux_troca, Resultado;
reg [23:0] mantissa_A, mantissa_B;
reg [7:0] expoente_A, expoente_B, expoente_Resultado, expoente_dif;
reg sinal_A, sinal_B, sinal_Resultado;

reg [22:0] aux_mantissa_Resultado;
reg [24:0] mantissa_Resultado; // 1 bit a mais para capiturar o carry
integer i;


initial begin
/* B = entrada[31:0];
A = entrada[64:32]; */
A =  32'b01000000100101000000000000000000;  // 1.00101000000000000000000
B =  32'b01000000001100000000000000000000;  // 1.01100000000000000000000
expoente_A = A[30:23];
expoente_B = B[30:23];

// ================================================================================================== 
// A>B (Verifica qual do valores é maior, faz A maior que B caso necessário)
if(expoente_A < expoente_B) begin
	aux_troca = A;
	A = B;
	B = aux_troca;
end

mantissa_A = A[22:0];
mantissa_B = B[22:0];
mantissa_A[23] = 1'b1;
mantissa_B[23] = 1'b1;
expoente_A = A[30:23];
expoente_B = B[30:23];
sinal_A = A[31]; 
sinal_B = B[31];

expoente_Resultado = expoente_A; // O expoente do resultado será temporariamente igual a expoente_A. 
							     // Pode requerer ajuste ao final da operação para normalização do resultado.
#40;								 
// ================================================================================================== 
// Calcula o deslocamento e desloca o expoente de B para que sejam os dois iguais
expoente_dif = expoente_A - expoente_B;

for(i=0; i<expoente_dif; i=i+1) begin
	mantissa_B = mantissa_B >> 1;
	if(i==0) begin 
		mantissa_B[22] = 1'b1;
		mantissa_B[23] = 1'b0;       // O bit Escondido passa a ser 0 
	end
end	

expoente_B = expoente_B + expoente_dif;
#40;
// ================================================================================================== 
// Soma as mantissas
if(sinal_A == sinal_B) begin
	mantissa_Resultado = mantissa_A + mantissa_B;
end else begin
	mantissa_Resultado = mantissa_A - mantissa_B;	
end
	sinal_Resultado = sinal_A;
#40;
// ================================================================================================== 
// Normalizar (ajustar expoente resultado caso necessário)

//if(mantissa_Resultado[24]==0 & mantissa_Resultado[23]==1)//ok normalizado

aux_mantissa_Resultado = mantissa_Resultado[22:0];

if(mantissa_Resultado[24]==1 & mantissa_Resultado[23]==1) begin
	aux_mantissa_Resultado = aux_mantissa_Resultado >> 1;
	aux_mantissa_Resultado[22] = 1'b1;
	aux_mantissa_Resultado = aux_mantissa_Resultado + 1;

end else if(mantissa_Resultado[24]==1 & mantissa_Resultado[23]==0) begin
	aux_mantissa_Resultado = aux_mantissa_Resultado >> 1;	
	aux_mantissa_Resultado = aux_mantissa_Resultado + 1;
	
end


#40;
// ================================================================================================== 
// Montar Resultado
Resultado[31] = sinal_Resultado;
Resultado[30:23] = expoente_Resultado;
Resultado[22:0] = aux_mantissa_Resultado;
#40;
end

endmodule 






