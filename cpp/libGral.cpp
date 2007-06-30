//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "libGral.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
//quita un caracter en el primer argumento especificado en el segundo argumento
AnsiString __fastcall ChauCaracter(AnsiString sCadena,AnsiString s)
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


//---------------------------------------------------------------------------
//convierte un AnsiString con valor en hexadecimal a su valor en entero
int __fastcall AnsiHexToIntDec(AnsiString sN)
{
        AnsiString scar,snum=sN;
        __int32 h,nnumero=0;
        int expo,num=0,nlong=snum.Length();

        for(int i=1;i<=nlong;i++)
        {
          scar=snum[i];
          if (scar >= '0' && scar <= '9') snum[i]='0';
          switch (snum[i])
          {
                case 'A' : num=10;break;
                case 'B' : num=11;break;
                case 'C' : num=12;break;
                case 'D' : num=13;break;
                case 'E' : num=14;break;
                case 'F' : num=15;break;
                case '0' : num=scar.ToInt();break;
          }
          expo=nlong-i;

          h=1;
          for (int v=1;v<=expo;v++){
            h=16*h;
          }
          //f=(Power(16,expo));
          //f=nnumero+num*f;
          //nnumero=f;
          nnumero = nnumero + num*h;
        }//fin For

        return nnumero;
}
//--fin AnsiIntToHex----------------------------------------------------


//---------------------------------------------------------------------------
//convierte un AnsiString con hora en milésimas de segundo a hh:mm:ss
AnsiString __fastcall mCentToHHMMSS(AnsiString sN)
{
        return "0";
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//rescato el indice en cuestion
//pre de un AnsiString "1.1.2.3.4.5.7.153"
//post devuelve "153"
AnsiString __fastcall GetIndice(const AnsiString sOID)
{
        AnsiString sInd;
        int ji,j;

        for (ji=0, j=sOID.Length(); j > 0; ji++, j--){
                if (sOID.SubString(j,1)=='.')
                        break;
        }
        sInd = sOID.SubString(j+1,ji);  //oid de la llamada
        return sInd;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//rescato el doble indice en cuestion
//pre de un AnsiString "1.1.2.3.4.5.7.153"
//post devuelve "7.153"
AnsiString __fastcall GetDobleIndice(const AnsiString sOID)
{
        AnsiString sInd1,sInd2;

        sInd1 = GetIndice(sOID);
        sInd2 = GetIndice(sOID.SubString(1, sOID.Length() - sInd1.Length() - 1));

        //return sInd2 + DecimalSeparator	+ sInd1;
        return sInd2 + "." + sInd1;
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//convierte un string a un double
//pre: AnsiString representando un nro, con cualquuier separador
//post: cero en caso de error
double __fastcall sToDouble(AnsiString sNumber)
{
    int nSep=0, nInit=0;
    //double dResult;
    bool bSep=false, bInit=false;
    AnsiString sI, sResult;


    //busca al separador y el comienzo de los caracteres sacando el cero
    for (int j=1; j<sNumber.Length()+1; j++){
        sI = sNumber.SubString(j,1);


        if (!bSep && !bInit && sI==0){
            nInit++;
        }
        if (sI > "0" && sI  <= "9" && !bInit){
            bInit=true;
            nInit=j;
        }


        if ((sI < "0" || sI > "9") && !bSep ){
            nSep=j;
            bSep=true;
            if (!bInit){
                bInit=true;
                nInit=j;
            }
        }
        else{
            if ((sI < "0" || sI > "9") && bSep ){
                sResult = "-1";
                break;
            }
        }
    }

    if (sResult == "-1")
        return 0;

    if (!bSep)
        sResult = sNumber.SubString(nInit,  sNumber.Length() - nInit + 1);
    else{
        sResult = sNumber.SubString(nInit, nSep-nInit) + DecimalSeparator;
        sResult = sResult + sNumber.SubString(nSep+1, sNumber.Length() - nSep);
    }

    return sResult.ToDouble();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//pre número int válido en string
//post int o cero en caso de error
//TODO controlar largo del string
int __fastcall StringToInt(AnsiString sNumero)
{
    for (int i=1; i<sNumero.Length()+1; i++){
        if (sNumero.SubString(i,1) > "9" || sNumero.SubString(i,1) < "0")
            return 0;
    }

    return sNumero.ToInt();
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//pasa de timeticks a hora min segundo tomando en cuenta TimeTicks y Hora Actual
//sTimeTicksi  tiempo actual en timeticks
//nTT0  tiempo inicial en timeticks
//nTime0  tiempo inicial en TTimeDate
AnsiString CalculoHora(AnsiString sTimeTicksi, unsigned int nTT0, double nTime0)
{
    if (sTimeTicksi == "" || sTimeTicksi == "0") return "0";

    AnsiString sFormatoHora = "hh:nn:ss";

    if (nTT0 == 0 || nTime0==0) return "";

    double nAux, nDeltaTT;

    //diferencia entre timeticks inicio y actual
    nDeltaTT =  abs(sTimeTicksi.ToDouble() - nTT0);


    AnsiString sTimei, sTime;

    nAux = nDeltaTT;
    double nDias, nHoras, nSeg;

    nAux = nAux / 100;
    nAux = (nAux / 60) / 60;
    nAux = nAux / 24;
    nDias = (int) nAux;
    nAux = nAux - nDias;

    //diferencia en TDateTime de la hora inicial y final
    sTimei = AnsiString(nAux);
    sTimei = AnsiString(nDias) + DecimalSeparator + sTimei.SubString(3,sTimei.Length()-3);

    //agrego la hora inicial
    TDateTime dtH1;
    if (nTT0 > sTimeTicksi.ToDouble()){
        dtH1 = Now() - sTimei.ToDouble();
    }
    else
        dtH1 = sTimei.ToDouble() + nTime0;

    sTime = FormatDateTime(sFormatoHora, dtH1);
    return sTime;

}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
AnsiString CharToHexa(AnsiString sValue)
{
  AnsiString s, sVal;
  unsigned char *c;
  int n;

  for (int j=1; j < 17; j++)
  {
            s = sValue.SubString(j, 1);
            c = s.c_str();
            n = (int) *c;
            s = s.IntToHex(n,2);
            sVal = sVal + s;
  }
  return sVal;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
AnsiString __fastcall mEmpaquetar(AnsiString sComando)
{
  AnsiString sTop,sCmd,sFSN;
  AnsiString sPaquete,sHeader,sTail,sProcess,s,sData;
  int nTop,msg;
  int j;
  char *c,car;

  //sComando=sComando.UpperCase(); //mayusculas
  sComando=ChauCaracter(sComando,' '); //quita blancos
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

