object Form1: TForm1
  Left = 192
  Top = 114
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'CEMF Builder'
  ClientHeight = 324
  ClientWidth = 490
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 131
    Height = 13
    Caption = 'Code Eye 1.2 Mix File name'
  end
  object Label3: TLabel
    Left = 360
    Top = 296
    Width = 119
    Height = 13
    Caption = '(C) MatrixS_Master, 2007'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsUnderline]
    ParentFont = False
  end
  object Edit1: TEdit
    Left = 8
    Top = 24
    Width = 433
    Height = 21
    TabOrder = 0
  end
  object Button1: TButton
    Left = 448
    Top = 24
    Width = 33
    Height = 25
    Caption = '...'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 8
    Top = 272
    Width = 137
    Height = 41
    Caption = 'Start Process'
    TabOrder = 2
    OnClick = Button2Click
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 56
    Width = 473
    Height = 169
    Caption = 'Output Folder'
    TabOrder = 3
    object Label2: TLabel
      Left = 8
      Top = 136
      Width = 25
      Height = 13
      Caption = 'Drive'
    end
    object dirList: TDirectoryListBox
      Left = 8
      Top = 16
      Width = 457
      Height = 113
      ItemHeight = 16
      TabOrder = 0
    end
    object cbox1: TComboBox
      Left = 40
      Top = 136
      Width = 65
      Height = 21
      ItemHeight = 13
      TabOrder = 1
      OnChange = cbox1Change
    end
  end
  object Panel1: TPanel
    Left = 8
    Top = 232
    Width = 473
    Height = 33
    BevelOuter = bvLowered
    TabOrder = 4
    object CGauge1: TCGauge
      Left = 8
      Top = 8
      Width = 457
      Height = 17
      ShowText = False
      ForeColor = clGreen
    end
  end
  object Button3: TButton
    Left = 168
    Top = 288
    Width = 169
    Height = 25
    Caption = 'Exit'
    TabOrder = 5
    OnClick = Button3Click
  end
  object od1: TOpenDialog
    DefaultExt = 'txt'
    Filter = 'Text Files (TXT)|*.txt|All Files|*.*'
    Left = 200
    Top = 8
  end
end
