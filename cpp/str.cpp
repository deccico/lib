//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "str.h"
//---------------------------------------------------------------------------

namespace str_util
{

//---------------------------------------------------------------------------
//reemplaza un caracter por otro en una cadena dada
//sString: cadena a reemplazar
//sBuscar: cadena a buscar
//sReemplazar: cadena que reemplazará la cadena a buscar
AnsiString __fastcall sReemplazar(AnsiString sString, AnsiString sBuscar, AnsiString sReemplazar)
{

	AnsiString sAux;

	for (int i=1; i<sString.Length()+1; i++){
        if ( sString.SubString(i,sBuscar.Length())==sBuscar){
	    	sAux += sReemplazar;
            i += sBuscar.Length() - 1;
        }
        else
	    	sAux += sString.SubString(i,1);
    }

    return sAux;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//verifica si el argumento str es un mail válido
//pre: cadena
//post: true o false según el email es o no válido
bool __fastcall isEmail(AnsiString str)
{
	int j = str.Pos("@"),
    	nP= str.Pos(".");

	if (j  < 2 ||  // la arroba debe estar en la posicion 2 como mínimo
        nP < 2 ||  // el punto debe estar en la posición 2 como mínimo
        str.Length() < 5){	//el largo total del email debe ser de 5 como mínimo
    		return false;
    }
    else
    		return true;	//el email es válido
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//encripta un string, mediante un algoritmo simple de corrimiento
AnsiString sEncriptar(AnsiString str, int c)
{
	AnsiString sCript;
    char *cCar;

	for (int i=1; i<str.Length()+1; i++){
        sCript = str.SubString(i,1);
        cCar = sCript.c_str();
        *cCar += c;
    	sCript = AnsiString(cCar);
     	str = str.SubString(1,i-1) + sCript + str.SubString(i+1,str.Length()-i);
    }
    return str;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//desencripta un string, mediante un algoritmo simple de corrimiento
AnsiString sDesEncriptar(AnsiString str, int c)
{
	AnsiString sCript;
    char *cCar;

	for (int i=1; i<str.Length()+1; i++){
        sCript = str.SubString(i,1);
        cCar = sCript.c_str();
        *cCar -= c;
    	sCript = AnsiString(cCar);
     	str = str.SubString(1,i-1) + sCript + str.SubString(i+1,str.Length()-i);
    }
    return str;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
AnsiString sValidarPorcentaje(AnsiString sStr)
{
    AnsiString s,sIVA = sStr;
    sIVA = sIVA.Trim();

    if (sIVA.Length() > 5)
        sIVA = sIVA.SubString(1,5);
        //sIVA = sIVA.SubString(sIVA.Length()-4,5);

    bool bSep = false;
    for (int i=1; i< sIVA.Length()+1; i++) {
        s = sIVA.SubString(i,1);
        if ((s < "0" || s > "9")) {
            if (!bSep &&  i > 1 && i < sIVA.Length()) {
                s = DecimalSeparator;
                bSep = true;
            }
            else {
                s = "0";
            }
            sIVA = sIVA.SubString(1,i-1) + s + sIVA.SubString(i+1,sIVA.Length());
        }
    }

    sStr = sIVA.ToDouble();
    return sStr;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//verifica la validez del CUIT
bool bEsCuitValido(AnsiString sCuit)
{
 //return true;
    
 int XX=1;
 int suma = 0;
 bool validacion=true ;
 int coc;
 int resto ;
 int Digito_Ver;
 int v3;
    if ((sCuit.Trim().IsEmpty())||(sCuit.SubString(3,1)!="-")||(sCuit.SubString(12,1)!="-"))
        validacion = false;
    else
        {
         for (XX=1;XX<=sCuit.Length();XX++)
         {
                 if ((XX!=3)&&(XX!=12))
                 {
                                 if ((sCuit.SubString(XX,1)<"0")||(sCuit.SubString(XX,1)>"9"))
                                  {
                                   validacion = false;
                                   XX=sCuit.Length();
                                  };
                 };

          };
        };
   if (validacion)
   {
     suma = (sCuit.SubString(1,1)  * 5 +
             sCuit.SubString(2,1)  * 4 +
             sCuit.SubString(4,1)  * 3 +
             sCuit.SubString(5,1)  * 2 +
             sCuit.SubString(6,1)  * 7 +
             sCuit.SubString(7,1)  * 6 +
             sCuit.SubString(8,1)  * 5 +
             sCuit.SubString(9,1)  * 4 +
             sCuit.SubString(10,1) * 3 +
             sCuit.SubString(11,1) * 2);

       coc= suma / 11;
       resto = suma-(coc*11);
       Digito_Ver=StrToInt(sCuit.SubString(13,1));
     if (resto >1)
     {
       resto = 11- resto;
     };
     if (resto!=Digito_Ver)
     {
      return false;
      }
     else
     {
       return true;
     };
   }
   else
   {
    return false;
   };
}
//---------------------------------------------------------------------------

bool RemoveODBCAlias(AnsiString sAlias)

{

    typedef BOOL (__stdcall *pSQLConfigDataSource)(HWND, WORD, LPCSTR, LPCSTR);

    pSQLConfigDataSource SQLConfigDataSource;

    HINSTANCE hLib;

    bool bRet = false;

    hLib = LoadLibrary("odbccp32.dll");

    if (hLib)

    {

        SQLConfigDataSource =

            (pSQLConfigDataSource) GetProcAddress(hLib, "SQLConfigDataSource");

        if (SQLConfigDataSource)

        {

            char szParam[1024];

            sprintf(szParam, "DSN=%s;\0", sAlias.c_str());

            bRet = SQLConfigDataSource(NULL, 3 /*ODBC_REMOVE_DSN*/,

                        "Microsoft Access Driver (*.mdb)", szParam);

        }

        FreeLibrary(hLib);

    }    // Devuelve true si se borra o false en caso contrario

    return bRet;

}
//--------------------------------------------------------------------------------


//---------------------------------------------------------------------------


bool CreateODBCAlias(AnsiString sAlias, AnsiString sDB, AnsiString sDir, AnsiString sDescription)

{

    typedef BOOL (__stdcall *pSQLConfigDataSource)(HWND, WORD, LPCSTR, LPCSTR);

    pSQLConfigDataSource SQLConfigDataSource;

    HINSTANCE hLib;

    bool bRet = false;

    hLib = LoadLibrary("odbccp32.dll");

    if (hLib)

    {

        SQLConfigDataSource =

            (pSQLConfigDataSource) GetProcAddress(hLib, "SQLConfigDataSource");

        if (SQLConfigDataSource)

        {

            char szParam[1024];

            sprintf(szParam, "DSN=%s; Description=%s; DefaultDir=%s; DBQ=%s\0",

                sAlias.c_str(), sDescription.c_str(), sDir.c_str(), sDB.c_str());

            bRet = SQLConfigDataSource(NULL, 1 /*ODBC_ADD_DSN*/,

                        "Microsoft Access Driver (*.mdb)", szParam);

        }

        FreeLibrary(hLib);

    }    // Devuelve true si se crea o false en caso contrario

    return bRet;

}
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//devuelve el nro de campo pedido es un .csv dado
const AnsiString GetCSVField(AnsiString sLinea, int nField=1)
{
    int nCurField = 1;
    AnsiString sResult="";

    for (int i=0; i<sLinea.Length(); i++){
        if (sLinea.SubString(i,1)==",") nCurField++;
        if (nCurField==nField){
            for (int j=i+1; sLinea.SubString(j,1) != "," && j<sLinea.Length(); j++){
                sResult += sLinea.SubString(j,1);
            }
            break;
        }
    }

    return sResult;

}
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//devuelve el nro de campo pedido es un .csv dado
const AnsiString GetCSVField(AnsiString sLinea, AnsiString sSep, int nField=1)
{
    int nCurField = 1;
    AnsiString sResult="";

    for (int i=0; i<sLinea.Length(); i++){
        if (sLinea.SubString(i,1)==sSep) nCurField++;
        if (nCurField==nField){
            for (int j=i+1; sLinea.SubString(j,1) != sSep && j<sLinea.Length(); j++){
                sResult += sLinea.SubString(j,1);
            }
            break;
        }
    }

    return sResult;

}
//------------------------------------------------------------------------------


//---------------------------------------------------------------------------
void Encriptar(char *instr, char *outstr, int size)
{
    int ii;
    for (ii=0; ii<size; ii++) {
        outstr[ii] = instr[ii] ^ ii;
        }
    outstr[size] = NULL;
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
void ToMime64(char *instr, char *outstr, int size)
{
    int ii;
    for (ii=0; ii<size; ii++) {
        outstr[ii] = instr[ii] ^ ii;
        }
    outstr[size] = NULL;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
AnsiString Encomillar(AnsiString s)
{
    return "\"" + s + "\"";    
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
AnsiString __fastcall DameUsuario(const AnsiString &nombre, const AnsiString &apellido)
{
    AnsiString n = nombre.Trim(), a = apellido.Trim();

    n = n.SubString(1,1) + a;
    n = sReemplazar(n," ","_");

    return (n);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
AnsiString __fastcall DameFlotante(AnsiString str)
{
    str = sReemplazar(str, ",", DecimalSeparator);
    str = sReemplazar(str, ".", DecimalSeparator);


    //..valido monto con número flotante correcto
    try{
        str.ToDouble();
    }
    catch(EConvertError &E)
    {
        throw Exception (str + "no es un número decimal válido");
    }

    return str;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
double __fastcall DameFlotanteDec(AnsiString str)
{
    str = sReemplazar(str, ",", DecimalSeparator);
    str = sReemplazar(str, ".", DecimalSeparator);


    //..valido monto con número flotante correcto
    try{
        str.ToDouble();
    }
    catch(EConvertError &E)
    {
        throw Exception (str + "no es un número decimal válido");
    }

    return str.ToDouble();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
AnsiString GenerarTextoAlAzar(int len)
{
    AnsiString resultado;

    randomize();
    for(int i=0; i<len/2; ++i)
        resultado += AnsiString::IntToHex(rand() % 100,2);

    return resultado;
}
//---------------------------------------------------------------------------


AnsiString __fastcall EncriptarConMime64(const AnsiString &text)
{
    int len = text.Length();
    AnsiString ret;

    char *resultado = (char *) malloc(len * 2);
    char *pivote = (char *) malloc(len * 2);
    Encriptar(text.c_str(), pivote, len);
    ToMime64(pivote, resultado, strlen(pivote));

    ret = mEmpaquetar(resultado);

    free(pivote);
    free(resultado);

    return ret;
}
//---------------------------------------------------------------------------

AnsiString __fastcall mEmpaquetar(AnsiString sComando)
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

}
