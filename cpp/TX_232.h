//clase para el manejo de RS-232
//
//Por Adrián Deccico - deccico@gmx.net
//comienzo: 22/09/2004
//---------------------------------------------------------------------------

#ifndef TX_232H
#define TX_232H

#define SEND 3000

//---------------------------------------------------------------------------
class T232 : public TObject
{

private:

public:
    int __fastcall mTransmitir(HANDLE, int);


};

#endif
