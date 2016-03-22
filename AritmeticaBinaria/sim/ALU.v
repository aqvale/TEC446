module ALU(s1, s2, result, carry);
input [10:0] s1, s2;
output reg [10:0] result;
output reg carry;

reg [11:0] auxResult;

always @(s1 or s2)begin
	auxResult = 12'b000000000000;
	auxResult = s1 + s2;
	carry = auxResult[11];
	result = auxResult[10:0];
end

endmodule 
