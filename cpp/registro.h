//---------------------------------------------------------------------------

#ifndef registroH
#define registroH

#define KEYNAMELOCK "SOFTWARE\\MICROSOFT"
#define DATALOCK "Data"

#include <Registry.hpp>


//---------------------------------------------------------------------------


AnsiString sGetRegistryValue(AnsiString sKeyName, AnsiString sValue);
void SetRegistryValue(AnsiString KeyName, AnsiString sValue, AnsiString sDato);

bool __fastcall mTerminar(AnsiString sLimite);

#endif
