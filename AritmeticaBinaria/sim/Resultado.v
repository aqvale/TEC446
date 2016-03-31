module Resultado(controle, sinal, mantissa, expoente, resultado, entrada_A, entrada_B, qNaN, sNaN, inf);
input [15:0] entrada_A, entrada_B;
input controle, sinal;
input [9:0] mantissa;
input [4:0] expoente;
output reg [15:0] resultado;
output reg qNaN;
output reg sNaN;
output reg inf;

reg [15:0] auxResultado;

always @(controle or sinal or mantissa or expoente)
	if(controle) begin
/* 		qNaN = 0;
		sNaN = 0;
		inf = 0;
	if((entrada_A[15] != entrada_B[15])&( entrada_A[14:0] != entrada_B[14:0])) begin
		resultado = 0;
		qNaN = 0;
		sNaN = 0;
		inf = 0;	
	end		
	else if(expoente == 31 && mantissa == 0) begin
		qNaN = 0;
		sNaN = 0;
		inf = 1;
	end
	else if(expoente == 31 && mantissa[9] == 1) begin
		qNaN = 1;
		sNaN = 0;
		inf = 0;
	end
	else if(expoente == 31 && mantissa[9] == 0) begin
		qNaN = 0;
		sNaN = 1;
		inf = 0;		
	end			
	 */	
	
	auxResultado[15] = sinal;
	auxResultado[14:10] = expoente;
	auxResultado[9:0] = mantissa;
	resultado = auxResultado;
	end

endmodule