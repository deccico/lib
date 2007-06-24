//----------------------------------------------------------------------------
#ifndef blobH
#define blobH
//----------------------------------------------------------------------------
#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
#include <DBCtrls.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
//----------------------------------------------------------------------------
class TdlgMemo : public TForm
{
__published:
	TBevel *Bevel1;
    TDBMemo *dbMemo;
        TRichEdit *redBlob;
        TBitBtn *BitBtn1;
    TBitBtn *btnImprimir;
    TBitBtn *btnGuardar;
    TSaveDialog *SaveDialog;
    TMemo *Memo1;
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall btnImprimirClick(TObject *Sender);
    void __fastcall btnGuardarClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:
    void __fastcall mAsignarredBlob();
public:
	virtual __fastcall TdlgMemo(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TdlgMemo *dlgMemo;
//----------------------------------------------------------------------------
#endif    
