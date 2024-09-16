object Form1: TForm1
  Left = 189
  Top = 107
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'MSM'#39's Code Eye'
  ClientHeight = 297
  ClientWidth = 513
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
  object Label4: TLabel
    Left = 8
    Top = 240
    Width = 62
    Height = 13
    Caption = 'Project name'
  end
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 25
    Height = 13
    Caption = 'Drive'
  end
  object selDir: TDirectoryListBox
    Left = 8
    Top = 40
    Width = 201
    Height = 185
    FileList = selFile
    ItemHeight = 16
    TabOrder = 1
  end
  object selFile: TFileListBox
    Left = 216
    Top = 8
    Width = 289
    Height = 217
    ItemHeight = 13
    TabOrder = 2
    OnChange = selFileChange
    OnDblClick = selFileDblClick
  end
  object Edit1: TEdit
    Left = 80
    Top = 240
    Width = 217
    Height = 21
    TabOrder = 3
  end
  object BitBtn1: TBitBtn
    Left = 304
    Top = 240
    Width = 201
    Height = 49
    Caption = 'Mix!'
    TabOrder = 5
    OnClick = BitBtn1Click
    Kind = bkAll
  end
  object CheckBox1: TCheckBox
    Left = 80
    Top = 272
    Width = 73
    Height = 17
    Caption = 'Obfuscate'
    TabOrder = 4
  end
  object DriveComboBox1: TDriveComboBox
    Left = 40
    Top = 8
    Width = 145
    Height = 19
    TabOrder = 0
    OnChange = DriveComboBox1Change
  end
  object MainMenu1: TMainMenu
    Left = 16
    Top = 184
    object File1: TMenuItem
      Caption = 'File'
      object Mixit1: TMenuItem
        Caption = 'Mix it'
        ShortCut = 116
        OnClick = BitBtn1Click
      end
      object Openmixfile1: TMenuItem
        Caption = 'Open mix file'
        ShortCut = 114
        OnClick = Openmixfile1Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Exit1: TMenuItem
        Caption = 'Exit'
        ShortCut = 16465
        OnClick = Exit1Click
      end
    end
    object Edit2: TMenuItem
      Caption = 'Edit'
      object Disclaimer1: TMenuItem
        Caption = 'Disclaimer'
        Enabled = False
        OnClick = Disclaimer1Click
      end
      object Changelog1: TMenuItem
        Caption = 'Changelog'
        Enabled = False
      end
    end
    object Window1: TMenuItem
      Caption = 'Window'
      object Arrange1: TMenuItem
        Caption = 'Arrange'
        Enabled = False
      end
      object Closeall1: TMenuItem
        Caption = 'Close all'
        ShortCut = 122
        OnClick = Closeall1Click
      end
    end
    object Help1: TMenuItem
      Caption = 'Help'
      object Launchparams1: TMenuItem
        Caption = 'Launch args'
        OnClick = Launchparams1Click
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object About1: TMenuItem
        Caption = 'About'
        ShortCut = 112
        OnClick = About1Click
      end
    end
  end
  object sd1: TSaveDialog
    DefaultExt = 'txt'
    Filter = 'Text files|*.txt|All files|*.*'
    Options = [ofEnableSizing]
    Title = 'Save MixProject file'
    Left = 48
    Top = 184
  end
  object od1: TOpenDialog
    DefaultExt = 'txt'
    Filter = 'Text files|*.txt|All files|*.*'
    Title = 'Open MixProject file'
    Left = 80
    Top = 184
  end
end
