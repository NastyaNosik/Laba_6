object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Game Login'
  ClientHeight = 250
  ClientWidth = 400
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  TextHeight = 13
  object Label1: TLabel
    Left = 80
    Top = 40
    Width = 48
    Height = 13
    Caption = 'Username'
  end
  object Label2: TLabel
    Left = 80
    Top = 100
    Width = 46
    Height = 13
    Caption = 'Password'
  end
  object EditUsername: TEdit
    Left = 80
    Top = 59
    Width = 240
    Height = 21
    TabOrder = 0
    TextHint = 'Enter username'
  end
  object EditPassword: TEdit
    Left = 80
    Top = 120
    Width = 240
    Height = 21
    PasswordChar = '*'
    TabOrder = 1
    TextHint = 'Enter password'
  end
  object ButtonRegister: TButton
    Left = 80
    Top = 170
    Width = 100
    Height = 40
    Caption = 'Register'
    TabOrder = 2
    OnClick = ButtonRegisterClick
  end
  object ButtonLogin: TButton
    Left = 220
    Top = 170
    Width = 100
    Height = 40
    Caption = 'Login'
    TabOrder = 3
    OnClick = ButtonLoginClick
  end
end
