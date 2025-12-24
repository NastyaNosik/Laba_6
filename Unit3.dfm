object Form3: TForm3
  Left = 0
  Top = 0
  Caption = 'Menu'
  ClientHeight = 260
  ClientWidth = 300
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  TextHeight = 13
  object LabelHello: TLabel
    Left = 0
    Top = 0
    Width = 300
    Height = 16
    Align = alTop
    Alignment = taCenter
    Caption = 'Hello'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    Layout = tlCenter
    ExplicitWidth = 31
  end
  object LabelBest: TLabel
    Left = 0
    Top = 16
    Width = 300
    Height = 13
    Align = alTop
    Alignment = taCenter
    Caption = 'Best score: 0'
    Layout = tlCenter
    ExplicitWidth = 63
  end
  object ButtonPlay: TButton
    Left = 80
    Top = 80
    Width = 140
    Height = 35
    Caption = 'Play'
    TabOrder = 0
    OnClick = ButtonPlayClick
  end
  object ButtonTop10: TButton
    Left = 80
    Top = 130
    Width = 140
    Height = 35
    Caption = 'Top 10'
    TabOrder = 1
    OnClick = ButtonTop10Click
  end
  object ButtonExit: TButton
    Left = 80
    Top = 180
    Width = 140
    Height = 35
    Caption = 'Exit'
    TabOrder = 2
    OnClick = ButtonExitClick
  end
end
