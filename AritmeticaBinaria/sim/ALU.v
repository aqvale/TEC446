module ALU(sinal_A, sinal_B, mantissa_A, mantissa_B, mantissa_Resultado, sinal_Resultado);
input sinal_A, sinal_B;
input [10:0] mantissa_A, mantissa_B;
output reg sinal_Resultado;
output reg [11:0] mantissa_Resultado;


always @(sinal_A or sinal_B or mantissa_A or mantissa_B) begin
	if(sinal_A == sinal_B) 
		mantissa_Resultado = mantissa_A + mantissa_B;
	else 
		mantissa_Resultado = mantissa_A - mantissa_B;	
	
	sinal_Resultado = sinal_A;
end

endmodule 
