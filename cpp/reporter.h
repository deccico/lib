//---------------------------------------------------------------------------

#ifndef reporterH
#define reporterH

#define MM 25.4

#include <Printers.hpp>

//---------------------------------------------------------------------------
class TReporter
{
private:
    //constantes con la resolución en puntos por pulgada de la impresora predeterminada
    float Xppp;
    float Yppp;
    int Factor; 

public:
    TReporter();

    //convierte puntos a milímetros en resolución horizontal
    float P2MM_hor (float points);

    //convierte puntos a milímetros en resolución vertical
    float P2MM_ver (float points);

    //convierte milímetros a puntos en resolución horizontal
    float MM2P_hor (float mms);

    //convierte milímetros a puntos en resolución vertical
    float MM2P_ver (float mms);

};

#endif
