// unidad que edita campos blob

//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "blob.h"
#include "dmFact.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TdlgMemo *dlgMemo;
//---------------------------------------------------------------------
__fastcall TdlgMemo::TdlgMemo(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------


void __fastcall TdlgMemo::BitBtn1Click(TObject *Sender)
{
   dlgMemo->Close();
}
//---------------------------------------------------------------------------

void __fastcall TdlgMemo::btnImprimirClick(TObject *Sender)
{
   mAsignarredBlob();

   Beep();
   //ShowMessage("Imprimiendo " + dbMemo->DataField);
   redBlob->Print(dbMemo->DataField);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//guarda el texto del cuadro memo
void __fastcall TdlgMemo::btnGuardarClick(TObject *Sender)
{
   mAsignarredBlob();

   if (SaveDialog->Execute())       //save dialog no se ve en el form
   {
       if (FileExists(SaveDialog->FileName)){
           FileSetAttr(SaveDialog->FileName, faArchive);
           DeleteFile(SaveDialog->FileName);
       }
       Memo1->Lines->SaveToFile(SaveDialog->FileName);
       //redBlob->Lines->SaveToFile(SaveDialog->FileName);
   }
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TdlgMemo::mAsignarredBlob()
{

   AnsiString
        sSubr = "-------------------------------------------------------------------------------",
        sLine1, sLine2,sLine1a,sLine2a,sLine,sLine3,sTitle1,sTitle2,sT,
        sLine4 = sSubr.SubString(1,dbMemo->DataField.Length()*2);

   if (dbMemo->DataSource == dmFacturar->dsClientes){
        sLine1 = dmFacturar->tblClientes->FieldValues["codigo"];
        //sLine2 =
        bool bVacio = dmFacturar->tblClientes->FieldValues["Empresa"].IsNull() ;
        if (!bVacio)    sLine2 = dmFacturar->tblClientes->FieldValues["Empresa"];
        sT = "Cliente ";
        sTitle1 = sLine1;
        sTitle2 = sLine2;
        sLine3 = dmFacturar->tblClientes->FieldValues[dbMemo->DataField];
        sLine =  "- " + sLine1 + ", " + sLine2 + " - \r\n\r\n\r\n"
        + dbMemo->DataField + ": \r\n" + sLine4 + "\r\n\r\n" + sLine3 ;
   }
   else if (dbMemo->DataSource == dmFacturar->dsProveedores){
        sLine1 = dmFacturar->tblProveedores->FieldValues["codigo"];
        //sLine2 =
        bool bVacio = dmFacturar->tblProveedores->FieldValues["Empresa"].IsNull() ;
        if (!bVacio)    sLine2 = dmFacturar->tblProveedores->FieldValues["Empresa"];
        sT = "Proveedor ";
        sTitle1 = sLine1;
        sTitle2 = sLine2;
        sLine3 = dmFacturar->tblClientes->FieldValues[dbMemo->DataField];
        sLine =  "- " + sLine1 + ", " + sLine2 + " - \r\n\r\n\r\n"
        + dbMemo->DataField + ": \r\n" + sLine4 + "\r\n\r\n" + sLine3 ;
   }

   redBlob->Clear();
   Memo1->Clear();
   redBlob->Text = sLine;
   Memo1->Lines->Text = sLine;

   SaveDialog->Title = Application->Title + " " + AnsiString(dbMemo->DataField);
   SaveDialog->FileName = sT+sTitle1 + " - " + sTitle2 + " " + dbMemo->DataField;
}
//---------------------------------------------------------------------------

void __fastcall TdlgMemo::FormClose(TObject *Sender, TCloseAction &Action)
{
    Action = caFree;
}
//---------------------------------------------------------------------------

