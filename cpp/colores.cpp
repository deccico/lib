//---------------------------------------------------------------------------
#include <vcl\vcl.h>

#pragma hdrstop

#include "colores.h"
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//recibe el color y devuelve su codigo
TColor __fastcall TColores::Convertir(AnsiString sColor)
{
    AnsiString sCode="";
    TColor colorRet;
    bool bFound = false;

	AnsiString sColores[] = {"VERDE AGUA",
    							"CREMA",
                                "OLIVA",
                                "VERDE AZULADO",
                                "GRIS",
                                "PLATEADO",
                                "LIMA",
                                "AMARILLO",
                                "AGUA",
                                "BLANCO"
    						};

    TColor cl[] = { 0xc0dcc0,  //clMoneyGreen
                    0xf0fbff,   //clCream
                    clOlive,     //0x8080
                    clTeal,  //clTeal
                    clGray,
                    clSilver,
                    clLime,
                    clYellow,
                    clAqua,
                    clWhite
                    };

    sColor = sColor.UpperCase();
    for(int i=0; i<COLORCODES; i++)
    {
    	if (Trim(sColor) == sColores[i])
        {
            bFound=true;
        	colorRet = cl[i];
            break;
        }
    }

    if (!bFound) colorRet = 0xffffff;
    return colorRet;
}
//---------------------------------------------------------------------------


