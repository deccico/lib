//---------------------------------------------------------------------------


#pragma hdrstop

#include "reporter.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


//---------------------------------------------------------------------------
TReporter::TReporter()
{
    //constantes con la resoluci�n en puntos por pulgada de la impresora predeterminada
    Xppp = GetDeviceCaps(Printer()->Handle, LOGPIXELSX);
    Yppp = GetDeviceCaps(Printer()->Handle, LOGPIXELSY);

    Factor = 1;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//convierte puntos a mil�metros en resoluci�n horizontal
float TReporter::P2MM_hor (float points)
{
  return (points / Xppp) * MM;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//convierte puntos a mil�metros en resoluci�n vertical
float TReporter::P2MM_ver (float points)
{
  return (points / Yppp) * MM;
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//convierte mil�metros a puntos en resoluci�n horizontal
float TReporter::MM2P_hor (float mms)
{
  return (mms / MM) * Xppp * Factor;
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//convierte mil�metros a puntos en resoluci�n vertical
float TReporter::MM2P_ver (float mms)
{
  return (mms / MM) * Yppp * Factor;
}
//---------------------------------------------------------------------------
