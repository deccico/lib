//---------------------------------------------------------------------------
#ifndef iniH
#define iniH
//---------------------------------------------------------------------------

//manejo de ini's

//---------------------------------------------------------------------------

#include <vcl.h>
#include <IniFiles.hpp>

//clase que reproduce las funcionalidades de TIniFile
//con el agregado que graba en cada lectura


//---------------------------------------------------------------------------
class tini
{
private:
    TIniFile *ini;

public:
    __fastcall tini();
    __fastcall ~tini();
    AnsiString __fastcall ReadString(AnsiString seccion, AnsiString valor, AnsiString valor_defecto);
    int __fastcall ReadInteger(AnsiString seccion, AnsiString valor, int valor_defecto);
    bool __fastcall ReadBool(AnsiString seccion, AnsiString valor, bool valor_defecto);
};
//---------------------------------------------------------------------------


#endif
