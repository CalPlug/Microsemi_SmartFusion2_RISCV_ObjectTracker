/******************************************************************************

    File Name:  corepwm_timebase.v
      Version:  4.0
         Date:  July 14th, 2009
  Description:  Timebase module
  
  
  SVN Revision Information:
  SVN $Revision: 22461 $
  SVN $Date: 2014-04-24 10:12:56 +0100 (Thu, 24 Apr 2014) $  
  
  

 COPYRIGHT 2009 BY ACTEL 
 THE INFORMATION CONTAINED IN THIS DOCUMENT IS SUBJECT TO LICENSING RESTRICTIONS 
 FROM ACTEL CORP.  IF YOU ARE NOT IN POSSESSION OF WRITTEN AUTHORIZATION FROM 
 ACTEL FOR USE OF THIS FILE, THEN THE FILE SHOULD BE IMMEDIATELY DESTROYED AND 
 NO BACK-UP OF THE FILE SHOULD BE MADE. 
 
FUNCTIONAL DESCRIPTION: 
Refer to the CorePWM Handbook.
******************************************************************************/
`timescale 1 ns / 1 ns // timescale for following modules

module corepwm_timebase #(
parameter APB_DWIDTH = 8
) (
input  PRESETN, 
input  PCLK, 
input [APB_DWIDTH-1:0] period_reg,
input [APB_DWIDTH-1:0] prescale_reg,
output reg [APB_DWIDTH-1:0] period_cnt,
output sync_pulse
);


//wire declarations

//reg  declarations
reg [APB_DWIDTH-1:0] prescale_cnt;

//////main//////
////take prescale, period values and generate period_cnt

// 1st, generate prescale_cnt
always @(negedge PRESETN or posedge PCLK)
begin
   if (!PRESETN) 
   begin
         prescale_cnt <= 0;
   end
   else
   begin
       if (prescale_cnt >= prescale_reg)  //reset prescale_cnt
       begin
   	   prescale_cnt <= 0;   
       end
       else 
       begin
   	   prescale_cnt <= prescale_cnt + 1;   
	   end
   end
end



// 2nd, generate period_cnt based off prescale_cnt
always @(negedge PRESETN or posedge PCLK)
begin
   if (!PRESETN) 
   begin
       period_cnt <= 0;
   end
   else
   begin
       if ((period_cnt >= period_reg) && (prescale_cnt >= prescale_reg))  //reset period_cnt
       begin
   	   period_cnt <= 0;   
       end
       else if (prescale_cnt == prescale_reg) 
       begin
   	   period_cnt <= period_cnt + 1;   
	   end
   end
end

assign sync_pulse = (prescale_cnt >= prescale_reg)? 1'b1:1'b0;

endmodule
