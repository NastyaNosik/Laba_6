object GameForm: TGameForm
  Left = 0
  Top = 0
  Caption = '2048'
  ClientHeight = 380
  ClientWidth = 350
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  TextHeight = 13
  object PanelTop: TPanel
    Left = 0
    Top = 0
    Width = 350
    Height = 40
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    object LabelScore: TLabel
      Left = 8
      Top = 12
      Width = 40
      Height = 13
      Caption = 'Score: 0'
    end
    object ButtonMenu: TButton
      Left = 270
      Top = 7
      Width = 70
      Height = 25
      Caption = 'Menu'
      TabOrder = 0
      OnClick = ButtonMenuClick
    end
  end
  object Grid: TStringGrid
    Left = 0
    Top = 40
    Width = 350
    Height = 340
    Align = alClient
    ColCount = 4
    DefaultColWidth = 80
    DefaultRowHeight = 80
    FixedCols = 0
    RowCount = 4
    FixedRows = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
    ScrollBars = ssNone
    TabOrder = 1
  end
end
