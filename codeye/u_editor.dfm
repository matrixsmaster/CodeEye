object frmEdit: TfrmEdit
  Left = 192
  Top = 114
  Width = 508
  Height = 351
  Caption = 'view'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = mMenu0
  OldCreateOrder = False
  Position = poDesktopCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object TXT: TMemo
    Left = 0
    Top = 0
    Width = 500
    Height = 297
    Align = alClient
    Color = clSilver
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier'
    Font.Style = []
    ParentFont = False
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 0
  end
  object mMenu0: TMainMenu
    Left = 80
    Top = 120
    object File1: TMenuItem
      Caption = 'File'
      object Close1: TMenuItem
        Caption = 'Close'
        OnClick = Close1Click
      end
    end
    object Edit1: TMenuItem
      Caption = 'Edit'
      object SelectAll1: TMenuItem
        Caption = 'Select All'
        ShortCut = 16449
        OnClick = SelectAll1Click
      end
      object Copy1: TMenuItem
        Caption = 'Copy'
        OnClick = Copy1Click
      end
    end
    object View1: TMenuItem
      Caption = 'View'
      object Font1: TMenuItem
        Caption = 'Font'
        OnClick = Font1Click
      end
      object Background1: TMenuItem
        Caption = 'Background'
        OnClick = Background1Click
      end
    end
  end
  object fd0: TFontDialog
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    MinFontSize = 0
    MaxFontSize = 0
    Left = 200
    Top = 64
  end
  object cd0: TColorDialog
    Ctl3D = True
    Left = 232
    Top = 64
  end
end
