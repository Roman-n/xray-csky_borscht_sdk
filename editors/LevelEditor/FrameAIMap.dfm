object fraAIMap: TfraAIMap
  Left = 918
  Top = 206
  VertScrollBar.Visible = False
  Align = alClient
  BorderStyle = bsNone
  ClientHeight = 346
  ClientWidth = 213
  Color = 10528425
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clBlack
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  object paObjectList: TPanel
    Left = 0
    Top = 0
    Width = 213
    Height = 117
    Align = alTop
    ParentColor = True
    TabOrder = 0
    DesignSize = (
      213
      117)
    object Label2: TLabel
      Left = 1
      Top = 1
      Width = 211
      Height = 13
      Align = alTop
      Alignment = taCenter
      Caption = 'AI Map Commands'
      Color = clGray
      ParentColor = False
      OnClick = ExpandClick
    end
    object ExtBtn2: TExtBtn
      Left = 200
      Top = 2
      Width = 11
      Height = 11
      Align = alNone
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Glyph.Data = {
        DE000000424DDE00000000000000360000002800000007000000070000000100
        180000000000A8000000120B0000120B00000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFF00
        0000FFFFFFFFFFFF000000000000000000FFFFFFFFFFFF000000FFFFFF000000
        000000000000000000000000FFFFFF0000000000000000000000000000000000
        00000000000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00
        0000}
      ParentFont = False
      OnClick = PanelMinClick
    end
    object ebGenerateMap: TExtBtn
      Left = 1
      Top = 16
      Width = 107
      Height = 15
      Align = alNone
      BevelShow = False
      HotTrack = True
      HotColor = 15790320
      Caption = 'Generate Full'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Margin = 13
      ParentFont = False
      OnClick = ebGenerateMapClick
    end
    object ebSmoothNodes: TExtBtn
      Left = 102
      Top = 16
      Width = 107
      Height = 15
      Align = alNone
      Anchors = [akTop]
      BevelShow = False
      HotTrack = True
      HotColor = 15790320
      Caption = 'Smooth Selected'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Margin = 13
      ParentFont = False
      OnClick = ebSmoothNodesClick
    end
    object ExtBtn6: TExtBtn
      Left = 102
      Top = 32
      Width = 107
      Height = 15
      Align = alNone
      Anchors = [akTop]
      BevelShow = False
      HotTrack = True
      HotColor = 15790320
      Caption = 'Clear AI Map'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Margin = 13
      ParentFont = False
      OnClick = ExtBtn6Click
    end
    object ebGenerateSelected: TExtBtn
      Left = 1
      Top = 32
      Width = 107
      Height = 15
      Align = alNone
      BevelShow = False
      HotTrack = True
      HotColor = 15790320
      Caption = 'Generate Selected'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Margin = 13
      ParentFont = False
      OnClick = ebGenerateSelectedClick
    end
    object ebResetSelected: TExtBtn
      Left = 1
      Top = 48
      Width = 107
      Height = 15
      Align = alNone
      BevelShow = False
      HotTrack = True
      HotColor = 15790320
      Caption = 'Reset Selected'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Margin = 13
      ParentFont = False
      OnClick = ebResetSelectedClick
    end
    object ebLoadErrorList: TExtBtn
      Left = 0
      Top = 80
      Width = 97
      Height = 17
      Align = alNone
      BevelShow = False
      HotTrack = True
      HotColor = 15790320
      Caption = 'Load Error List'
      OnClick = ebLoadErrorListClick
    end
    object ebSelectErrorNodes: TExtBtn
      Left = 106
      Top = 80
      Width = 105
      Height = 17
      Align = alNone
      Anchors = [akTop]
      BevelShow = False
      HotTrack = True
      HotColor = 15790320
      Caption = 'Select Error Nodes'
      OnClick = ebSelectErrorNodesClick
    end
    object ebClearErrorList: TExtBtn
      Left = 0
      Top = 96
      Width = 97
      Height = 17
      Align = alNone
      BevelShow = False
      HotTrack = True
      HotColor = 15790320
      Caption = 'Clear Error List'
      OnClick = ebClearErrorListClick
    end
    object Label4: TLabel
      Left = 1
      Top = 64
      Width = 210
      Height = 13
      Alignment = taCenter
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      Caption = 'AI Map Errors'
      Color = clGray
      ParentColor = False
    end
  end
  object paLink: TPanel
    Left = 0
    Top = 117
    Width = 213
    Height = 232
    Align = alTop
    ParentColor = True
    TabOrder = 1
    DesignSize = (
      213
      232)
    object Label3: TLabel
      Left = 1
      Top = 1
      Width = 211
      Height = 13
      Align = alTop
      Alignment = taCenter
      Caption = 'AI Map Nodes'
      Color = clGray
      ParentColor = False
      OnClick = ExpandClick
    end
    object ExtBtn4: TExtBtn
      Left = 200
      Top = 2
      Width = 11
      Height = 11
      Align = alNone
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Glyph.Data = {
        DE000000424DDE00000000000000360000002800000007000000070000000100
        180000000000A8000000120B0000120B00000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFF00
        0000FFFFFFFFFFFF000000000000000000FFFFFFFFFFFF000000FFFFFF000000
        000000000000000000000000FFFFFF0000000000000000000000000000000000
        00000000000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00
        0000}
      ParentFont = False
      OnClick = PanelMinClick
    end
    object ebModeAppend: TExtBtn
      Left = 6
      Top = 55
      Width = 46
      Height = 15
      Align = alNone
      BevelShow = False
      HotTrack = True
      HotColor = 15790320
      GroupIndex = 1
      Down = True
      Caption = 'Add'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Margin = 2
      ParentFont = False
      FlatAlwaysEdge = True
    end
    object ebModeRemove: TExtBtn
      Left = 6
      Top = 70
      Width = 46
      Height = 15
      Align = alNone
      BevelShow = False
      HotTrack = True
      HotColor = 15790320
      GroupIndex = 1
      Caption = 'Delete'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Margin = 2
      ParentFont = False
      FlatAlwaysEdge = True
    end
    object ebUp: TExtBtn
      Tag = 1
      Left = 78
      Top = 55
      Width = 24
      Height = 15
      Align = alNone
      Anchors = [akTop]
      BevelShow = False
      HotTrack = True
      HotColor = 15790320
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Glyph.Data = {
        F6000000424DF600000000000000360000002800000008000000080000000100
        180000000000C0000000120B0000120B00000000000000000000FFFFFFFFFFFF
        FFFFFF000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000000000
        00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000FFFFFFFFFFFFFF
        FFFFFFFFFF000000000000000000000000191919000000FFFFFFFFFFFFFFFFFF
        000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFF0000000000000000
        00000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000FFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFF000000000000FFFFFFFFFFFFFFFFFF}
      ParentFont = False
      FlatAlwaysEdge = True
      OnClick = ebSideClick
    end
    object ebDown: TExtBtn
      Tag = 3
      Left = 78
      Top = 85
      Width = 24
      Height = 15
      Align = alNone
      Anchors = [akTop]
      BevelShow = False
      HotTrack = True
      HotColor = 15790320
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Glyph.Data = {
        F6000000424DF600000000000000360000002800000008000000080000000100
        180000000000C0000000120B0000120B00000000000000000000FFFFFFFFFFFF
        FFFFFF000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000000000
        00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000000000000000FFFFFFFF
        FFFFFFFFFFFFFFFF000000000000000000000000FFFFFFFFFFFFFFFFFF000000
        191919000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFF0000000000
        00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000FFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFF000000000000FFFFFFFFFFFFFFFFFF}
      ParentFont = False
      FlatAlwaysEdge = True
      OnClick = ebSideClick
    end
    object ebLeft: TExtBtn
      Left = 55
      Top = 70
      Width = 24
      Height = 15
      Align = alNone
      Anchors = [akTop]
      BevelShow = False
      HotTrack = True
      HotColor = 15790320
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Glyph.Data = {
        F6000000424DF600000000000000360000002800000008000000080000000100
        180000000000C0000000120B0000120B00000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000
        00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000000000FFFFFFFFFFFFFF
        FFFF000000000000000000000000000000000000000000000000000000000000
        000000000000000000000000000000000000FFFFFFFFFFFF0000000000001919
        19FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
      ParentFont = False
      FlatAlwaysEdge = True
      OnClick = ebSideClick
    end
    object ebRight: TExtBtn
      Tag = 2
      Left = 100
      Top = 70
      Width = 24
      Height = 15
      Align = alNone
      Anchors = [akTop]
      BevelShow = False
      HotTrack = True
      HotColor = 15790320
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Glyph.Data = {
        F6000000424DF600000000000000360000002800000008000000080000000100
        180000000000C0000000120B0000120B00000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF191919000000000000FFFFFFFF
        FFFF000000000000000000000000000000000000000000000000000000000000
        000000000000000000000000000000000000FFFFFFFFFFFFFFFFFF0000000000
        00000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
      ParentFont = False
      FlatAlwaysEdge = True
      OnClick = ebSideClick
    end
    object ebFull: TExtBtn
      Tag = 4
      Left = 78
      Top = 70
      Width = 24
      Height = 15
      Align = alNone
      Anchors = [akTop]
      BevelShow = False
      HotTrack = True
      HotColor = 15790320
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Glyph.Data = {
        E6010000424DE60100000000000036000000280000000C0000000C0000000100
        180000000000B0010000120B0000120B00000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFF000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFF000000000000000000000000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFF7F7F7F0000000000000000000000007F7F7FFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFF7F7F7FFFFFFFFFFFFF000000000000FFFFFFFFFF
        FF7F7F7FFFFFFFFFFFFFFFFFFF000000000000FFFFFFFFFFFF000000000000FF
        FFFFFFFFFF000000000000FFFFFF000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        00000000000000000000000000000000000000000000FFFFFF000000000000FF
        FFFFFFFFFF000000000000FFFFFFFFFFFF000000000000FFFFFFFFFFFFFFFFFF
        7F7F7FFFFFFFFFFFFF000000000000FFFFFFFFFFFF7F7F7FFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFF7F7F7F0000000000000000000000007F7F7FFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000FFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFF}
      ParentFont = False
      FlatAlwaysEdge = True
      OnClick = ebSideClick
    end
    object ebModeInvert: TExtBtn
      Left = 6
      Top = 85
      Width = 46
      Height = 15
      Align = alNone
      BevelShow = False
      HotTrack = True
      HotColor = 15790320
      GroupIndex = 1
      Caption = 'Invert'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Margin = 2
      ParentFont = False
      FlatAlwaysEdge = True
    end
    object Label5: TLabel
      Left = 1
      Top = 36
      Width = 211
      Height = 13
      Alignment = taCenter
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      Caption = 'Link Commands'
      Color = clGray
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
    end
    object ebIgnoreConstraints: TExtBtn
      Left = 3
      Top = 16
      Width = 100
      Height = 15
      Align = alNone
      AllowAllUp = True
      Anchors = [akTop]
      BevelShow = False
      HotTrack = True
      HotColor = 15790320
      BtnColor = 10528425
      GroupIndex = 2
      Caption = 'Ignore Constraints'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      NumGlyphs = 4
      ParentFont = False
      Spacing = 3
    end
    object ebAutoLink: TExtBtn
      Left = 108
      Top = 16
      Width = 99
      Height = 15
      Align = alNone
      AllowAllUp = True
      Anchors = [akTop]
      BevelShow = False
      HotTrack = True
      HotColor = 15790320
      BtnColor = 10528425
      GroupIndex = 3
      Down = True
      Caption = 'Auto Link'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      NumGlyphs = 4
      ParentFont = False
      Spacing = 3
    end
    object ExtBtn1: TExtBtn
      Left = 128
      Top = 55
      Width = 77
      Height = 15
      Align = alNone
      Anchors = [akTop, akRight]
      BevelShow = False
      HotTrack = True
      HotColor = 15790320
      Caption = 'Select 0-Link'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Margin = 2
      ParentFont = False
      FlatAlwaysEdge = True
      OnClick = ebSelLinkClick
    end
    object ExtBtn5: TExtBtn
      Tag = 1
      Left = 128
      Top = 70
      Width = 77
      Height = 15
      Align = alNone
      Anchors = [akTop, akRight]
      BevelShow = False
      HotTrack = True
      HotColor = 15790320
      Caption = 'Select 1-Link'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Margin = 2
      ParentFont = False
      FlatAlwaysEdge = True
      OnClick = ebSelLinkClick
    end
    object ExtBtn3: TExtBtn
      Tag = 2
      Left = 128
      Top = 85
      Width = 77
      Height = 15
      Align = alNone
      Anchors = [akTop, akRight]
      BevelShow = False
      HotTrack = True
      HotColor = 15790320
      Caption = 'Select 2-Link'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Margin = 2
      ParentFont = False
      FlatAlwaysEdge = True
      OnClick = ebSelLinkClick
    end
    object btnIgnoreMaterialClear: TExtBtn
      Left = 170
      Top = 121
      Width = 37
      Height = 14
      Hint = 'Clear snap list'
      Align = alNone
      Anchors = [akTop, akRight]
      BevelShow = False
      HotTrack = True
      HotColor = 15790320
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Glyph.Data = {
        56010000424D560100000000000036000000280000000A000000090000000100
        18000000000020010000120B0000120B00000000000000000000C8D0D4C8D0D4
        C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D40000C8D0D4000000
        000000C8D0D4C8D0D4C8D0D4C8D0D4000000000000C8D0D40000C8D0D4C8D0D4
        000000000000C8D0D4C8D0D4000000000000C8D0D4C8D0D40000C8D0D4C8D0D4
        C8D0D4000000000000000000000000C8D0D4C8D0D4C8D0D40000C8D0D4C8D0D4
        C8D0D4C8D0D4000000000000C8D0D4C8D0D4C8D0D4C8D0D40000C8D0D4C8D0D4
        C8D0D4000000000000000000000000C8D0D4C8D0D4C8D0D40000C8D0D4C8D0D4
        000000000000C8D0D4C8D0D4000000000000C8D0D4C8D0D40000C8D0D4000000
        000000C8D0D4C8D0D4C8D0D4C8D0D4000000000000C8D0D40000C8D0D4C8D0D4
        C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D40000}
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnClick = btnIgnoreMaterialClearClick
    end
    object Label1: TLabel
      Left = 1
      Top = 105
      Width = 217
      Height = 13
      Alignment = taCenter
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      Caption = 'Ignore materials'
      Color = clGray
      ParentColor = False
      OnClick = ExpandClick
    end
    object btnAddIgnoredMaterial: TExtBtn
      Left = 11
      Top = 121
      Width = 30
      Height = 14
      Hint = 'add material to ignore list'
      Align = alNone
      BevelShow = False
      HotTrack = True
      HotColor = 15790320
      Caption = 'Add'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnClick = btnAddIgnoredMaterialClick
    end
    object lbIgnoreMaterialsList: TListBox
      Left = 4
      Top = 138
      Width = 206
      Height = 87
      Anchors = [akLeft, akTop, akRight]
      BorderStyle = bsNone
      Color = clGray
      ExtendedSelect = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemHeight = 13
      MultiSelect = True
      ParentFont = False
      Sorted = True
      TabOrder = 0
    end
  end
  object fsStorage: TFormStorage
    IniSection = 'FrameAIMap'
    Options = []
    Version = 15
    StoredProps.Strings = (
      'paObjectList.Tag'
      'paLink.Tag'
      'paLink.Height'
      'ebModeAppend.Down'
      'ebModeInvert.Down'
      'ebModeRemove.Down')
    StoredValues = <>
    Left = 65528
    Top = 65528
  end
end
