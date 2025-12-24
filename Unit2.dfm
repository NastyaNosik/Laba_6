object GameForm: TGameForm
  Left = 0
  Top = 0
  Caption = '2048'
  ClientHeight = 350
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
  object LabelScore: TLabel
    Left = 0
    Top = 0
    Width = 350
    Height = 16
    Align = alTop
    Alignment = taCenter
    Caption = 'Score: 0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    Layout = tlCenter
    ExplicitWidth = 54
  end
  object Grid: TStringGrid
    Left = 0
    Top = 16
    Width = 350
    Height = 334
    Align = alClient
    ColCount = 4
    DefaultColWidth = 80
    DefaultRowHeight = 80
    FixedCols = 0
    RowCount = 4
    FixedRows = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
    ScrollBars = ssNone
    TabOrder = 0
  end
end
