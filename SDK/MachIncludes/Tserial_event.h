/* ------------------------------------------------------------------------ --
--                                                                          --
--                        PC serial port connection object                  --
--                           for  event-driven programs                     --
--                                                                          --
--                                                                          --
--                                                                          --
--  Copyright @ 2001-2002     Thierry Schneider                             --
--                            thierry@tetraedre.com                         --
--                                                                          --
--                                                                          --
--                                                                          --
-- ------------------------------------------------------------------------ --
--                                                                          --
--  Filename : Tserial_event.cpp                                            --
--  Author   : Thierry Schneider                                            --
--  Created  : April 4th 2000                                               --
--  Modified : June 22nd 2002                                               --
--  Plateform: Windows 95, 98, NT, 2000, XP (Win32)                         --
-- ------------------------------------------------------------------------ --
--                                                                          --
--  This software is given without any warranty. It can be distributed      --
--  free of charge as long as this header remains, unchanged.               --
--                                                                          --
-- ------------------------------------------------------------------------ --
--                                                                          --
-- 01.04.24      Comments added                                             --
-- 01.04.28      Bug 010427 corrected. OnDisconnectedManager was not        --
--                initialized                                               --
-- 01.04.28      connect() function prototype modified to handle 7-bit      --
--                communication                                             --
-- 01.04.29      "ready" field added to remove a bug that occured during    --
--                 reconnect (event manager pointers cleared)               --
--                 I removed the "delete" in Tserial_event_thread_start     --
--                 because it was destroying the object even if we would    --
--                 use it again                                             --
--                                                                          --
-- 02.01.30      Version 2.0 of the serial event object                     --
--                                                                          --
--                                                                          --
-- 02.06.22      - wait for the thread termination before                   --
--                 quiting or restarting                                    --
--               - "owner" field added to be able to call C++ object from   --
--                  the event manager routine                               --
--               - Correction of a bug that occured when receiving data     --
--                 (setting twice the SIG_READ_DONE event)                  --
--                                                                          --
--                                                                          --
--                                                                          --
-- ------------------------------------------------------------------------ --
--                                                                          --
--    Note to Visual C++ users:  Don't forget to compile with the           --
--     "Multithreaded" option in your project settings                      --
--                                                                          --
--         See   Project settings                                           --
--                   |                                                      --
--                   *--- C/C++                                             --
--                          |                                               --
--                          *--- Code generation                            --
--                                       |                                  --
--                                       *---- Use run-time library         --
--                                                     |                    --
--                                                     *---- Multithreaded  --
--                                                                          --
--                                                                          --
--                                                                          --
-- ------------------------------------------------------------------------ */
 

#ifndef TSERIAL_EVENT_H
#define TSERIAL_EVENT_H

#include <stdio.h>
#include <windows.h>
#include "processor.h"


#define SERIAL_PARITY_NONE 0
#define SERIAL_PARITY_ODD  1
#define SERIAL_PARITY_EVEN 2

#define SERIAL_CONNECTED         0
#define SERIAL_DISCONNECTED      1
#define SERIAL_DATA_SENT         2
#define SERIAL_DATA_ARRIVAL      3
#define SERIAL_RING              4
#define SERIAL_CD_ON             5
#define SERIAL_CD_OFF            6

typedef unsigned long uint32;
 
 
#define bool  BOOL 
#define true  TRUE
#define false FALSE
 
 

#define SERIAL_SIGNAL_NBR 7         // number of events in the thread
#define SERIAL_MAX_RX     256       // Input buffer max size
#define SERIAL_MAX_TX     256       // output buffer max size

 
/* -------------------------------------------------------------------- */
/* -----------------------------  Tserial  ---------------------------- */
/* -------------------------------------------------------------------- */
class Tserial_event
{
    // -------------------------------------------------------- //
protected:
    bool          ready;
    bool          check_modem;
    char          port[10];                          // port name "com1",...
    int           rate;                              // baudrate
    int           parityMode;
    cCallback     *manager;
    HANDLE        serial_events[SERIAL_SIGNAL_NBR];  // events to wait on
    unsigned int  threadid;                          // ...
    HANDLE        serial_handle;                     // ...
    HANDLE        thread_handle;                     // ...
    OVERLAPPED    ovReader;                          // Overlapped structure for ReadFile
    OVERLAPPED    ovWriter;                          // Overlapped structure for WriteFile
    OVERLAPPED    ovWaitEvent;                       // Overlapped structure for WaitCommEvent
public:
    char          tx_in_progress;                    // BOOL indicating if a WriteFile is
                                                     // in progress
    char          rx_in_progress;                    // BOOL indicating if a ReadFile is
                                                     // in progress
    char          WaitCommEventInProgress;
    char          rxBuffer[SERIAL_MAX_RX];
    int           max_rx_size;
    int           received_size;
    char          txBuffer[SERIAL_MAX_TX];
    int           tx_size;
    DWORD         dwCommEvent;                       // to store the result of the wait

  

    // ............................................................
    void          OnCharArrival    (char c);
    void          OnEvent          (unsigned long events);


    // ++++++++++++++++++++++++++++++++++++++++++++++
    // .................. EXTERNAL VIEW .............
    // ++++++++++++++++++++++++++++++++++++++++++++++
public:
    void         *owner;                // do what you want with this
    void          run          (void);
                  Tserial_event();
                 ~Tserial_event();
    int           connect          (char *port, int rate, int parity,
                                    char ByteSize, bool modem_events);

    void          setManager       (cCallback *CALL);
    void          setRxSize        (int size);
    void          sendData         (char *buffer, int size);
    int           getNbrOfBytes    (void);
    int           getDataInSize    (void);
    char *        getDataInBuffer  (void);
    void          dataHasBeenRead  (void);
    void          disconnect       (void);
};
/* -------------------------------------------------------------------- */

#endif TSERIAL_EVENT_H

 
