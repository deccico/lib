//---------------------------------------------------------------------------
#ifndef rs232H
#define rs232H

//---------------------------------------------------------------------------
#include <limits.h>

class TRS232 //: public TComponent
{
private:

protected:
    HANDLE hComm; // = NULL;
    long nSent;  //indica cantidad de bytes enviados
    int nReceived; //indica cantidad de bytes recibidos
    int __fastcall mSendRS232(int ncaracter);
    bool bTransmitiendo;
    int nSendTimes;   //nro de reintentos al enviar
    bool bConectado;    //indica si ha establecido una conexión
    AnsiString __fastcall mChauCaracter(AnsiString sCadena,AnsiString s);


public:
    __fastcall TRS232(void);
    ~TRS232();
                                    //COM,Baudios,Data,Stop,Paridad
    void __fastcall mConectar(AnsiString sPuerto,AnsiString sBaudios,
    AnsiString sData,AnsiString sStop,AnsiString sParidad);
    void __fastcall mDesconectar();
    bool __fastcall mTransmitir(AnsiString);  //transmite HEXA en AnsiString al puerto RS232
    long __fastcall mGetnSent() {return nSent;}
    bool __fastcall mGetbTransmitiendo() {return bTransmitiendo;}
    int __fastcall mGetSendTimes() {return nSendTimes;}    //default 3000
    void __fastcall mSetSendTimes(int n) {nSendTimes = n;}
    bool __fastcall mGetbConectado() {return bConectado;}
    int __fastcall mGetnReceived();
    AnsiString __fastcall mEmpaquetar(AnsiString sComando);
//__published:
    //  __property AnsiString ParametrosConexion = {read=sParametrosConexion};


};
//----------------------------------------------------------------------------
#endif