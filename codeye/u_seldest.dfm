object frmSelDest: TfrmSelDest
  Left = 293
  Top = 109
  Width = 531
  Height = 296
  BorderIcons = [biSystemMenu, biMaximize]
  Caption = 'Select destination'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 41
    Width = 523
    Height = 180
    Align = alClient
    BevelOuter = bvLowered
    TabOrder = 0
    object Splitter1: TSplitter
      Left = 297
      Top = 1
      Width = 4
      Height = 178
      Cursor = crHSplit
    end
    object fileList: TFileListBox
      Left = 301
      Top = 1
      Width = 221
      Height = 178
      Align = alClient
      ItemHeight = 13
      TabOrder = 0
    end
    object selDir: TDirectoryListBox
      Left = 1
      Top = 1
      Width = 296
      Height = 178
      Align = alLeft
      ItemHeight = 16
      TabOrder = 1
      OnChange = selDirChange
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 523
    Height = 41
    Align = alTop
    TabOrder = 1
    OnResize = Panel2Resize
    object selDrv: TDriveComboBox
      Left = 8
      Top = 6
      Width = 505
      Height = 19
      TabOrder = 0
      OnChange = selDrvChange
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 221
    Width = 523
    Height = 41
    Align = alBottom
    TabOrder = 2
    object BitBtn1: TBitBtn
      Left = 8
      Top = 8
      Width = 75
      Height = 25
      TabOrder = 0
      Kind = bkOK
    end
    object BitBtn2: TBitBtn
      Left = 88
      Top = 8
      Width = 75
      Height = 25
      TabOrder = 1
      Kind = bkAbort
    end
  end
end
