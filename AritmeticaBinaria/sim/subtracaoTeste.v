module subtracaoTeste();
reg [31:0] A, B, aux_troca, Resultado;
reg [23:0] mantissa_A, mantissa_B, complemento_A2;
reg [7:0] expoente_A, expoente_B, expoente_Resultado, expoente_dif;
reg sinal_A, sinal_B,sinal_Resultado;
reg [24:0] mantissa_Resultado; 
reg [22:0] aux_mantissa_Resultado;
integer file;

initial begin
	file = $fopen("TesteResultado.txt");

A =  32'b01000001001010000000000000000000;  // 1.00101000000000000000000
B =  32'b11000001001100100000000000000000;  // 1.01100000000000000000000
mantissa_A = A[22:0];
mantissa_B = B[22:0];
mantissa_A[23] = 1'b1;
mantissa_B[23] = 1'b1;
expoente_A = A[30:23];
expoente_B = B[30:23];
sinal_A = A[31];
sinal_B = B[31];

if(expoente_A < expoente_B) begin
	aux_troca = A;
	A = B;
	B = aux_troca;
end

expoente_dif = expoente_A-expoente_B;
case(expoente_dif)
	0: expoente_Resultado = expoente_A - 1;
	1: expoente_Resultado = expoente_B;
	default: expoente_Resultado = expoente_A;
endcase

if(sinal_A != sinal_B)
	if(sinal_A == 1) begin
		complemento_A2 = (~mantissa_A) + 1;
		complemento_A2 = complemento_A2 >> expoente_dif;
		mantissa_Resultado = mantissa_A + complemento_A2;
		
	end else if(sinal_B == 1) begin
		complemento_A2 = (~mantissa_B) + 1;
		complemento_A2 = complemento_A2 >> expoente_dif;
		mantissa_Resultado = complemento_A2 + mantissa_B;
		
	end
    sinal_Resultado = sinal_A;





aux_mantissa_Resultado = mantissa_Resultado[22:0];

if(mantissa_Resultado[24]==1 & mantissa_Resultado[23]==1) begin
	aux_mantissa_Resultado = aux_mantissa_Resultado >> 1;
	aux_mantissa_Resultado[22] = 1'b1;
	expoente_Resultado = expoente_Resultado + 1;

end else if(mantissa_Resultado[24]==1 & mantissa_Resultado[23]==0) begin
	aux_mantissa_Resultado = aux_mantissa_Resultado >> 1;	
	expoente_Resultado = expoente_Resultado + 1;
	
end


Resultado[31] = sinal_Resultado;
Resultado[30:23] = expoente_Resultado;
Resultado[22:0] = aux_mantissa_Resultado;
$fdisplay(file,"%b %b %b : %b",sinal_Resultado, expoente_Resultado, aux_mantissa_Resultado, Resultado);
		
end
endmodule 