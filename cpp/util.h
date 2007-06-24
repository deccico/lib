//---------------------------------------------------------------------------
#ifndef utilH
#define utilH

#define SONIDO_EXITO "success.wav"

//---------------------------------------------------------------------------
//Clase con funcionalidades varias
//
//Developed by Adrián Deccico
//Febrero del 2005
//---------------------------------------------------------------------------
//#include <Psock.hpp>
#include <ScktComp.hpp>

#include <Math.hpp>
#include <mmsystem>

//---------------------------------------------------------------------------
class TUtil
{
private:

public:
	__fastcall TUtil(){};

	//espera n Milisegundos
    static void __fastcall Esperar(int nMili);

    //ejecuta una instrucción por la línea de comandos
    static bool __fastcall Ejecutar(AnsiString sCmd, AnsiString sParam);

    static bool __fastcall AddUser(AnsiString sUser, AnsiString sPW,
    AnsiString sUserAdd, AnsiString sUPW, AnsiString sUName, AnsiString sMName,
    AnsiString sLName, AnsiString sUID, AnsiString sGID);

    static void __fastcall ArrastrarDesdeHasta(int desdeX, int desdeY, int hastaX, int hastaY);
    static void __fastcall ClickEn(int x, int y);
    static void __fastcall EscribirNro(int n);
    static void __fastcall EscribirNro2(int n,bool b);
    static void __fastcall ImprimirLineas
    ( TStringList *LINEAS,char *INICIO,char *FIN, char *EJECT,
    AnsiString IMPRESORA, AnsiString TITULO);
    static AnsiString __fastcall IncAlfaNum(AnsiString s);
    static AnsiString __fastcall IncChar(AnsiString sN);
    static  void __fastcall EscribirLetra(AnsiString s);
    static void __fastcall SetNumLock( BOOL bState );
    static void __fastcall SetCapsLock( BOOL bState );
    static AnsiString __fastcall IncrementarNroFact(AnsiString sFact);
    static AnsiString __fastcall GetNumGuionado(AnsiString sNro, int i);
    static AnsiString __fastcall IncLetra(AnsiString sN);
    static int __fastcall sHexToIntDec(AnsiString sN);
    static AnsiString __fastcall GetHoras(double nTiempo, int Formato=0);
    static bool __fastcall Ejecutar(AnsiString sCmd, AnsiString sParam, int nVentana);
    static bool __fastcall Sonar(AnsiString File);
    static void __fastcall RegistrarEnInicio(AnsiString sApp);
    static void __fastcall DesregistrarDeInicio(AnsiString sApp);
    static int WinExecAndWait32(AnsiString FileName, int Visibility);
    static void __fastcall EnviarMensajeMDIChilds(TObject *Sender, UINT msg);
    static void __fastcall SetIniForm(TForm *frm,
                                    AnsiString sSeccion,
                                    bool bChangeHeight,
                                    bool bChangeWidth,
                                    bool bChangeTop,
                                    bool bChangeLeft,
                                    bool bChangeMaximized);
    static void __fastcall SaveIniForm(TForm *frm,
                                    AnsiString sSeccion,
                                    bool bChangeHeight,
                                    bool bChangeWidth,
                                    bool bChangeTop,
                                    bool bChangeLeft,
                                    bool bChangeMaximized);

    //TODO: hacer un template
    static void __fastcall cargar_xywh_controles(TPanel *frm, AnsiString Seccion);
    static void __fastcall guardar_xywh_controles(TPanel *frm, AnsiString Seccion);
    static void __fastcall cargar_xywh_controles(TForm *frm, AnsiString Seccion);
    static void __fastcall guardar_xywh_controles(TForm *frm, AnsiString Seccion);

    static void __fastcall DameResolucionPantalla(int *ancho, int *alto);
    static unsigned long __fastcall DameSizeArchivo(AnsiString file);
    static AnsiString __fastcall DameErrorSocket(TErrorEvent error);
    static bool apagarWindows(int flag = EWX_POWEROFF);


};
//---------------------------------------------------------------------------

#endif
