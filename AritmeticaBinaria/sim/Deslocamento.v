module Descocamento(expoente_A, expoente_B, mantissa_B, mantissa_B_ajustado, expoente_B_ajustado);
input [4:0] expoente_A, expoente_B;
input [10:0] mantissa_B;
output reg [10:0] mantissa_B_ajustado;
output reg [4:0]  expoente_B_ajustado;

reg [10:0]aux_mantissa_B;
reg [4:0] expoente_dif;
integer i;




always @(expoente_A or expoente_B or mantissa_B) begin
	
	expoente_dif = expoente_A - expoente_B;
    aux_mantissa_B = mantissa_B;
	
	for(i=0; i<expoente_dif; i=i+1) begin
		mantissa_B_ajustado = aux_mantissa_B >> 1;	
		aux_mantissa_B = mantissa_B_ajustado;
	
		$display  ("des   %d %b",i,mantissa_B_ajustado);
	end	
	
	if(expoente_dif==0) 
		mantissa_B_ajustado = aux_mantissa_B;
	
	expoente_B_ajustado = expoente_B + expoente_dif;
end
endmodule 