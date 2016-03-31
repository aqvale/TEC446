
module Banco_Registro (hab_escrita, reset, clock, A, B, entrada);  
  
  input [31:0] entrada;
  output reg [15:0] A, B;
  input reset, clock, hab_escrita;
  reg [15:0] registro_1;	
  reg [15:0] registro_2;	
	

	always @(posedge clock) begin 		  
		if(reset) begin 
			registro_1 = 16'b0000000000000000;
			registro_2 = 16'b0000000000000000;
				
		end	else if(hab_escrita) begin 			
			registro_1 = entrada[15:0]; 
			registro_2 = entrada[31:16]; 
				
		end 
			
		if(registro_1[14:10]<=registro_2[14:10]) begin
			A = registro_2; // Maior 	   
			B = registro_1; // Menor			
		end	else begin
			A = registro_1; // Maior	   
			B = registro_2; // Menor
		end
	end
endmodule

