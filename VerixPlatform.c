//
// Platform module for Verix API
// 
// This module provides access to Verix API's
//

#include <svc.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <printer.h>

//
//
// IMSI 
//    International Mobile Subscriber Identity
//
//    https://www.portech.com.tw/data/Siemens%20mc55i_AT.pdf
//        Page 111, Section 6.10
//
//    AT+CIMI Request IMSI
//
// GPS COORDINATES
//
//    http://www.groundcontrol.com/AT_Command_Reference_5_9_1_3.htm#AT__IGPS
//
//    request:  AT _IGPS=?
//    response: _IGPS:  <lat_deg>,<lon_deg>,<type>,<status>,<time>
//              Defined values
//                 <lat_deg>:	decimal (-90.00-90.00); 
//                              Latitude in decimal degrees (minutes & seconds 
//                                 converted to decimal degrees)
//                 <lon_deg>:	decimal (-180.00-180.00); 
//                              Longitude, also in decimal
//                 <type>:	string constant ("2D","3D","Stored","Acquiring"); 
//                                 Fix Quality
//                              "2D",  	     GPS receiver has a 2D fix
//                              "3D",  	     GPS receiver has a 3D fix
//                              "Stored",    GPS receiver is off 
//                                              – Lat & Lon are stored values of latest fix
//                              "Acquiring", attempting to acquire a fix
//                 <status>:	string constant ("allowed","barred","undetermined"); 
//                                   Fix status
//                               "allowed"  	Terminal is permitted to display GPS
//                               "barred"  	GPS operation barred at the location
//                               "undetermined" GPS network-policy not received
//                 <time>:	decimal; Timestamp

//
// GPS STRUCTURE
//
gps_struct_t {
   char* latitude,
   char* longitude
}

char* get_gprs_params(void) {

   // open com port
   int modem_fle_descriptor = open("/dev/com2", O_ASYNC);

   // imsi request AT command
   char imsi_req_cmd[] = "AT+CIMI";

   // cell towers info request ATM command 
   char towers_req_cmd[] = "AT^SMONC"

   // imsi request 
   write(modem_file_descriptor, imsi_req_cmd, sizeof(imsi_req_cmd));

   // cell towers info request
   write(modem_file_descriptor, towers_req_cmd, sizeof(towers_req_cmd));

   return imsi;
}

/*
 * open com port
 */
int open_port(void) {

   int file_descriptor; /* file descriptor for the port */

   file_descriptor = open("/dev/com2", O_RDWR | O_NOCTTY | O_NDELAY);
   if (file_descriptor == -1) {
      perror("open_port: Unable to open /dev/com2 - ");
   } else {
      fcntl(file_descriptor, F_SETFL, FNDELAY);
   }
   
   printf("In Open port file_descriptor = %i\n", file_descriptor);

   return (file_descriptor);
}

//
// RESTART DEVICE 
//
void Platform_Reboot(void) {
   SVC_RESTART("")
}

//
// READ SYSTEM LOG FILE
//
int Platform_fread(int handle, char *buf, int len) {
   return read(handle, buf, len)
}

//
// READ PRINTER STATUS
//
void Platform_read_printer_status(void) {

   int hPrinter;
   int retVal; // capture the return value from called function

   // structure to fill comm parameters for com port
   open_block_t param;

   // open printer com port
   hPrinter = open("/dev/com4", 0);

   // printer status request
   int printer_status = hPrinter.write("<ESC>d");

   /*
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
   
   */

}

// 
// GET RAM SIZE
//    Verix-V-Operating-System-Programmers-Manual – Page 308
//
int get_ram_size(void) {
   return SVC_RAM_SIZE(void);
}
