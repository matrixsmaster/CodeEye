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
    object BitBtn3: TBitBtn
      Left = 208
      Top = 8
      Width = 91
      Height = 25
      Caption = 'Make dir'
      TabOrder = 2
      OnClick = BitBtn3Click
      Glyph.Data = {
        DE010000424DDE01000000000000760000002800000024000000120000000100
        0400000000006801000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00344446333334
        44433333FFFF333333FFFF33000033AAA43333332A4333338833F33333883F33
        00003332A46333332A4333333383F33333383F3300003332A2433336A6633333
        33833F333383F33300003333AA463362A433333333383F333833F33300003333
        6AA4462A46333333333833FF833F33330000333332AA22246333333333338333
        33F3333300003333336AAA22646333333333383333F8FF33000033444466AA43
        6A43333338FFF8833F383F330000336AA246A2436A43333338833F833F383F33
        000033336A24AA442A433333333833F33FF83F330000333333A2AA2AA4333333
        333383333333F3330000333333322AAA4333333333333833333F333300003333
        333322A4333333333333338333F333330000333333344A433333333333333338
        3F333333000033333336A24333333333333333833F333333000033333336AA43
        33333333333333833F3333330000333333336663333333333333333888333333
        0000}
      NumGlyphs = 2
    end
    object nDirName: TEdit
      Left = 304
      Top = 8
      Width = 209
      Height = 21
      TabOrder = 3
    end
  end
end
