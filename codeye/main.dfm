object Form1: TForm1
  Left = 189
  Top = 107
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'MSM'#39's Code Eye'
  ClientHeight = 265
  ClientWidth = 515
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDesktopCenter
  OnActivate = FormActivate
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Label2: TLabel
    Left = 424
    Top = 240
    Width = 79
    Height = 16
    Caption = 'C++ Edition'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 184
    Top = 200
    Width = 39
    Height = 13
    Caption = 'Method:'
  end
  object selDir: TDirectoryListBox
    Left = 8
    Top = 8
    Width = 201
    Height = 177
    FileList = selFile
    ItemHeight = 16
    TabOrder = 0
  end
  object selFile: TFileListBox
    Left = 216
    Top = 8
    Width = 289
    Height = 177
    ItemHeight = 13
    TabOrder = 1
    OnChange = selFileChange
    OnDblClick = selFileDblClick
  end
  object Button1: TButton
    Left = 160
    Top = 224
    Width = 201
    Height = 33
    Caption = 'Mix Project and View'
    TabOrder = 2
    OnClick = Button1Click
  end
  object Panel1: TPanel
    Left = 8
    Top = 192
    Width = 121
    Height = 33
    TabOrder = 3
    object Label1: TLabel
      Left = 8
      Top = 4
      Width = 25
      Height = 13
      Caption = 'Drive'
    end
    object cb1: TComboBox
      Left = 40
      Top = 4
      Width = 73
      Height = 21
      ItemHeight = 13
      TabOrder = 0
      OnChange = cb1Change
    end
  end
  object RadioButton1: TRadioButton
    Left = 240
    Top = 200
    Width = 49
    Height = 17
    Caption = 'Rich'
    TabOrder = 4
  end
  object RadioButton2: TRadioButton
    Left = 296
    Top = 200
    Width = 57
    Height = 17
    Caption = 'Classic'
    Checked = True
    TabOrder = 5
    TabStop = True
  end
  object MainMenu1: TMainMenu
    Left = 160
    Top = 152
    object File1: TMenuItem
      Caption = 'File'
      object Exit1: TMenuItem
        Caption = 'Exit'
        OnClick = Exit1Click
      end
    end
    object Window1: TMenuItem
      Caption = 'Window'
      object Closeall1: TMenuItem
        Caption = 'Close all'
        OnClick = Closeall1Click
      end
    end
    object Help1: TMenuItem
      Caption = 'Help'
      object Launchparams1: TMenuItem
        Caption = 'Launch params'
      end
      object About1: TMenuItem
        Caption = 'About'
        OnClick = About1Click
      end
    end
  end
end
