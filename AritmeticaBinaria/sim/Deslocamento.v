module Descocamento(s1, qtd_deslocamento, saida_s1);
input [10:0] s1;
input [3:0] qtd_deslocamento;
output reg [10:0] saida_s1;

always @(s1) begin
	generate
		genvar i;
		for (i = 0; i < qtd_deslocamento; i = i + 1)
		begin:identifier			
			saida_s1 <= {0, s1[10:1]};
		end
	endgenerate
end
endmodule