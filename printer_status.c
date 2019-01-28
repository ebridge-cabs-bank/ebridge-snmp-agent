//
// Printer Status Reader
//

#include <svc.h>
#include <stdio.h>
#include <string.h>
#include <printer.h>

void main(void) 
{
   int hPrinter;
   int retVal; // capture the return value from called function

   // structure to fill comm parameters for com port
   open_block_t param;

   // open printer com port
   hPrinter = open("/dev/com4", 0);

   // set printer com port parameters
   memset(&param, 0, sizeof(param));
   // ITP default baud rate, 19200 baud
   param.rate = Rt_19200;
   // ITP is always set at 8N1
   param.format = Fmt_A8N1 | Fmt_auto | Fmt_RTS;
   param.protocol = P_char_mode;
   param.parameter = 0;
   
   set_opn_blk(hPrinter, &param);
   SVC_WAIT(200);

   p3700_init(hPrinter, 6);

}
