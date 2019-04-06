#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#define BUFFER_SIZE         4096
#define PM33F_ROW_SIZE		64*8


#define PM_SIZE		682		/* Max: 64KB/3/32=682 PM rows for our 33F64MC802. */

#define COMMAND_NACK       'N'
#define COMMAND_ACK        'Y'
#define COMMAND_WRITE_PM1  '1'
#define COMMAND_WRITE_PM2  '2'
#define COMMAND_WRITE_PM3  '3'
#define COMMAND_RESET      'R'



/* embedded firmware hex file */
extern const unsigned char bin_data[];
extern const long bin_data_size ;

/* embedded firmware hex file version*/
extern const char step2mach_ver; 

int update_firmware(void * handle,void * reset_handle);

#endif