//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "rs232.h"
#include "libGral.h"


//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

// GLOBAL VARIABLES
//TRead *ReadThread;
COMMTIMEOUTS ctmoNew = {0}, ctmoOld;
//HANDLE hComm = NULL;
//HANDLE hRS232;



__fastcall TRS232::TRS232()
{
    nSent=0;
    nSendTimes=3000;
    bConectado=false;
    hComm = NULL;
}


//---------------------------------------------------------------------------
//Conecta con el puerto serie correspondiente
void __fastcall TRS232::mConectar(AnsiString sPuerto,AnsiString sBaudios,AnsiString sData,AnsiString sStop,AnsiString sParidad)
{
 AnsiString sParamCom;
 mDesconectar();
 DCB dcbCommPort;

 //9600,N,8,1";
 sParamCom=sBaudios + "," + sParidad + "," + sData + "," + sStop  ;
 //sParamCom=frmSetup->cmbBaudios->Text+","+sParidad+","+frmSetup->cmbData->Text+","+frmSetup->cmbStop->Text;

 if (sPuerto == "NO")
    return;
 if (sPuerto.IsEmpty()){
        ShowMessage("Debe seleccionar un puerto");
        return;}

  // ABRIR EL COMM PORT.

  hComm = CreateFile(sPuerto.c_str(),
                      GENERIC_READ | GENERIC_WRITE,
                      0,
                      0,
                      OPEN_EXISTING,
                      0,
                      0);


  // chequea si sirve el puerto
  if(hComm == INVALID_HANDLE_VALUE)
  {
    //cerrar el puerto si esta abierto
	if(hComm) {
            Sleep(250); // WAIT FOR THREAD TO FINISH
            SetCommTimeouts(hComm, &ctmoOld);
    	    CloseHandle(hComm);
    throw Exception("Error conectando al puerto com "+sPuerto);
  }

         return;
         }

  // SETEAR LOS COMM TIMEOUTS.

  GetCommTimeouts(hComm,&ctmoOld);
  ctmoNew.ReadTotalTimeoutConstant = 100;
  ctmoNew.ReadTotalTimeoutMultiplier = 0;
  ctmoNew.WriteTotalTimeoutMultiplier = 0;
  ctmoNew.WriteTotalTimeoutConstant = 0;
  SetCommTimeouts(hComm, &ctmoNew);

  // setear parametros de comunicacion BAUD RATE, PARITY, WORD SIZE
  // y STOP BITS.
  // BuildCommDCB debe ser un puntero a STRING.
  // BuildCommDCB() DEFAULTS TO NO HANDSHAKING.

  dcbCommPort.DCBlength = sizeof(DCB);
  GetCommState(hComm, &dcbCommPort);
  BuildCommDCB(sParamCom.c_str(), &dcbCommPort);
  SetCommState(hComm, &dcbCommPort);

  // ACTIVAr la THREAD.
  // THE FALSE ARGUMENT SIMPLY MEANS IT HITS THE
  // GROUND RUNNING RATHER THAN SUSPENDED.

  //ReadThread = new TRead(false);
  //frmLCD->mEstadoConexion(true);
  bConectado=true;
  Beep();


}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//realiza la desconección del puerto serie usado
void __fastcall TRS232::mDesconectar()
{
  //chequea que no se este desconectado
  if(!hComm)
         return;


  // terminar la thread
  //if (ReadThread != NULL) ReadThread->Terminate();

  // CERRAR EL PUERTO SI ESTA ABIERTO
  if(hComm != INVALID_HANDLE_VALUE)
  {
    Sleep(250); // ESPERA QUE TERMINE LA THREAD
    SetCommTimeouts(hComm, &ctmoOld);
    CloseHandle(hComm);
    hComm = NULL;
  }
  //frmLCD->mEstadoConexion(false);
  bConectado=false;
  Beep();

}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//Procesamiento y transmisión del paquete. Chequea conexión
bool __fastcall TRS232::mTransmitir(AnsiString sPaq)
{
        if (!bConectado) return false;

        AnsiString sCmd;
        int msg;

        if (!mGetbConectado()) return false;

        sPaq = ChauCaracter(sPaq,' ');
        sPaq = sPaq.UpperCase();
        for( int n=1; n <= sPaq.Length() ;n=n+2)
        {      sCmd = sPaq.SubString(n,2);
               msg = AnsiHexToIntDec(sCmd);
               if (msg == - 1)
                   {Beep();
                    ShowMessage("You must input a correct number");
                    return false;
                    }
               if ( mSendRS232(msg) < 0 )
                   {return false;}
        } //fin for

        nSent=nSent+(sPaq.Length()/2);
        if (nSent > LONG_MAX)
            nSent=0; 
        return true;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//transmite el caracter hasta que se vacie en el buffer segun
//condiciones de transmision
//pre HANDLE (puerto serie) y caracter valido
//post caracter transmitido en el puerto => return 0; o error => return < 0
int __fastcall TRS232::mSendRS232(int ncaracter)
{
    int ntries=nSendTimes; //nro de intentos de transmisión del caracter .INI
    int nresult=0; //resultado de la operacion de transmision
    AnsiString sError;

    bTransmitiendo=true;
     //reemplazar por un label que indique estado de conexión
    if (!hComm)   //chequea conexión al puerto
      { Beep();
        ShowMessage("Error opening serial port");
        return -1;
       }

    while ( (nresult == 0) && (ntries != 0) )
        {ntries--;
         nresult=TransmitCommChar(hComm, ncaracter);
         //if(!TimerTx->Enabled) TimerTx->Enabled=true;
         }

    if (ntries==0) sError = "Time Out";
    if (nresult == 0) sError=sError+" Byte not transmited";
    if (ntries==0 || nresult == 0)
        {Beep();
         ShowMessage(sError);
         return -2;
         }

    bTransmitiendo=false;
    return 0;            //funcion terminada coorectamente
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
TRS232::~TRS232()
{
    mDesconectar();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
int __fastcall TRS232::mGetnReceived()
{
    //nReceived=ReadThread->mGetnRead();
    //return nReceived;
    return 0;
}
//---------------------------------------------------------------------------

AnsiString __fastcall TRS232::mEmpaquetar(AnsiString sComando)
{
  AnsiString sTop,sCmd,sFSN;
  AnsiString sPaquete,sHeader,sTail,sProcess,s,sData;
  int nTop,msg;
  int j;
  char *c,car;

  //sComando=sComando.UpperCase(); //mayusculas
  //sComando=mChauCaracter(sComando,' '); //quita blancos
  if (sComando.IsEmpty())
        return "-1";
  sData=sComando;

  s.SetLength(1);

  for (int i=1;i<=sData.Length();i++){
       s= sData.SubString(i,1);
       c= s.c_str();
       car = (char) *c;
       j=toascii(car);
       sProcess = sProcess + sProcess.IntToHex(j,2);
  }

  return sProcess;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//quita un caracter en el primer argumento especificado en el segundo argumento
AnsiString __fastcall TRS232::mChauCaracter(AnsiString sCadena,AnsiString s)
{
    AnsiString sSinBlancos;
    int i;
    i=sCadena.Length();

    for (int c=1;c<i+1;c++)
        if (sCadena.SubString(c,1)!= s)
            sSinBlancos=sSinBlancos+sCadena[c];
     return sSinBlancos;
};
//---------------------------------------------------------------------------

