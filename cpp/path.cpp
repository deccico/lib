//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "path.h"
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//convierte un path de simple a doble slash
//pre c:\archivo.txt
//post c:\\archivo.txt
AnsiString __fastcall sPathToDoubleSlash(AnsiString sPath)
{
	AnsiString sAux;

	for (int i=1; i<sPath.Length()+1; i++){
    	sAux += sPath.SubString(i,1);
        if ( sPath.SubString(i,1)=='/' || sPath.SubString(i,1)=="\\" )
	    	sAux += sPath.SubString(i,1);
    }

    return sAux;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
AnsiString __fastcall sSinExtension(AnsiString sName)
{
 	int j = sName.Pos(".");
    if (j==0) j = sName.Length()+1;
    sName =  sName.SubString(1,j-1);

    return sName;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//cambia la extension de un archivo
AnsiString __fastcall CambiarExtension(AnsiString sFileName, AnsiString sExt)
{
    sFileName = sSinExtension(sFileName);
    sFileName += sExt;

    return sFileName;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//agrega caracteres al nombre de un archivo conservando su extension
AnsiString __fastcall AppendNombre(AnsiString sFileName, AnsiString sAddFileName)
{
    AnsiString sExt, sNombre = sSinExtension(sFileName);

    sExt =ExtractFileExt(sFileName);

    sNombre += sAddFileName;

    //sNombre += sFileName.SubString(sNombre.Length(), sFileName.Length() - sNombre.Length() +1);
    sNombre += sExt;

    return sNombre;


}
//---------------------------------------------------------------------------

