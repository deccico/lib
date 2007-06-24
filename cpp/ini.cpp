//---------------------------------------------------------------------------
#pragma hdrstop

#include "ini.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


//---------------------------------------------------------------------------
__fastcall tini::tini()
{
    ini = new TIniFile(ChangeFileExt( Application->ExeName, ".INI"));
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
__fastcall tini::~tini()
{
    delete ini;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
int __fastcall tini::ReadInteger(AnsiString seccion, AnsiString valor, int valor_defecto)
{
    int i = ini->ReadInteger(seccion, valor, valor_defecto);
    ini->WriteInteger(seccion, valor, i);

    return i;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
AnsiString __fastcall tini::LeerString(AnsiString seccion,
                                        AnsiString valor,
                                        AnsiString valor_defecto)
{
    AnsiString s = ini->ReadString(seccion, valor, valor_defecto);
    ini->WriteString(seccion, valor, s);

    return s;
}
//---------------------------------------------------------------------------

