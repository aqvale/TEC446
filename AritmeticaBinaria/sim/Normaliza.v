module Normaliza(controle, mantissa_Resultado, expoente_Resultado, expoente_Ajustado, mantissa_Normalizada);
input controle;
input [11:0] mantissa_Resultado;
input [4:0] expoente_Resultado;
output reg [4:0] expoente_Ajustado;
output reg [9:0] mantissa_Normalizada;


always @(controle or mantissa_Resultado or expoente_Resultado) begin
	if(controle) begin
		mantissa_Normalizada = mantissa_Resultado[9:0];
		expoente_Ajustado = expoente_Resultado;

		if(mantissa_Resultado[11]==1 & mantissa_Resultado[10]==1) begin
			mantissa_Normalizada = mantissa_Normalizada >> 1;
			mantissa_Normalizada[9] = 1'b1;
			expoente_Ajustado = expoente_Resultado + 1;

		end else if(mantissa_Resultado[11]==1 & mantissa_Resultado[10]==0) begin
			mantissa_Normalizada = mantissa_Normalizada >> 1;	
			expoente_Ajustado = expoente_Resultado + 1;	
		end
	end
end

endmodule