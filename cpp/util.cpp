//---------------------------------------------------------------------------
#include <vcl\vcl.h>

#pragma hdrstop

#include "util.h"
#include "registro.h"

#include <iostream.h>
#include <fstream.h>
#include <set>
#include <memory>
using namespace std;

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TUtil::Esperar (int nMili)
{
    DWORD TiempoEntrada=GetTickCount();
    do;
    while((GetTickCount()-TiempoEntrada)<((unsigned)nMili));}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//ejecuta una instrucción por la línea de comandos
//devuelve true si la instrucción se corró correctamente
bool __fastcall TUtil::Ejecutar(AnsiString sCmd, AnsiString sParam, int nVentana)
{

    HINSTANCE hi = ShellExecute(0, "open", sCmd.c_str(), sParam.c_str(), "", nVentana);  //SW_HIDE
    int ni = (int) hi;
    AnsiString sMsg;
    bool bFallo = false;

    switch (ni) {
    case 0:	sMsg = "El sistema operativo posee pocos recursos o poca memoria.";
            bFallo=true; break;
    case ERROR_FILE_NOT_FOUND: sMsg = "No se encontró el archivo especificado.";
            bFallo=true; break;
    case ERROR_PATH_NOT_FOUND: sMsg = "No se encontró el path (camino) especificado.";
            bFallo=true; break;
    case ERROR_BAD_FORMAT: sMsg = "El archivo .EXE es inválido (no es un archivo Win32 .EXE o existe un error dentro del .EXE).";
            bFallo=true; break;
    case SE_ERR_ACCESSDENIED: sMsg = "El sistema operativo ha negado el acceso al archivo especificado.";
            bFallo=true; break;
    case SE_ERR_ASSOCINCOMPLETE: sMsg = "La asociación del nombre del archivo está incompleta o bien es inválida.";
            bFallo=true; break;
    case SE_ERR_DDEBUSY: sMsg = "La transacción DDE no pudo ser completada porque otras transacciones se estuvieron procesando al mismo tiempo.";
            bFallo=true; break;
    case SE_ERR_DDEFAIL: sMsg = "Falló la transacción DDE.";
            bFallo=true; break;
    case SE_ERR_DDETIMEOUT: sMsg = "La transacción DDE no pudo ser completada porque se agotó el tiempo de espera.";
            bFallo=true; break;
    case SE_ERR_DLLNOTFOUND: sMsg = "La librería de enlace-dinámico especificada no pudo ser encontrada.";
            bFallo=true; break;
    //case SE_ERR_FNF: sMsg = "The specified file was not found.";
      //      bFallo=true; break;
    case SE_ERR_NOASSOC: sMsg = "No hay ninguna aplicación asociada a la extensión dada.";
            bFallo=true; break;
    case SE_ERR_OOM: sMsg = "No hay suficiente memoria para completar la operación.";
            bFallo=true; break;
    //case SE_ERR_PNF: sMsg = "The specified path was not found.";
      //      bFallo=true; break;
    case SE_ERR_SHARE: sMsg = "Ha ocurrido una violación de recursos compartidos.";
            bFallo=true; break;
    }

    if (bFallo) {
        sMsg = "Error ejecutando " + sCmd + " " + sParam + " " + sMsg;
        throw Exception(sMsg);
    }

    if (!bFallo && ni <= 32)
        throw Exception ("Fallo Desconocido ejecutando la instrucción " + sCmd + " " + sParam);

    return true;

}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//ejecuta una instrucción por la línea de comandos
//devuelve true si la instrucción se corró correctamente
bool __fastcall TUtil::Ejecutar(AnsiString sCmd, AnsiString sParam)
{

    HINSTANCE hi = ShellExecute(0, "open", sCmd.c_str(), sParam.c_str(), "",SW_HIDE);  //SW_SHOWDEFAULT
    int ni = (int) hi;
    AnsiString sMsg;
    bool bFallo = false;

    switch (ni) {
    case 0:	sMsg = "El sistema operativo posee pocos recursos o poca memoria.";
            bFallo=true; break;
    case ERROR_FILE_NOT_FOUND: sMsg = "No se encontró el archivo especificado.";
            bFallo=true; break;
    case ERROR_PATH_NOT_FOUND: sMsg = "No se encontró el path (camino) especificado.";
            bFallo=true; break;
    case ERROR_BAD_FORMAT: sMsg = "El archivo .EXE es inválido (no es un archivo Win32 .EXE o existe un error dentro del .EXE).";
            bFallo=true; break;
    case SE_ERR_ACCESSDENIED: sMsg = "El sistema operativo ha negado el acceso al archivo especificado.";
            bFallo=true; break;
    case SE_ERR_ASSOCINCOMPLETE: sMsg = "La asociación del nombre del archivo está incompleta o bien es inválida.";
            bFallo=true; break;
    case SE_ERR_DDEBUSY: sMsg = "La transacción DDE no pudo ser completada porque otras transacciones se estuvieron procesando al mismo tiempo.";
            bFallo=true; break;
    case SE_ERR_DDEFAIL: sMsg = "Falló la transacción DDE.";
            bFallo=true; break;
    case SE_ERR_DDETIMEOUT: sMsg = "La transacción DDE no pudo ser completada porque se agotó el tiempo de espera.";
            bFallo=true; break;
    case SE_ERR_DLLNOTFOUND: sMsg = "La librería de enlace-dinámico especificada no pudo ser encontrada.";
            bFallo=true; break;
    //case SE_ERR_FNF: sMsg = "The specified file was not found.";
      //      bFallo=true; break;
    case SE_ERR_NOASSOC: sMsg = "No hay ninguna aplicación asociada a la extensión dada.";
            bFallo=true; break;
    case SE_ERR_OOM: sMsg = "No hay suficiente memoria para completar la operación.";
            bFallo=true; break;
    //case SE_ERR_PNF: sMsg = "The specified path was not found.";
      //      bFallo=true; break;
    case SE_ERR_SHARE: sMsg = "Ha ocurrido una violación de recursos compartidos.";
            bFallo=true; break;
    }

    if (bFallo) {
        sMsg = "Error ejecutando " + sCmd + " " + sParam + " " + sMsg;
        throw Exception(sMsg);
    }

    if (!bFallo && ni <= 32)
        throw Exception ("Fallo Desconocido ejecutando la instrucción " + sCmd + " " + sParam);

    return true;

}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//agrega un user Firebird usando GSEC
bool __fastcall TUtil::AddUser(AnsiString sUser, AnsiString sPW,
    AnsiString sUserAdd, AnsiString sUPW, AnsiString sUName, AnsiString sMName,
    AnsiString sLName, AnsiString sUID, AnsiString sGID)
{
    const AnsiString KEYNAME = "SOFTWARE\\Firebird Project\\Firebird Server\\Instances";
    const AnsiString DATA = "DefaultInstance";
    AnsiString sGsec, sParam;

    sGsec = sGetRegistryValue(KEYNAME, DATA);
    sGsec += "bin\\gsec.exe";
    sParam = " -user " + sUser + " -password " + sPW + " -add " + sUserAdd;
    sParam += " -pw " + sUPW + " -fname " + sUName + " -mname " +sMName;
    sParam += " -lname " + sLName + " -uid " + sUID + " -gid " + sGID;

    if (TUtil::Ejecutar(sGsec, sParam))
        return true;

    return false;

}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TUtil::ArrastrarDesdeHasta(int desdeX, int desdeY, int hastaX, int hastaY)
{
    // Mover el cursor hasta las coordenadas (desdeX,desdeY)
    // y pulsar el botón izquierdo
    mouse_event(MOUSEEVENTF_LEFTDOWN
        | MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE,
        MulDiv(desdeX, 65535, Screen->Width - 1),
        MulDiv(desdeY, 65535, Screen->Height - 1),
        0, 0);

    // Mover el cursor hasta las coordenadas (hastaX,hastaY)
    // y _soltar_ el botón izquierdo
    mouse_event(MOUSEEVENTF_LEFTUP
        | MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE,
        MulDiv(hastaX, 65535, Screen->Width - 1),
        MulDiv(hastaY, 65535, Screen->Height - 1),
        0, 0);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TUtil::ClickEn(int x, int y)
{
      mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP
          | MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE,
          MulDiv(x, 65535, Screen->Width - 1),
          MulDiv(y, 65535, Screen->Height - 1),
          0, 0);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//recibe un número y lo escribe por teclado. La doble escritura permite la
//llamada de esta función en un ciclo sin que importe la velocidad de escritura
//pre el nro debe ser de 0 a 9  en otro caso escribe 0
//post escribe el nro por teclado
void __fastcall TUtil::EscribirNro(int n)
{
    static int nLast[2];
    int i;
    BYTE num;

    if (n < 0 || n > 9)
        n = 0;

    /*
    switch (n){
    case 0:
            i=0;
            if (nLast[0] == i){
                if (nLast[1] == VK_NUMPAD0)
                    num = 0x30;
                else
                    num = VK_NUMPAD0;
            }
            else
                num = 0x30;
            break;
    */


    switch (n){
    case 0:
            num = 0x30;
            break;
    case 1:
            num = 0x31;
            break;
    case 2:
            num = 0x32;
            break;
    case 3:
            num = 0x33;
            break;
    case 4:
            num = 0x34;
            break;
    case 5:
            num = 0x35;
            break;
    case 6:
            num = 0x36;
            break;
    case 7:
            num = 0x37;
            break;
    case 8:
            num = 0x38;
            break;
    case 9:
            num = 0x39;
            break;
    default:  //esto no debería ocurrir
            num = 0x30;
            break;
    }

    keybd_event(num,0,0,0);
    //keybd_event(num,0,KEYEVENTF_KEYUP,0);
    nLast[0] = i;
    nLast[1] = num;

}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//idem EscribirNro con la posibilidad de escribir un código distinto usando
//el 2do parámetro
void __fastcall TUtil::EscribirNro2(int n,bool b)
{
    //static int nLast[2];
    int i;
    BYTE num;

    if (n < 0 || n > 9)
        n = 0;
    switch (n){
    case 0:
            if (b)  num = 0x30;
            else    num = VK_NUMPAD0;
            break;
    case 1:
            if (b)  num = 0x31;
            else    num = VK_NUMPAD1;
            break;
    case 2:
            if (b)  num = 0x32;
            else    num = VK_NUMPAD2;
            break;
    case 3:
            if (b)  num = 0x33;
            else    num = VK_NUMPAD3;
            break;
    case 4:
            if (b)  num = 0x34;
            else    num = VK_NUMPAD4;
            break;
    case 5:
            if (b)  num = 0x35;
            else    num = VK_NUMPAD5;
            break;
    case 6:
            if (b)  num = 0x36;
            else    num = VK_NUMPAD6;
            break;
    case 7:
            if (b)  num = 0x37;
            else    num = VK_NUMPAD7;
            break;
    case 8:
            if (b)  num = 0x38;
            else    num = VK_NUMPAD8;
            break;
    case 9:
            if (b)  num = 0x39;
            else    num = VK_NUMPAD9;
            break;
    default:  //esto no debería ocurrir
            if (b)  num = 0x30;
            else    num = VK_NUMPAD0;
            break;
    }

    keybd_event(num,0,0,0);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TUtil::EscribirLetra(AnsiString s)
{
    s = s.SubString(1,1);
    BYTE num;

    if (s=="A")        num=0x41;
    else if (s=="B")   num=0x42;
    else if (s=="C")   num=0x43;
    else if (s=="D")   num=0x44;
    else if (s=="E")   num=0x45;
    else if (s=="F")   num=0x46;
    else if (s=="G")   num=0x47;
    else if (s=="H")   num=0x48;
    else if (s=="I")   num=0x49;
    else if (s=="J")   num=0x4A;
    else if (s=="K")   num=0x4B;
    else if (s=="L")   num=0x4C;
    else if (s=="M")   num=0x4D;
    else if (s=="N")   num=0x4E;
    else if (s=="O")   num=0x4F;
    else if (s=="P")   num=0x50;
    else if (s=="Q")   num=0x51;
    else if (s=="R")   num=0x52;
    else if (s=="S")   num=0x53;
    else if (s=="T")   num=0x54;
    else if (s=="U")   num=0x55;
    else if (s=="V")   num=0x56;
    else if (s=="W")   num=0x57;
    else if (s=="X")   num=0x58;
    else if (s=="Y")   num=0x59;
    else if (s=="Z")   num=0x5A;

    // Simulate a key press
     keybd_event( num,
                      0,
                      KEYEVENTF_EXTENDEDKEY | 0,
                      0 );

    // Simulate a key release
     keybd_event( num,
                      0,
                      KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                      0);

}
//---------------------------------------------------------------------------


//-----------------------------------------------------------------------------
////////////Impresion EN MODO TEXTO PARA EVITAR EL SPOOLER DE WINDOW
//          PARA IMPRESORAS DE MATRIZ TAMBIEN SIRVE PARA IMPRESORA FISCAL
//          O MINIPRINTER
// REALIZADA POR:
//               CESAR CUAUHTEMOC SALAZAR GONZALEZ.
//               06/04/04, ESPERO LES SIRVA..
//
// LINEAS    ->lo que se desea imprimir, ARREGLO DE LINEAS.
// INICIO    -> HABILITAR TIPO LETRAS EN MATRIZ, "\xF"-CONDENSADO "\xE"-EXPAND
// FIN       -> DESHABILITAR TIPO LETRAS "\X12" IMPRESION NORMAL
// EJECT     -> EXPULSAR HOJA O PONER MAS LINEAS "\xC"-EXPL "\N\N\N"-MAS LINEAS
// IMPRESORA -> A DONDE? LOCAL "EPSON" O RED "\\EPSON" // BAJO WINDOS.
// TITULO    -> TITULO DE IMPRESION.
//
// POR EJEMPLO
//    TStringList* MyList = new TStringList();
//    MyList->AddStrings(this->Memo1->Lines);
//    ImprimirLineas(MyList,"\xF","\x12","\xC","HP DeskJet 420","PRUEBA");
//----------
// ANEXO ("\x0d\x0a" Fin y nueva linea)
////////////////////////////////////////////////////////////////////////////
void __fastcall TUtil::ImprimirLineas( TStringList *LINEAS,char *INICIO,char *FIN,
                                       char *EJECT,AnsiString IMPRESORA,
                                       AnsiString TITULO)
{
    struct {
        char *DocName;
        char *OutputFile;
        char *DataType;
    } DocInfo;
    DocInfo.DocName     = TITULO.c_str();
    DocInfo.OutputFile  = 0;
    DocInfo.DataType    = "RAW";
    // Obtener un handle de impresora
    HANDLE hPrinter;
    if (! OpenPrinter(IMPRESORA.c_str(), &hPrinter, 0))
        throw Exception("No se encuentra la impresora");
    try {
        // Informar al spooler del comienzo de impresión
        if (StartDocPrinter(hPrinter, 1, LPBYTE(&DocInfo)) == 0)
            throw Exception("Operación inválida con la impresora");
        try {
            // Iniciar una página
            if (! StartPagePrinter(hPrinter))
                throw Exception("<StartPage> Operación inválida con la impresora");
            try {
                // Enviar los datos directamente
///////////////////////
                  // PREPARAR LA ULTIMA LINEA
                   for(int i=0;i < LINEAS->Count;i++){
                                        // INICIO CADENA           \R\N      FIN
                       AnsiString vLinea=INICIO+LINEAS->Strings[i]+FIN+"\x0d\x0a";
                       char* lineToPrint;
                       DWORD numBytesWritten;
                       lineToPrint=vLinea.c_str(); // convertir linea a cadena
                       WritePrinter(hPrinter,(LPVOID)lineToPrint,(DWORD) strlen(lineToPrint), &numBytesWritten);
                 }
                 char* lineToPrint;
                 DWORD numBytesWritten;
                 lineToPrint=EJECT; // si lleva se expulas "\xC"
                 WritePrinter(hPrinter,(LPVOID)lineToPrint,(DWORD) strlen(lineToPrint), &numBytesWritten);

////////////////////
            }
            __finally {
                // Terminar la página
                if (! EndPagePrinter(hPrinter))
                    throw Exception("<EndPage> Operación inválida con la impresora");
            }
        }
        __finally {
            // Informar al spooler del fin de impresión
            if (! EndDocPrinter(hPrinter))
            throw Exception("<EndDoc> Operación inválida con la impresora");
        }
    }
    __finally {
        // Devolver el handle de impresora
        ClosePrinter(hPrinter);
    }
}

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//incrementa un numero alfanumerico por ej 1AA => 1AB
AnsiString __fastcall TUtil::IncAlfaNum(AnsiString sN)
{
    AnsiString s;
    const AnsiString LAST="A";

    for (int i=sN.Length(); i>0; i--){
        s = sN.SubString(i,1);
        if (i > 1)
            s = IncLetra(s);
        else
            s = IncChar(s);
        sN.Insert(s,i);
        sN.Delete(i+1,1);
        if (i > 1 &&  s != LAST)
            break;
        else if (i == 1 && s != "0")
            break;
    }

    return sN;

}
//---------------------------------------------------------------------------


//-----------------------------------
AnsiString __fastcall TUtil::IncChar(AnsiString sN)
{
    if (sN      == "0")
        return "1";
    else if (sN == "1")
        return "2";
    else if (sN == "2")
        return "3";
    else if (sN == "3")
        return "4";
    else if (sN == "4")
        return "5";
    else if (sN == "5")
        return "6";
    else if (sN == "6")
        return "7";
    else if (sN == "7")
        return "8";
    else if (sN == "8")
        return "9";
    else if (sN == "9")
        return "A";
    else if (sN == "A")
        return "B";
    else if (sN == "B")
        return "C";
    else if (sN == "C")
        return "D";
    else if (sN == "D")
        return "E";
    else if (sN == "E")
        return "F";
    else if (sN == "F")
        return "G";
    else if (sN == "G")
        return "H";
    else if (sN == "H")
        return "I";
    else if (sN == "I")
        return "J";
    else if (sN == "J")
        return "K";
    else if (sN == "K")
        return "L";
    else if (sN == "L")
        return "M";
    else if (sN == "M")
        return "N";
    else if (sN == "N")
        return "O";
    else if (sN == "O")
        return "P";
    else if (sN == "P")
        return "Q";
    else if (sN == "Q")
        return "R";
    else if (sN == "R")
        return "S";
    else if (sN == "S")
        return "T";
    else if (sN == "T")
        return "U";
    else if (sN == "U")
        return "V";
    else if (sN == "V")
        return "W";
    else if (sN == "W")
        return "X";
    else if (sN == "X")
        return "Y";
    else if (sN == "Y")
        return "Z";
    else if (sN == "Z")
        return "0";
    else
        return "0";

}
//-----------------------------------

//-----------------------------------
AnsiString __fastcall TUtil::IncLetra(AnsiString sN)
{
    if (sN      == "0")
        return "A";
    else if (sN == "1")
        return "A";
    else if (sN == "2")
        return "A";
    else if (sN == "3")
        return "A";
    else if (sN == "4")
        return "A";
    else if (sN == "5")
        return "A";
    else if (sN == "6")
        return "A";
    else if (sN == "7")
        return "A";
    else if (sN == "8")
        return "A";
    else if (sN == "9")
        return "A";
    else if (sN == "A")
        return "B";
    else if (sN == "B")
        return "C";
    else if (sN == "C")
        return "D";
    else if (sN == "D")
        return "E";
    else if (sN == "E")
        return "F";
    else if (sN == "F")
        return "G";
    else if (sN == "G")
        return "H";
    else if (sN == "H")
        return "I";
    else if (sN == "I")
        return "J";
    else if (sN == "J")
        return "K";
    else if (sN == "K")
        return "L";
    else if (sN == "L")
        return "M";
    else if (sN == "M")
        return "N";
    else if (sN == "N")
        return "O";
    else if (sN == "O")
        return "P";
    else if (sN == "P")
        return "Q";
    else if (sN == "Q")
        return "R";
    else if (sN == "R")
        return "S";
    else if (sN == "S")
        return "T";
    else if (sN == "T")
        return "U";
    else if (sN == "U")
        return "V";
    else if (sN == "V")
        return "W";
    else if (sN == "W")
        return "X";
    else if (sN == "X")
        return "Y";
    else if (sN == "Y")
        return "Z";
    else if (sN == "Z")
        return "A";
    else
        return "0";

}
//-----------------------------------


//-----------------------------------
 void __fastcall TUtil::SetNumLock( BOOL bState )
   {
      BYTE keyState[256];

      GetKeyboardState((LPBYTE)&keyState);
      if( (bState && !(keyState[VK_NUMLOCK] & 1)) ||
          (!bState && (keyState[VK_NUMLOCK] & 1)) )
      {
      // Simulate a key press
         keybd_event( VK_NUMLOCK,
                      0x45,
                      KEYEVENTF_EXTENDEDKEY | 0,
                      0 );

      // Simulate a key release
         keybd_event( VK_NUMLOCK,
                      0x45,
                      KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                      0);
      }
   }
//-----------------------------------------------------

//-----------------------------------------------------
 void __fastcall TUtil::SetCapsLock( BOOL bState )
   {
      BYTE keyState[256];

      GetKeyboardState((LPBYTE)&keyState);
      if( (bState && !(keyState[VK_CAPITAL] & 1)) ||
          (!bState && (keyState[VK_CAPITAL] & 1)) )
      {
      // Simulate a key press
         keybd_event( VK_CAPITAL,
                      0x45,
                      KEYEVENTF_EXTENDEDKEY | 0,
                      0 );

      // Simulate a key release
         keybd_event( VK_CAPITAL,
                      0x45,
                      KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                      0);
      }
   }
//-----------------------------------------------------


//---------------------------------------------------------------------------
//incrementa el nro de una factura
AnsiString __fastcall TUtil::IncrementarNroFact(AnsiString sFact)
{
    /* TODO -cfacturacion : modificar para incrementar primeros cuatro numeros */

    const int nLen=8;
    AnsiString sCeros = "00000000", sAux;
    const AnsiString sBlank = "0000-00000000";
    int nPos = sFact.Pos("-");
    unsigned long nFact;

    if (sFact.IsEmpty())
        return sBlank;

    if (nPos == 0) nPos = 5;

    try {
        nFact = sFact.SubString(nPos+1,sFact.Length()).ToDouble() + 1;
    }
    catch (...)
    {
        nFact = 0;
    }

    sAux = AnsiString(nFact);

    sFact = sFact.SubString(1,nPos) + sCeros.SubString(1, nLen - sAux.Length()) + sAux;

    return sFact;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
AnsiString __fastcall TUtil::GetNumGuionado(AnsiString sNro, int i)
{
/* TODO: agregar validaciones y que funciones para otros casos*/

    bool EsNegativo=false;
    AnsiString s;

    if (sNro.SubString(1,1) == "-"){
        EsNegativo = true;
        sNro.Delete(1,1);
    }

    int n = sNro.Pos("-");

    switch (i)
    {
      case 1: s = sNro.SubString(1,n-1);
              if (EsNegativo)
                s = "-" + s;
              break;
      case 2: s = sNro.SubString(n+1,sNro.Length());
              break;
      default: s = "-1";
    }


    return s;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//convierte un AnsiString con valor en hexadecimal a su valor en entero
int __fastcall TUtil::sHexToIntDec(AnsiString sN)
{
        AnsiString scar,snum=sN;
        unsigned int nnumero=0;
        int expo,num=0,nlong=snum.Length();
        snum=snum.UpperCase();

        for(int i=1;i<=nlong;i++)
        {
          scar=snum[i];
          if (scar >= '0' && scar <= '9') snum[i]='0';
          switch (snum[i])
          {
                case 'A' : num=10;break;
                case 'B' : num=11;break;
                case 'C' : num=12;break;
                case 'D' : num=13;break;
                case 'E' : num=14;break;
                case 'F' : num=15;break;
                case '0' : num=scar.ToInt();break;
          }
          expo=nlong-i;
          nnumero=nnumero+num*(IntPower(16,expo));
        }//fin For

        return nnumero;
}
//--fin AnsiIntToHex----------------------------------------------------



//----------------------------------------------------------------------
//dado un TDateTime devuelve hh:mm
//Formato = 0 devuelve hh mm ss
//formato = 1 deveulve n minutos
//formato = 2 devuelve n horas
AnsiString __fastcall TUtil::GetHoras(double nTiempo, int Formato)
{
    int nInt;
    double nFrac;
    int nH=0,nM=0,nS=0;

    //obtengo horas de días
    nInt = Floor(nTiempo);  //días totales
    nFrac = (double) nTiempo - nInt; //horas restantes
    nH = nInt * 24; //obtiene las horas


    //obtengo horas de la parte decimal
    nFrac = nFrac * 24;
    nInt = Floor(nFrac);
    nFrac = (double) nFrac - nInt;
    nH += nInt;
    nM = nFrac * 60;

    //segundos
    nInt = Floor(nFrac * 60);
    nFrac = (double) (nFrac * 60) - nInt;
    nS = Ceil(nFrac * 60);

    AnsiString Return;
    double ret;

    switch (Formato)
    {
    case 0:
            Return = AnsiString(nH) + " hs " + AnsiString(nM) + " min " + AnsiString(nS) + " sec";
            break;
    case 1:
            Return = FormatFloat("0.00",(nH * 60.0) + (double) nM + ((double)nS /(60.0)));
            break;
    case 2:
            Return = FormatFloat("0.00",(double)nH + ((double) nM / 60.0) + (nS /(60.0 * 60.0)));
            break;
    default:
            throw Exception("Formato desconocido");
    }

    return (Return);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
//ejecuta un sonido dado por File
bool __fastcall TUtil::Sonar(AnsiString File)
{
    if (!FileExists(File))
        return false;

    bool b = PlaySound( File.c_str(), NULL, SND_ASYNC );

    return b;
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
void __fastcall TUtil::RegistrarEnInicio(AnsiString sApp)
{
 TRegistry *R = new TRegistry;
 if (R->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run", true))
    R->WriteString(sApp, Application->ExeName);
 delete R;
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
void __fastcall TUtil::DesregistrarDeInicio(AnsiString sApp)
{
 TRegistry *R = new TRegistry;
 if (R->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run", false))
    R->DeleteValue(sApp);
 delete R;
}
//----------------------------------------------------------------------


//---------------------------------------------------------------------------
//Envía un mensaje a todos los MDI childs de una aplicación (menos al origen)
void __fastcall TUtil::EnviarMensajeMDIChilds(TObject *Sender, UINT msg)
{
    for (int i = 0; i < Forms::Screen->FormCount; i++)
    {
       Forms::TForm *pHijo = Forms::Screen->Forms[i];
       if (Sender != pHijo)
       {
          ::SendMessage(pHijo->Handle, msg, 0, 0L);
       }
    }

}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TUtil::SetIniForm(TForm *frm,
                                    AnsiString sSeccion,
                                    bool bChangeHeight,
                                    bool bChangeWidth,
                                    bool bChangeTop,
                                    bool bChangeLeft,
                                    bool bChangeMaximized)
{
    TIniFile *ini;
    ini = new TIniFile( ChangeFileExt( Application->ExeName, ".INI" ) );

    frm = dynamic_cast <TForm*> (frm);
    AnsiString sName = sSeccion.IsEmpty()?frm->Caption:sSeccion;

    if (bChangeHeight)
        frm->Height = ini->ReadInteger( sName, "Height", 100 );

    if (bChangeWidth)
        frm->Width = ini->ReadInteger( sName, "Width", 100 );

    if (bChangeTop)
        frm->Top = ini->ReadInteger( sName, "Top", 100 );

    if (bChangeLeft)
        frm->Left = ini->ReadInteger( sName, "Left", 100 );

    if (bChangeMaximized)
        frm->WindowState = ini->ReadBool( sName, "Maximized", false)?wsMaximized:wsNormal;

    delete ini;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TUtil::SaveIniForm(TForm *frm,
                                    AnsiString sSeccion,
                                    bool bChangeHeight,
                                    bool bChangeWidth,
                                    bool bChangeTop,
                                    bool bChangeLeft,
                                    bool bChangeMaximized)
{
    TIniFile *ini;
    ini = new TIniFile( ChangeFileExt( Application->ExeName, ".INI" ) );

    frm = dynamic_cast <TForm*> (frm);
    AnsiString sName = sSeccion.IsEmpty()?frm->Caption:sSeccion;

    if (bChangeHeight)
        ini->WriteInteger( sName, "Height", frm->Height);

    if (bChangeWidth)
        ini->WriteInteger( sName, "Width", frm->Width);

    if (bChangeTop)
        ini->WriteInteger( sName, "Top", frm->Top);

    if (bChangeLeft)
        ini->WriteInteger( sName, "Left", frm->Left);

    if (bChangeMaximized)
        ini->WriteBool( sName, "Maximized",frm->WindowState == wsMaximized);


    delete ini;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TUtil::guardar_xywh_controles(TPanel *frm, AnsiString Seccion)
{
    auto_ptr<TIniFile> ini(new TIniFile(ChangeFileExt(Application->ExeName, ".INI")));

    AnsiString NombreControl;
    int valor;
    TControl *ctrl;
    set<AnsiString> tipos_permitidos;

    tipos_permitidos.insert("TButton");
    tipos_permitidos.insert("TBitBtn");
    tipos_permitidos.insert("TSpeedButton");
    tipos_permitidos.insert("TImage");
    tipos_permitidos.insert("TPanel");
    tipos_permitidos.insert("TMemo");
    tipos_permitidos.insert("TStaticText");
    tipos_permitidos.insert("TLabel");


    for(int i=0;i < frm->ComponentCount;i++)
    {
        ctrl = static_cast <TControl*> (frm->Components[i]);

        if (tipos_permitidos.find(AnsiString(ctrl->ClassName())) == tipos_permitidos.end())
            continue;

        //TOP
        NombreControl = ctrl->Name + "_Top";
        valor = ctrl->Top;
        ini->WriteInteger(Seccion, NombreControl, valor);
        //LEFT
        NombreControl = ctrl->Name + "_Left";
        valor = ctrl->Left;
        ini->WriteInteger(Seccion, NombreControl, valor);
        //Width
        NombreControl = ctrl->Name + "_Width";
        valor = ctrl->Width;
        ini->WriteInteger(Seccion, NombreControl, valor);
        //Height
        NombreControl = ctrl->Name + "_Height";
        valor = ctrl->Height;
        ini->WriteInteger(Seccion, NombreControl, valor);
    }

}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
void __fastcall TUtil::cargar_xywh_controles(TPanel *frm, AnsiString Seccion)
{
    auto_ptr<TIniFile> ini(new TIniFile(ChangeFileExt(Application->ExeName, ".INI")));

    TControl *ctrl;
    set<AnsiString> tipos_permitidos;

    tipos_permitidos.insert("TButton");
    tipos_permitidos.insert("TBitBtn");
    tipos_permitidos.insert("TSpeedButton");
    tipos_permitidos.insert("TImage");
    tipos_permitidos.insert("TPanel");
    tipos_permitidos.insert("TMemo");
    tipos_permitidos.insert("TStaticText");
    tipos_permitidos.insert("TLabel");

    for(int i=0;i < frm->ControlCount;i++)
    {
        ctrl = static_cast <TControl*> (frm->Controls[i]);

        if (tipos_permitidos.find(AnsiString(ctrl->ClassName())) == tipos_permitidos.end())
            continue;

        //TOP
        ctrl->Top = ini->ReadInteger(Seccion, ctrl->Name + "_Top", ctrl->Top);
        //LEFT
        ctrl->Left = ini->ReadInteger(Seccion, ctrl->Name + "_Left", ctrl->Left);
        //Width
        ctrl->Width = ini->ReadInteger(Seccion, ctrl->Name + "_Width", ctrl->Width);
        //Height
        ctrl->Height = ini->ReadInteger(Seccion, ctrl->Name + "_Height", ctrl->Height);
    }
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TUtil::guardar_xywh_controles(TForm *frm, AnsiString Seccion)
{
    auto_ptr<TIniFile> ini(new TIniFile(ChangeFileExt(Application->ExeName, ".INI")));

    AnsiString NombreControl;
    int valor;
    TControl *ctrl;
    set<AnsiString> tipos_permitidos;

    tipos_permitidos.insert("TButton");
    tipos_permitidos.insert("TBitBtn");
    tipos_permitidos.insert("TSpeedButton");
    tipos_permitidos.insert("TImage");
    tipos_permitidos.insert("TPanel");
    tipos_permitidos.insert("TMemo");
    tipos_permitidos.insert("TStaticText");
    tipos_permitidos.insert("TLabel");

    for(int i=0;i < frm->ControlCount;i++)
    {
        ctrl = static_cast <TControl*> (frm->Controls[i]);

        if (tipos_permitidos.find(AnsiString(ctrl->ClassName())) == tipos_permitidos.end())
            continue;

        //TOP
        NombreControl = ctrl->Name + "_Top";
        valor = ctrl->Top;
        ini->WriteInteger(Seccion, NombreControl, valor);
        //LEFT
        NombreControl = ctrl->Name + "_Left";
        valor = ctrl->Left;
        ini->WriteInteger(Seccion, NombreControl, valor);
        //Width
        NombreControl = ctrl->Name + "_Width";
        valor = ctrl->Width;
        ini->WriteInteger(Seccion, NombreControl, valor);
        //Height
        NombreControl = ctrl->Name + "_Height";
        valor = ctrl->Height;
        ini->WriteInteger(Seccion, NombreControl, valor);
    }

}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
void __fastcall TUtil::cargar_xywh_controles(TForm *frm, AnsiString Seccion)
{
    auto_ptr<TIniFile> ini(new TIniFile(ChangeFileExt(Application->ExeName, ".INI")));

    TControl *ctrl;
    set<AnsiString> tipos_permitidos;

    tipos_permitidos.insert("TButton");
    tipos_permitidos.insert("TBitBtn");
    tipos_permitidos.insert("TSpeedButton");
    tipos_permitidos.insert("TImage");
    tipos_permitidos.insert("TPanel");
    tipos_permitidos.insert("TMemo");
    tipos_permitidos.insert("TStaticText");
    tipos_permitidos.insert("TLabel");

    for(int i=0;i < frm->ComponentCount;i++)
    {
        ctrl = static_cast <TControl*> (frm->Components[i]);

        if (tipos_permitidos.find(AnsiString(ctrl->ClassName())) == tipos_permitidos.end())
            continue;

        //TOP
        ctrl->Top = ini->ReadInteger(Seccion, ctrl->Name + "_Top", ctrl->Top);
        //LEFT
        ctrl->Left = ini->ReadInteger(Seccion, ctrl->Name + "_Left", ctrl->Left);
        //Width
        ctrl->Width = ini->ReadInteger(Seccion, ctrl->Name + "_Width", ctrl->Width);
        //Height
        ctrl->Height = ini->ReadInteger(Seccion, ctrl->Name + "_Height", ctrl->Height);
    }
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TUtil::DameResolucionPantalla(int *ancho, int *alto)
{
    HDC Handle;
    DWORD bitesPP, x, y;

    Handle =GetDC(Application->Handle);
    // pero lo de dejo para otra historia.
    x = GetDeviceCaps(Handle, HORZRES);
    y = GetDeviceCaps(Handle, VERTRES);

    ReleaseDC(Application->Handle, Handle);

    *ancho = x;
    *alto = y;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// obtaining file size
unsigned long __fastcall TUtil::DameSizeArchivo(AnsiString thefile)
{
    const char * filename = thefile.c_str();
    long l,m;
    ifstream file (filename, ios::in|ios::binary);
    l = file.tellg();
    file.seekg (0, ios::end);
    m = file.tellg();
    file.close();
    return m-l;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
AnsiString __fastcall TUtil::DameErrorSocket(TErrorEvent error)
{
    AnsiString sError;

    if (error == eeGeneral)
        sError = "Error inesperado del socket.";
    else if (error == eeSend)
        sError = "Ocurrió un error mientras se intentaba escribir en la conexión con el socket.";
    else if (error == eeReceive)
        sError = "Ocurrió un error mientras se intentaba leer en la conexión con el socket.";
    else if (error == eeConnect)
        sError = "Error localizando al servidor, o existió un problema abriendo la conexión.";
    else if (error == eeDisconnect)
        sError = "Ocurrió un error mientras se intentaba cerrar la conexión.";
    else if (error == eeAccept)
        sError = "Error aceptando la petición de conexión del cliente.";

    return sError;
}
//---------------------------------------------------------------------------


//----------------------------------------------------------------------
int TUtil::WinExecAndWait32(AnsiString FileName, int Visibility)
{
    //char zAppName[1024];
    //char zCurDir[512];
    AnsiString zAppName, zCurDir;
    AnsiString WorkDir;
    TStartupInfo StartupInfo;
    TProcessInformation ProcessInfo;

    //strcpy(zAppName, FileName.c_str());
    zAppName = FileName;
    WorkDir = GetCurrentDir();
    //strcpy(zCurDir, WorkDir.c_str());
    zCurDir = WorkDir;
    setmem(&StartupInfo, sizeof(StartupInfo), 0);

    StartupInfo.cb = sizeof(StartupInfo);
    StartupInfo.dwFlags = STARTF_USESHOWWINDOW;
    StartupInfo.wShowWindow = Visibility;

    if (!CreateProcess(NULL, zAppName.c_str(), // pointer to command line string
        NULL, // pointer to process security attributes
        NULL, // pointer to thread security attributes
        false, // handle inheritance flag
        CREATE_NEW_CONSOLE | // creation flags
        NORMAL_PRIORITY_CLASS,
        NULL, // pointer to new environment block
        NULL, // pointer to current directory name
        &StartupInfo, // pointer to STARTUPINFO
        &ProcessInfo))
    {
        return -1; // pointer to PROCESS_INF
    }
    else
    {
        WaitForSingleObject(ProcessInfo.hProcess,INFINITE);
        DWORD ExitCode;
        GetExitCodeProcess(ProcessInfo.hProcess, &ExitCode);
        return ExitCode;
    }
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
//ver http://msdn2.microsoft.com/en-us/library/aa376868.aspx
bool TUtil::apagarWindows(int flag)
{
    OSVERSIONINFO osvi;
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx( &osvi );
    if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
        //--- Si estamos en NT/2000/XP obtenemos el permiso necesario del sistema

        HANDLE hToken;
        TOKEN_PRIVILEGES tkp;

        if (!OpenProcessToken(GetCurrentProcess(),
                TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
            return false;

        LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);

        tkp.PrivilegeCount = 1;
        tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

        AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

        if (GetLastError() != ERROR_SUCCESS)
            return false;
    }

    //--- Apagamos

    if (!ExitWindowsEx(flag | EWX_FORCE,
                  SHTDN_REASON_MINOR_ENVIRONMENT | SHTDN_REASON_FLAG_PLANNED))
        return false;

    return true;
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
//crea un proceso y devuelve su handle
int TUtil::CrearProceso(AnsiString FileName, int Visibility)
{
    //char zAppName[1024];
    //char zCurDir[512];
    AnsiString zAppName, zCurDir;
    AnsiString WorkDir;
    TStartupInfo StartupInfo;
    TProcessInformation ProcessInfo;

    //strcpy(zAppName, FileName.c_str());
    zAppName = FileName;
    WorkDir = GetCurrentDir();
    //strcpy(zCurDir, WorkDir.c_str());
    zCurDir = WorkDir;
    setmem(&StartupInfo, sizeof(StartupInfo), 0);

    StartupInfo.cb = sizeof(StartupInfo);
    StartupInfo.dwFlags = STARTF_USESHOWWINDOW;
    StartupInfo.wShowWindow = Visibility;

    if (!CreateProcess(NULL, zAppName.c_str(), // pointer to command line string
        NULL, // pointer to process security attributes
        NULL, // pointer to thread security attributes
        false, // handle inheritance flag
        CREATE_NEW_CONSOLE | // creation flags
        NORMAL_PRIORITY_CLASS,
        NULL, // pointer to new environment block
        NULL, // pointer to current directory name
        &StartupInfo, // pointer to STARTUPINFO
        &ProcessInfo))
    {
        return -1; // pointer to PROCESS_INF
    }

    return (int)ProcessInfo.hProcess;
}
//----------------------------------------------------------------------


