//---------------------------------------------------------------------------
//librería de acceso al registro
//todo, convertir en una clase

#pragma hdrstop

#include "registro.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)



//---------------------------------------------------------------------------
//devuelve el valor del registro indicado
AnsiString sGetRegistryValue(AnsiString KeyName, AnsiString sValue)
{
  AnsiString S;
  TRegistry *Registry = new TRegistry;
  try
  {
    Registry->RootKey = HKEY_LOCAL_MACHINE;
    // false because we do not want to create it if it doesn’t exist
    Registry->OpenKey(KeyName, true);
    S = Registry->ReadString(sValue);
  }
  catch(...)
  {
    delete Registry;
    Registry = NULL;
  }

  if (Registry != NULL)
	  delete Registry;
  return S;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//devuelve el valor del registro indicado
void SetRegistryValue(AnsiString KeyName, AnsiString sValue, AnsiString sDato)
{
  TRegistry *Registry = new TRegistry;
  try
  {
    Registry->RootKey = HKEY_LOCAL_MACHINE;
    // false because we do not want to create it if it doesn’t exist
    Registry->OpenKey(KeyName, true);
    Registry->WriteString(sValue, sDato);
  }
  catch(...)
  {
    delete Registry;
    Registry = NULL;
  }

  if (Registry != NULL)
	  delete Registry;

  return;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
bool __fastcall mTerminar(AnsiString sLimite)
{
    if (sGetRegistryValue(KEYNAMELOCK, DATALOCK)=="031")
      return true;

    AnsiString sHoy;
    sHoy = DateTimeToStr(Date());
    AnsiString S ;
    S = FormatDateTime("yyyymmdd", Now());

    if (S > sLimite){
      SetRegistryValue(KEYNAMELOCK, DATALOCK, "031");
      return true;
    }
    return false;
}
//---------------------------------------------------------------------------


