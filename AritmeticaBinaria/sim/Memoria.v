// +UEFSHDR---------------------------------------------------------------------
// FILE NAME            : sp_rom.v
// AUTHOR               : Jo?o Carlos Nunes Bittencourt
// AUTHOR'S E-MAIL      : joaocarlos@ecomp.uefs.br
// -----------------------------------------------------------------------------
// RELEASE HISTORY
// VERSION  DATE        AUTHOR        DESCRIPTION
// 1.0      2013-02-15  joaocarlos    initial version
// -----------------------------------------------------------------------------
// KEYWORDS: memory, rom, single-port, altera
// -----------------------------------------------------------------------------
// PURPOSE: read hexadecimal values stored in a INPUT_FILE.
// -----------------------------------------------------------------------------
// REUSE ISSUES
//   Reset Strategy: N/A
//   Clock Domains: system clk
//   Critical Timing: N/A
//   Test Features: N/A
//   Asynchronous I/F: N/A
//   Instantiations: N/A
//   Synthesizable (y/n): y
//   Other: N/A
// -UEFSHDR---------------------------------------------------------------------

// Define Input File if it isnt iet
`ifndef ROM_FILE
  `define ROM_FILE "entrada.BIN"
`endif

module Memoria #(
              parameter ADDRESS_WIDTH   = 200,
              parameter DATA_WIDTH      = 48 
            )(
              clk,
              sink_address,  // Address input
              src_data, 	 // Data output
              sink_ren,      // Read Enable
              sink_cen,      // Chip Enable
			  reset
            ) /* synthesis romstyle = "M9K" */;

input  clk, reset;
input  [7:0] sink_address;
output [31:0] src_data;
input sink_ren, sink_cen;

// Specify rom style for ALTERA memory block
//(* romstyle = "M9K" *) reg [DATA_WIDTH-1:0] mem [0:(1001)-1] ;
(* romstyle = "M9K" *) reg [DATA_WIDTH-1:0] mem_Leitura [ADDRESS_WIDTH-1:0] ;
reg [31:0] mem [ADDRESS_WIDTH-1:0] ;
reg [DATA_WIDTH-1:0] aux_mem;

reg [31:0] src_data;
reg [8*40:1] infile;

integer i, file;

// Funcional read block
always @ (negedge clk) begin
	if(reset) begin
	    file = $fopen("Memoria.txt");
		$readmemb(`ROM_FILE, mem_Leitura);  // read memory file		
		for(i=0; i<ADDRESS_WIDTH; i=i+1) begin
			aux_mem = mem_Leitura[i];
			mem[i] = aux_mem[47:16];	
			$fdisplay(file,"%b ",mem[i]);	
		end
		 
	end 
	

	//if (sink_cen && sink_ren)
		src_data = mem[sink_address];
		
end

endmodule
// Thats all folks!
