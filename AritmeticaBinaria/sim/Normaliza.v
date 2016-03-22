module Normliza(exp1, exp2, carry, exp_result);

input [4:0] exp1, exp2;
input carry;
output reg [4:0] exp_result;

always @(exp1 or exp2 or carry) begin
	if (carry == 1)
		exp_result = (exp1 + exp2) - 15 + 1;
	else 
		exp_result = exp1;
end
endmodule