include "Memoria.v";

module Teste();
integer count_stop = 0;
reg clock;

Memoria Memoria(.clk(clock));

initial	clock = 1;
	
always #5 clock = ~clock;


  always begin	
	#1
	if(count_stop>=1200) $stop;
	count_stop = count_stop+1;
  end
endmodule
