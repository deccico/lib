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
AnsiString __fastcall tini::ReadString(AnsiString seccion,
                                        AnsiString valor,
                                        AnsiString valor_defecto)
{
    AnsiString s = ini->ReadString(seccion, valor, valor_defecto);
    ini->WriteString(seccion, valor, s);

    return s;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
bool __fastcall tini::ReadBool(AnsiString seccion,
                                        AnsiString valor,
                                        bool valor_defecto)
{
    bool r = ini->ReadBool(seccion, valor, valor_defecto);
    ini->WriteBool(seccion, valor, r);

    return r;
}
//---------------------------------------------------------------------------

