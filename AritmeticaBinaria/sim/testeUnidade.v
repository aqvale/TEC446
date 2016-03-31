`ifndef ROM_FILE
  `define ROM_FILE "entrada.BIN"
`endif

module testeUnidade();
  parameter endereco   = 200;
  parameter palavra    = 48;
	
  reg clock, reset;
  reg [12:0] count_stop, count;   
  reg [palavra-1:0] mem [endereco-1:0] ;
  reg [15:0] resu [endereco-1:0] ;
  reg [palavra-1:0] aux_mem;
  reg [15:0] esperado, obtido, A, B;
  integer i, j, acerto, erro, file, erroSubtracao, erroSoma, acertoSubtracao, acertoSoma;
  
  Integrador Integrador(.clock(clock), .reset(reset));
  
	initial begin
	    file = $fopen("TesteUnidade.txt");
	    $readmemb(`ROM_FILE, mem);
		
		for(j=0; j<endereco; j=j+1) begin // Guarda os resultados esperados
		    aux_mem = mem[j];
			resu[j] = aux_mem[15:0];
		end	
		
	    i = 0;
		acerto = 0;
		erro = 0;
		erroSubtracao = 0;
		erroSoma = 0;
	    count_stop = 1'd0;
		acertoSubtracao = 0;
		acertoSoma = 0;
	    count = 1'd0;
		clock = 1'b1;
		reset = 1'b1;
		#10;
		reset = 1'b0;
	end

  always #5 clock = ~clock;
	
  always @(posedge clock) begin
	if(count==3) begin
		esperado = resu[i];
		obtido = Integrador.resultado;
		A = Integrador.saida_A;
		B = Integrador.saida_B;
		if(resu[i] == Integrador.resultado) begin
			acerto = acerto + 1;
			
			if(A[15]!=B[15]) acertoSubtracao = acertoSubtracao + 1;
			else             acertoSoma = acertoSoma + 1;
			
			$fdisplay(file,"Ok ");
		end else begin
			erro = erro + 1;
			
			if(A[15]!=B[15]) erroSubtracao = erroSubtracao + 1;
			else             erroSoma = erroSoma + 1;
			
			$fdisplay(file,"A[%b %b %b] B[%b %b %b] BEsperado : %b %b %b Obtido : %b %b %b  ",
			A[15],A[14:10],A[9:0],B[15],B[14:10],B[9:0],
			esperado[15],esperado[14:10],esperado[9:0],
			obtido[15],obtido[14:10],obtido[9:0]);
		end	
		
		count_stop = count_stop + 1'b1;	
		i = i+1;
	end
	  
	if(count==4)count=0;	
	  count = count + 1;
  end  
	
  always begin
	#1
	if(count_stop>=endereco) begin
	$fdisplay(file,"Total Acertos: %d",acerto);
	$fdisplay(file,"Total Erros: %d",erro);
	$fdisplay(file,"Erros Subtracao: %d",erroSubtracao);
	$fdisplay(file,"Erros Soma: %d",erroSoma);
	$fdisplay(file,"Acertos Subtracao: %d",acertoSubtracao);
	$fdisplay(file,"Acertos Soma: %d",acertoSoma);
	$fclose(file);
	$stop;
	end
  end   

endmodule 