module Calc_Deslocamento(exp1, exp2, exp);
input [4:0] exp1, exp2;
output reg [4:0] exp;

always @(exp1 or exp2) 
	exp = exp1 - exp2;

endmodule 