//---------------------------------------------------------------------------

#ifndef reporterH
#define reporterH

#define MM 25.4

#include <Printers.hpp>

//---------------------------------------------------------------------------
class TReporter
{
private:
    //constantes con la resoluci�n en puntos por pulgada de la impresora predeterminada
    float Xppp;
    float Yppp;
    int Factor; 

public:
    TReporter();

    //convierte puntos a mil�metros en resoluci�n horizontal
    float P2MM_hor (float points);

    //convierte puntos a mil�metros en resoluci�n vertical
    float P2MM_ver (float points);

    //convierte mil�metros a puntos en resoluci�n horizontal
    float MM2P_hor (float mms);

    //convierte mil�metros a puntos en resoluci�n vertical
    float MM2P_ver (float mms);

};

#endif
