//---------------------------------------------------------------------------
#ifndef strH
#define strH

//---------------------------------------------------------------------------
namespace str_util
{
    AnsiString __fastcall sReemplazar(AnsiString sString, AnsiString sBuscar, AnsiString sReemplazar);
    bool __fastcall isEmail(AnsiString str);
    void __fastcall MostrarPanel(const AnsiString sPanel, const int nT, const int nL, const int nW, const int nH );
    void __fastcall MoverPanel(const AnsiString sPanel, const int nX, const int nY, const int nW, const int nH);
    AnsiString sEncriptar(AnsiString str, int c);
    AnsiString sDesEncriptar(AnsiString str, int c);
    AnsiString sValidarPorcentaje(AnsiString s);
    bool bEsCuitValido(AnsiString sCuit);
    bool CreateODBCAlias(AnsiString sAlias, AnsiString sDB, AnsiString sDir, AnsiString sDescription);
    bool RemoveODBCAlias(AnsiString sAlias);
    const AnsiString GetCSVField(AnsiString sLinea, int nField);
    const AnsiString GetCSVField(AnsiString sLinea, AnsiString sSep, int nField);
    void Encriptar(char *instr, char *outstr, int size);
    void ToMime64(char *instr, char *outstr, int size);
    AnsiString Encomillar(AnsiString s);
    AnsiString __fastcall DameUsuario(const AnsiString &nombre, const AnsiString &apellido);
    AnsiString __fastcall DameFlotante(AnsiString str);
    double __fastcall DameFlotanteDec(AnsiString str);
    AnsiString GenerarTextoAlAzar(int len);
    AnsiString __fastcall EncriptarConMime64(const AnsiString &text);
    AnsiString __fastcall mEmpaquetar(AnsiString sComando);

}

#endif
