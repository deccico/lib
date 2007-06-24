//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TX_232.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


//---------------------------------------------------------------------------
//transmite el caracter hasta que se vacie en el buffer segun
//condiciones de transmision
//pre HANDLE (puerto serie) y caracter valido
//post caracter transmitido en el puerto => return 0; o error => return < 0
int __fastcall T232::mTransmitir(HANDLE hhand, int ncaracter)
{
    int ntries=SEND; //nro de intentos de transmisión del caracter .INI
    int nresult=0; //resultado de la operacion de transmision
    AnsiString sError;

     //reemplazar por un label que indique estado de conexión
    if (!hhand)   //chequea conexión al puerto
      { Beep();
        ShowMessage("Error opening serial port");
        return -1;
       }

    while ( (nresult == 0) && (ntries != 0) )
        {ntries--;
         nresult=TransmitCommChar(hhand, ncaracter);
         if(!TimerTx->Enabled) TimerTx->Enabled=true;
         }

    if (ntries==0) sError = "Time Out";
    if (nresult == 0) sError=sError+" Byte not transmited";
    if (ntries==0 || nresult == 0)
        {Beep();
         ShowMessage(sError);
         return -2;
         }

    return 0;            //funcion terminada coorectamente
}
//---------------------------------------------------------------------------

