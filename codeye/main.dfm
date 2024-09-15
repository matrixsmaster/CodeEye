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
  object pbar1: TProgressBar
    Left = 8
    Top = 248
    Width = 289
    Height = 33
    Min = 0
    Max = 100
    TabOrder = 6
    Visible = False
  end
  object selDir: TDirectoryListBox
    Left = 8
    Top = 40
    Width = 201
    Height = 185
    FileList = selFile
    ItemHeight = 16
    TabOrder = 0
  end
  object selFile: TFileListBox
    Left = 216
    Top = 8
    Width = 289
    Height = 217
    ItemHeight = 13
    TabOrder = 1
    OnChange = selFileChange
    OnDblClick = selFileDblClick
  end
  object Edit1: TEdit
    Left = 80
    Top = 240
    Width = 217
    Height = 21
    TabOrder = 2
  end
  object BitBtn1: TBitBtn
    Left = 304
    Top = 240
    Width = 201
    Height = 49
    Caption = 'Mix!'
    TabOrder = 3
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
    TabOrder = 5
    OnChange = DriveComboBox1Change
  end
  object MainMenu1: TMainMenu
    Left = 160
    Top = 152
    object File1: TMenuItem
      Caption = 'File'
      object Openmixfile1: TMenuItem
        Caption = 'Open mix file'
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Exit1: TMenuItem
        Caption = 'Exit'
        OnClick = Exit1Click
      end
    end
    object Edit2: TMenuItem
      Caption = 'Edit'
      object Disclaimer1: TMenuItem
        Caption = 'Disclaimer'
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
        Caption = 'Launch args'
        OnClick = Launchparams1Click
      end
      object About1: TMenuItem
        Caption = 'About'
        OnClick = About1Click
      end
    end
  end
  object sd1: TSaveDialog
    DefaultExt = 'txt'
    Filter = 'Text files|*.txt|All files|*.*'
    Options = [ofEnableSizing]
    Left = 336
    Top = 152
  end
end
