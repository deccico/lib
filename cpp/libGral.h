//Librería de utilidades generales
//---------------------------------------------------------------------------
#ifndef libGralH
#define libGralH
//---------------------------------------------------------------------------

AnsiString __fastcall ChauCaracter(AnsiString sCadena,AnsiString s);
int __fastcall AnsiHexToIntDec(AnsiString sN);
AnsiString __fastcall GetIndice(const AnsiString sOID);
AnsiString __fastcall GetDobleIndice(const AnsiString sOID);
double __fastcall sToDouble(AnsiString sNumber);
int __fastcall StringToInt(AnsiString sNumero);
AnsiString CalculoHora(AnsiString sTimeTicksi, unsigned int nTT0, double nTime0);
AnsiString CharToHexa(AnsiString sValue);
AnsiString __fastcall mEmpaquetar(AnsiString sComando);

//---------------------------------------------------------------------------

#endif

