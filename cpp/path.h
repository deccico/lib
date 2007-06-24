/*
	libreria con utilidades de path y cadenas

    by Adrian Deccico
*/

//---------------------------------------------------------------------------
#ifndef pathH
#define pathH
//---------------------------------------------------------------------------


AnsiString __fastcall sPathToDoubleSlash(AnsiString sPath);
AnsiString __fastcall sSinExtension(AnsiString sName);
AnsiString __fastcall CambiarExtension(AnsiString sFileName, AnsiString sExt);
AnsiString __fastcall AppendNombre(AnsiString sFileName, AnsiString sAddFileName);

//---------------------------------------------------------------------------
#endif
