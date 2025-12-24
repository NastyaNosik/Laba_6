//---------------------------------------------------------------------------

#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>

//---------------------------------------------------------------------------

class TForm4 : public TForm
{
__published:
    TStringGrid *GridTop;
    TPanel *PanelBottom;
    TButton *ButtonClose;

    void __fastcall FormCreate(TObject *Sender);
    void __fastcall ButtonCloseClick(TObject *Sender);

public:
    __fastcall TForm4(TComponent* Owner);

    void RefreshTop10();
};

//---------------------------------------------------------------------------

extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------

#endif

