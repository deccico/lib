//---------------------------------------------------------------------------


#pragma hdrstop

#include "reporter.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


//---------------------------------------------------------------------------
TReporter::TReporter()
{
    //constantes con la resolución en puntos por pulgada de la impresora predeterminada
    Xppp = GetDeviceCaps(Printer()->Handle, LOGPIXELSX);
    Yppp = GetDeviceCaps(Printer()->Handle, LOGPIXELSY);

    Factor = 1;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//convierte puntos a milímetros en resolución horizontal
float TReporter::P2MM_hor (float points)
{
  return (points / Xppp) * MM;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//convierte puntos a milímetros en resolución vertical
float TReporter::P2MM_ver (float points)
{
  return (points / Yppp) * MM;
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//convierte milímetros a puntos en resolución horizontal
float TReporter::MM2P_hor (float mms)
{
  return (mms / MM) * Xppp * Factor;
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//convierte milímetros a puntos en resolución vertical
float TReporter::MM2P_ver (float mms)
{
  return (mms / MM) * Yppp * Factor;
}
//---------------------------------------------------------------------------
