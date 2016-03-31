/* 
0 10000001 10101000000000000000000(6.625) + 0 10000000 01100000000000000000000 (2.75) = 0 10000010 001011 (9.375) 0k precisou normalizar da primeira forma
0 10000001 00101000000000000000000(4,625) + 0 10000000 01100000000000000000000 (2.75) = 0 10000001 11011  (7.375) ok não precisou normalizar
0 10000000 11100000000000000000000(3,75)  + 0 10000000 11100000000000000000000 (3,75) = 0 10000001 1110   (7.5)   ok precisou normalizar da segunda forma
0 10000001 10101000000000000000000(6.625) + 1 10000000 01100000000000000000000 (2.75) = 0 10000000 1111   (3.875)
*/
	
module teste();
reg [32:0] entrada;
reg [16:0] A, B, aux_troca, Resultado;
reg [10:0] mantissa_A, mantissa_B;
reg [4:0] expoente_A, expoente_B, expoente_Resultado, expoente_dif;
reg sinal_A, sinal_B, sinal_Resultado;

reg [9:0] aux_mantissa_Resultado;
reg [11:0] mantissa_Resultado; // 1 bit a mais para capiturar o carry
integer i;


initial begin
/* B = entrada[31:0];
A = entrada[64:32]; */
A =  16'b0100100010000000;   // 1.00101000000000000000000
B =  16'b0100000000000000;  // 1.01100000000000000000000
expoente_A = A[14:10];
expoente_B = B[14:10];

// ================================================================================================== 
// A>B (Verifica qual do valores é maior, faz A maior que B caso necessário)
if(expoente_A < expoente_B) begin
	aux_troca = A;
	A = B;
	B = aux_troca;
end

mantissa_A = A[9:0];
mantissa_B = B[9:0];
mantissa_A[10] = 1'b1;
mantissa_B[10] = 1'b1;
expoente_A = A[14:10];
expoente_B = B[14:10];
sinal_A = A[16]; 
sinal_B = B[16];

expoente_Resultado = expoente_A; // O expoente do resultado será temporariamente igual a expoente_A. 
							     // Pode requerer ajuste ao final da operação para normalização do resultado.
#40;								 
// ================================================================================================== 
// Calcula o deslocamento e desloca o expoente de B para que sejam os dois iguais
expoente_dif = expoente_A - expoente_B;

for(i=0; i<expoente_dif; i=i+1) begin
	mantissa_B = mantissa_B >> 1;
	if(i==0) begin 
		mantissa_B[9] = 1'b1;
		mantissa_B[10] = 1'b0;       // O bit Escondido passa a ser 0 
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

aux_mantissa_Resultado = mantissa_Resultado[9:0];

if(mantissa_Resultado[11]==1 & mantissa_Resultado[10]==1) begin
	aux_mantissa_Resultado = aux_mantissa_Resultado >> 1;
	aux_mantissa_Resultado[9] = 1'b1;
	expoente_Resultado = expoente_Resultado + 1;

end else if(mantissa_Resultado[11]==1 & mantissa_Resultado[10]==0) begin
	aux_mantissa_Resultado = aux_mantissa_Resultado >> 1;	
	expoente_Resultado = expoente_Resultado + 1;
	
end


#40;
// ================================================================================================== 
Resultado[15] = sinal_Resultado;
Resultado[14:10] = expoente_Resultado;
Resultado[9:0] = aux_mantissa_Resultado;
#40;
end

endmodule 






