//---------------------------------------------------------------------------
#ifndef coloresH
#define coloresH

//---------------------------------------------------------------------------
#define COLORCODES 9


//---------------------------------------------------------------------------
class TColores
{
private:
    // AnsiString sColores[];
public:
	__fastcall TColores(){};

	//convierte el nombre de color de castellano a inglés
    TColor __fastcall Convertir(AnsiString sColor);
};
//---------------------------------------------------------------------------

#endif
