module Controler(clock, reset, endereco_Memoria, hab_Leitura, hab_Leitura_, hab_EscritaBR, entrada_A, entrada_B,
expoente_A, expoente_B, mantissa_B_ajustado, expoente_B_ajustado, mantissa_A, mantissa_B, sinal_A, sinal_B, 
sinal_Resultado, expoente_Resultado, controle_Resultado, resultado, controle_normaliza);

  input clock, reset, sinal_Resultado;
  input [15:0] entrada_A, entrada_B, resultado;
  input [10:0] mantissa_B_ajustado;
  input [4:0]  expoente_B_ajustado;
  
  output reg hab_Leitura, hab_Leitura_, hab_EscritaBR, controle_Resultado, sinal_A, sinal_B, controle_normaliza;
  output reg [7:0] endereco_Memoria;
  output reg [4:0] expoente_A, expoente_B, expoente_Resultado;
  output reg [10:0] mantissa_B, mantissa_A;
  
  integer file;
  reg [1:0] estado = 2'b00, prox_estado;
     
  initial begin
    endereco_Memoria = 8'b00000000;
	file = $fopen("TesteResultado.txt");
  end
  
  always @(posedge clock)  
    if(reset)
      estado<=2'b00;
    else
      estado <= prox_estado;
  
     
	  
  always @(estado) 
	case(estado)
      2'b00: begin 
	    controle_Resultado = 1'b0;
		hab_EscritaBR = 1'b1;
		controle_normaliza = 1'b0;
		
		prox_estado = 2'b01;
	  end
	
      2'b01: begin 
	  controle_Resultado = 1'b0;
	  
		expoente_A = entrada_A[14:10];
		expoente_B = entrada_B[14:10];
		mantissa_A = entrada_A[9:0];
		mantissa_B = entrada_B[9:0];
		mantissa_A[10] = 1'b1;
		mantissa_B[10] = 1'b1;
		sinal_A = entrada_A[15]; 
		sinal_B = entrada_B[15];
		
		expoente_Resultado = expoente_A; 
		controle_normaliza = 1'b1;
		prox_estado = 2'b10;
	  end
      
	  2'b10: begin
		mantissa_B = mantissa_B_ajustado;
		expoente_B = expoente_B_ajustado;
		controle_Resultado = 1'b1;
		controle_normaliza = 1'b0;
		prox_estado = 2'b11;
	  end
	  
	  2'b11: begin
		endereco_Memoria = endereco_Memoria + 1'b1;
		controle_normaliza = 1'b0;
	    $fdisplay(file,"%b %b %b ",entrada_A, entrada_B, resultado);
		
		prox_estado = 2'b00;
	  end
	endcase
	
endmodule 