module Integrador(clock, reset);
	input clock, reset;
	// reg clock, reset;
	wire hab_Leitura, hab_Leitura_, hab_EscritaBR, sinal_Resultado, sinal_A, sinal_B, controle_Resultado, controle_normaliza;
	wire [7:0] endereco_Memoria;
	wire [15:0] saida_A, saida_B, resultado;
	wire [31:0] saida_Memoria;
	wire [4:0] expoente_A, expoente_B, expoente_B_ajustado, expoente_Resultado, expoente_Resultado_Ajustado;
	wire [10:0] mantissa_A, mantissa_B, mantissa_B_ajustado;
	wire [11:0] mantissa_Resultado;
	wire [9:0] mantissa_Normalizada;
	
  
	reg [12:0] count_stop = 1'd0;    //so pra simular
	
   /*  
	initial  begin
		clock = 1'b1;
		reset = 1'b1;
		#10;
		reset = 1'b0;
	end
	
	always #5 clock = ~clock;
	 */
	
	Controler Controler(
	.clock(clock), 
	.reset(reset), 
	.endereco_Memoria(endereco_Memoria), 
	.hab_Leitura(hab_Leitura), 
	.hab_Leitura_(hab_Leitura_), 
	.hab_EscritaBR(hab_EscritaBR), 
	.entrada_A(saida_A), 
	.entrada_B(saida_B),
	.expoente_A(expoente_A), 
	.expoente_B(expoente_B),
	.mantissa_A(mantissa_A),
	.mantissa_B(mantissa_B),
	.sinal_A(sinal_A), 
	.sinal_B(sinal_B),
	.sinal_Resultado(sinal_Resultado), 
	.expoente_Resultado(expoente_Resultado),
	.controle_Resultado(controle_Resultado), 
	.mantissa_B_ajustado(mantissa_B_ajustado), 
	.expoente_B_ajustado(expoente_B_ajustado),
	.resultado(resultado),
	.controle_normaliza(controle_normaliza)
	);
	
	Resultado Resultado(
	.controle(controle_Resultado), 
	.sinal(sinal_Resultado), 
	.mantissa(mantissa_Normalizada), 
	.expoente(expoente_Resultado_Ajustado),
	.resultado(resultado), 
	.entrada_A(saida_A), 
	.entrada_B(saida_B)
	);
	
	Normaliza Normaliza(
	.mantissa_Resultado(mantissa_Resultado), 
	.expoente_Resultado(expoente_Resultado), 
	.expoente_Ajustado(expoente_Resultado_Ajustado), 
	.mantissa_Normalizada(mantissa_Normalizada), 
	.controle(controle_normaliza)
	);
	
	ALU ALU(
	.sinal_A(sinal_A), 
	.sinal_B(sinal_B), 
	.mantissa_A(mantissa_A),
	.mantissa_B(mantissa_B_ajustado), 
	.mantissa_Resultado(mantissa_Resultado), 
	.sinal_Resultado(sinal_Resultado)
	);
	
	Memoria Memoria(
    .clk(clock),
    .sink_address(endereco_Memoria),  	// Address input
    .src_data(saida_Memoria), 			// Data output
    .sink_ren(hab_Leitura),      		// Read Enable
    .sink_cen(hab_Leitura_),     		// Chip Enable
	.reset(reset)
	);
	
	Banco_Registro Banco_Registro(
	.hab_escrita(hab_EscritaBR), 
	.reset(reset), 
	.clock(clock), 
	.A(saida_A), 
	.B(saida_B),
	.entrada(saida_Memoria)
	);
	
	Descocamento Descocamento(
	.expoente_A(expoente_A), 
	.expoente_B(expoente_B), 
	.mantissa_B(mantissa_B), 
	.mantissa_B_ajustado(mantissa_B_ajustado), 
	.expoente_B_ajustado(expoente_B_ajustado)
	);	
	

/* 	
  always begin
	#1
	if(count_stop>=13'b1001110001000) $stop;
	count_stop = count_stop+1'b1;
  end 
  */ 
endmodule 
