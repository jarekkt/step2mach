#include "string.h"
#include "lwip/def.h"
#include "lwip/udp.h"
#include "lwip/netif.h"
#include "lwip/sys.h"
#include "lwip/sockets.h"

#include "../../serial.h"


#define SCAN_TIMEOUT     3
#define SEND_TIMEOUT    25
#define SERVER_TIMEOUT  5000

#define MAX_MTU       1500


static char         buffer[MAX_MTU];
int                 lSocket;
struct sockaddr_in  sLocalAddr;
socklen_t           sLocalAddrLen = sizeof( sLocalAddr);

struct sockaddr     sRemoteAddr;
socklen_t           sRemoteAddrLen; 
uint32_t            sRemoteOk;

static void mach_conn_thread(void *nf)
{
   char             *  send_buffer;
   uint32_t            send_length;

   int32_t             nbytes;
   uint32_t            divider = 0;
 

   lSocket = lwip_socket(AF_INET, SOCK_DGRAM, 0);

   memset((char *)&sLocalAddr, 0, sizeof(sLocalAddr));

   /* Our connection point */
   sLocalAddr.sin_family      = AF_INET;
   sLocalAddr.sin_len         = sizeof(sLocalAddr);
   sLocalAddr.sin_addr.s_addr = lwip_htonl(INADDR_ANY);
   sLocalAddr.sin_port        = lwip_htons(7000);

   lwip_bind(lSocket, (struct sockaddr *)&sLocalAddr, sizeof(sLocalAddr));

   while (1) 
   {
         sRemoteAddrLen = sizeof(sRemoteAddr);

         nbytes = lwip_recvfrom(lSocket, buffer, sizeof(buffer),MSG_DONTWAIT,&sRemoteAddr,&sRemoteAddrLen);
         if (nbytes>0)
         {
             serial_process_receive(buffer,nbytes);
             sRemoteOk = SERVER_TIMEOUT/SCAN_TIMEOUT;
         }
         else
         {
            if(sRemoteOk > 0)
            {
              sRemoteOk--;
            }
         }


        if( (divider %(SEND_TIMEOUT/SCAN_TIMEOUT)) == 0)
        {
            if(sRemoteOk > 0)
            {
              serial_prepare_response(&send_buffer,&send_length);
              lwip_sendto(lSocket, send_buffer, send_length, MSG_DONTWAIT, &sRemoteAddr, sRemoteAddrLen);
            }
        }

        vTaskDelay( SCAN_TIMEOUT ); 
        divider++;
   }

   lwip_close(lSocket);
}


void mach_conn_init(void)
{
  
  sys_thread_new("mach_conn", mach_conn_thread, NULL, 256, DEFAULT_THREAD_PRIO +2 );
}
