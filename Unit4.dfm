object Form4: TForm4
  Left = 0
  Top = 0
  Caption = 'Top 10'
  ClientHeight = 320
  ClientWidth = 360
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OnCreate = FormCreate
  TextHeight = 13
  object GridTop: TStringGrid
    Left = 0
    Top = 0
    Width = 360
    Height = 280
    Align = alClient
    ColCount = 2
    DefaultColWidth = 160
    FixedCols = 0
    RowCount = 11
    FixedRows = 1
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object PanelBottom: TPanel
    Left = 0
    Top = 280
    Width = 360
    Height = 40
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    object ButtonClose: TButton
      Left = 272
      Top = 7
      Width = 75
      Height = 25
      Caption = 'Close'
      TabOrder = 0
      OnClick = ButtonCloseClick
    end
  end
end
