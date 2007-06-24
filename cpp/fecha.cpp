//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "fecha.h"
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//valida una fecha devolviendo el extremo si es falsa
//en formato dd/mm/yyyy
//pre 78/78/3555
//post 31/12/3555
AnsiString __fastcall sValidarFecha(AnsiString sFecha)
{
    //TODO mes febrero, chequear año bisiesto

    int nDia = sFecha.SubString(1,2).ToInt(),
    	nMes = sFecha.SubString(4,2).ToInt(),
        nLimite;

	if (nMes > 12) nMes=12;

	if (nMes==1 || nMes==3 || nMes==5 || nMes==7 || nMes==8
    || nMes==10 || nMes==12)
    	nLimite = 31;

	if (nMes==4 || nMes==6 || nMes==9 || nMes==11)
    	nLimite = 30;


    if (nDia > nLimite) nDia = nLimite;

    return ( AnsiString(nDia) + "/" + AnsiString(nMes) + "/" + sFecha.SubString(7,8) );
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//valida una hora devolviendo el extremo si es falsa
//en formato hh:mm:ss
//pre 99:99:99
//post 23:59:59
AnsiString __fastcall sValidarHora(AnsiString sHora)
{
    AnsiString  sH, sMin, sSec, sBlank="00000000000000";

    int nHora, nMin, nSec=0;

    sH = sHora.SubString(1,2);
    //sH = sH.Trim();
    sH = sBlankear(sH);
    sMin = sHora.SubString(4,2);
    sMin = sBlankear(sMin);
    sSec = sHora.SubString(6,2);
    sSec = sBlankear(sSec);

	try{
	    nHora = sH.ToInt();}
    catch (EConvertError&){
    	nHora = 0;}
	try{
	    nMin = sMin.ToInt();}
    catch (EConvertError&){
    	nMin = 0;}
    if (sHora.Length() > 5){
		try{
			nSec = sSec.ToInt();}
	    catch (EConvertError&){
    		nSec = 0;}
    }

    AnsiString sResult;

	if (nHora > 23) nHora = 23;
    if (nMin > 59) nMin = 59;
	if (nSec > 59) nSec = 59;

    sH = nHora;
	sMin = nMin;
    sSec = nSec;

    sH   = sBlank.SubString(1,2-sH.Length()) + sH;
    sMin = sBlank.SubString(1,2-sMin.Length()) + sMin;
    sSec = sBlank.SubString(1,2-sSec.Length()) + sSec;

    if (sHora.Length() > 5)
    	sResult = sH + ":" + sMin + ":" + sSec;
    else
    	sResult = sH + ":" + sMin;

    return (sResult);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
AnsiString __fastcall sBlankear(AnsiString sHora)
{
	for (int i=1; i < sHora.Length() + 1; i++){
    	if (sHora.SubString(i,1) ==" ")
        	sHora = sHora.SubString(1,i-1) + "0" + sHora.SubString(i+1,sHora.Length());
    }

    return sHora;
}
//---------------------------------------------------------------------------
