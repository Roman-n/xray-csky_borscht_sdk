object frmChoseItem: TfrmChoseItem
  Left = 856
  Top = 319
  Caption = 'Select Item'
  ClientHeight = 429
  ClientWidth = 349
  Color = 10528425
  Constraints.MinHeight = 360
  Constraints.MinWidth = 330
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  KeyPreview = True
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 177
    Top = 0
    Width = 2
    Height = 429
    Align = alRight
    ExplicitLeft = 185
    ExplicitHeight = 435
  end
  object paRight: TPanel
    Left = 179
    Top = 0
    Width = 170
    Height = 429
    Align = alRight
    BevelOuter = bvNone
    Color = clGray
    Constraints.MinWidth = 170
    TabOrder = 0
    object Splitter2: TSplitter
      Left = 0
      Top = 284
      Width = 170
      Height = 2
      Cursor = crVSplit
      Align = alBottom
      ExplicitTop = 290
    end
    object paMulti: TPanel
      Left = 0
      Top = 286
      Width = 170
      Height = 125
      Align = alBottom
      Constraints.MinHeight = 125
      ParentColor = True
      TabOrder = 0
      Visible = False
      object ebMultiUp: TExtBtn
        Left = 155
        Top = 3
        Width = 14
        Height = 18
        Align = alNone
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        Glyph.Data = {
          F6000000424DF600000000000000360000002800000008000000080000000100
          180000000000C0000000120B0000120B00000000000000000000FFFFFFFFFFFF
          FFFFFF000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000000000
          00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFDDDDDC000000000000DDDDDCFFFFFFFF
          FFFFFFFFFF000000000000000000000000191919000000FFFFFFFFFFFFDDDDDC
          000000000000000000000000DDDDDCFFFFFFFFFFFFFFFFFF0000000000000000
          00000000FFFFFFFFFFFFFFFFFFFFFFFFDDDDDC000000000000DDDDDCFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFF000000000000FFFFFFFFFFFFFFFFFF}
        ParentFont = False
        Spacing = 0
        OnClick = ebMultiUpClick
      end
      object ebMultiDown: TExtBtn
        Left = 155
        Top = 63
        Width = 14
        Height = 18
        Align = alNone
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        Glyph.Data = {
          F6000000424DF600000000000000360000002800000008000000080000000100
          180000000000C0000000120B0000120B00000000000000000000FFFFFFFFFFFF
          FFFFFF000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFDDDDDC0000000000
          00DDDDDCFFFFFFFFFFFFFFFFFFFFFFFF000000000000000000000000FFFFFFFF
          FFFFFFFFFFDDDDDC000000000000000000000000DDDDDCFFFFFFFFFFFF000000
          191919000000000000000000000000FFFFFFFFFFFFFFFFFFDDDDDC0000000000
          00DDDDDCFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000FFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFF000000000000FFFFFFFFFFFFFFFFFF}
        ParentFont = False
        Spacing = 0
        OnClick = ebMultiDownClick
      end
      object ebMultiRemove: TExtBtn
        Left = 155
        Top = 23
        Width = 14
        Height = 18
        Align = alNone
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
        Spacing = 0
        OnClick = ebMultiRemoveClick
      end
      object ebMultiClear: TExtBtn
        Left = 155
        Top = 43
        Width = 14
        Height = 18
        Align = alNone
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        Glyph.Data = {
          C2010000424DC20100000000000036000000280000000C0000000B0000000100
          1800000000008C010000120B0000120B00000000000000000000FFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFF000000000000FFFFFFFFFFFFFFFFFFFFFFFF000000000000FF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000FFFFFFFFFFFF000000000000
          FFFFFFFFFFFFFFFFFF000000000000FFFFFFFFFFFF0000000000000000000000
          00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000FFFFFFFFFFFF00000000
          0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000000000
          000000000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000
          00000000FFFFFFFFFFFF000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00
          0000000000000000000000FFFFFFFFFFFF000000000000FFFFFFFFFFFFFFFFFF
          000000000000FFFFFFFFFFFF000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FF000000000000FFFFFFFFFFFFFFFFFFFFFFFF000000000000FFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFF}
        ParentFont = False
        Spacing = 0
        OnClick = ebMultiClearClick
      end
      object tvMulti: TElTree
        Left = 1
        Top = 1
        Width = 152
        Height = 123
        Align = alLeft
        AutoExpand = True
        DragAllowed = True
        DrawFocusRect = False
        DragTrgDrawMode = dtdDownColorLine
        Flat = True
        FocusedSelectColor = 10526880
        FocusedSelectTextColor = clBlack
        FullRowSelect = False
        HeaderHeight = 19
        HeaderHotTrack = False
        HeaderSections.Data = {
          F1FFFFFF070000000000000000000000FFFFFFFF000001010100000078000000
          0000000010270000000100006489770600000000000000000000000000000100
          0000000000000000000100000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000010000000001000000000000
          0000000000000000000000000000FFFFFFFF0000010101000000780000000000
          00001027000000010000BC083404010000000000000000000000000001000000
          0000000000000001000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000100000000010000000000000000
          000000000000000000000000FFFFFFFF00000101010000007800000000000000
          1027000000010000DC3D26040200000000000000000000000000010000000000
          0000000000010000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000001000000000100000000000000000000
          00000000000000000000FFFFFFFF000001010100000078000000000000001027
          0000000100004022300D03000000000000000000000000000100000000000000
          0000000100000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000010000000001000000000000000000000000
          0000000000000000FFFFFFFF0000010101000000780000000000000010270000
          00010000FCCF2A04040000000000000000000000000001000000000000000000
          0001000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000100000000010000000000000000000000000000
          000000000000FFFFFFFF00000101010000007800000000000000102700000001
          00001C0E440D0500000000000000000000000000010000000000000000000001
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000001000000000100000000000000000000000000000000
          00000000FFFFFFFF000001010100000078000000000000001027000000010000
          28886A0006000000000000000000000000000100000000000000000000010000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000010000000001000000000000000000000000}
        HorzDivLinesColor = 7368816
        HorzScrollBarStyles.Width = 17
        HorzScrollBarStyles.ButtonSize = 14
        HorzScrollBarStyles.UseSystemMetrics = False
        HorzScrollBarStyles.ThemeMode = ttmNone
        ItemIndent = 14
        LineHeight = 15
        LinesColor = clBtnShadow
        MultiSelect = False
        PlusMinusTransparent = True
        HorzScrollTracking = True
        VertScrollTracking = True
        ShowButtons = False
        ShowLines = False
        StoragePath = '\Tree'
        StripedOddColor = clGray
        StripedEvenColor = 8158332
        StripedItems = True
        TabOrder = 0
        Tracking = False
        TrackColor = clBlack
        VertDivLinesColor = 7368816
        VerticalLines = True
        VertScrollBarStyles.ShowTrackHint = True
        VertScrollBarStyles.Width = 17
        VertScrollBarStyles.ButtonSize = 14
        VertScrollBarStyles.UseSystemMetrics = False
        VertScrollBarStyles.ThemeMode = ttmNone
        ThemeMode = ttmNone
        TextColor = clBtnText
        BkColor = clGray
        OnDragDrop = tvMultiDragDrop
        OnDragOver = tvMultiDragOver
        OnStartDrag = tvMultiStartDrag
      end
    end
    object Panel2: TPanel
      Left = 0
      Top = 411
      Width = 170
      Height = 18
      Align = alBottom
      BevelOuter = bvNone
      Color = 10528425
      Constraints.MaxHeight = 18
      Constraints.MinHeight = 18
      TabOrder = 1
      object sbSelect: TExtBtn
        Left = 1
        Top = 0
        Width = 84
        Height = 18
        Align = alNone
        BevelShow = False
        Caption = 'Ok'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        FlatAlwaysEdge = True
        OnClick = sbSelectClick
      end
      object sbCancel: TExtBtn
        Left = 86
        Top = 0
        Width = 84
        Height = 18
        Align = alNone
        BevelShow = False
        Caption = 'Cancel'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        FlatAlwaysEdge = True
        OnClick = sbCancelClick
      end
    end
    object grdFon: TGradient
      Left = 0
      Top = 0
      Width = 170
      Height = 185
      BeginColor = clGray
      EndColor = 13160660
      FillDirection = fdBottomToUp
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      Caption = 'TGradient'
      TextTop = 5
      TextLeft = 12
      Border = False
      BorderWidth = 1
      BorderColor = clBlack
      Align = alTop
      object mxLabel2: TLabel
        Left = 2
        Top = 155
        Width = 28
        Height = 13
        AutoSize = False
        Caption = 'Hint:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        Transparent = True
      end
      object lbHint: TLabel
        Left = 32
        Top = 155
        Width = 137
        Height = 26
        AutoSize = False
        Caption = '`'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        Transparent = True
        WordWrap = True
      end
      object lbItemName: TLabel
        Left = 32
        Top = 141
        Width = 137
        Height = 13
        AutoSize = False
        Caption = '-'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        Transparent = True
      end
      object mxLabel1: TLabel
        Left = 2
        Top = 141
        Width = 32
        Height = 13
        AutoSize = False
        Caption = 'Item:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        Transparent = True
      end
      object ebExt: TExtBtn
        Left = 0
        Top = 1
        Width = 31
        Height = 16
        Hint = 'Extended information toggle'
        Align = alNone
        AllowAllUp = True
        BevelShow = False
        GroupIndex = 1
        Down = True
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        Glyph.Data = {
          D6050000424DD6050000000000003600000028000000300000000A0000000100
          180000000000A0050000120B0000120B00000000000000000000FFFFFFFFFFFF
          FFFFFFACB3B6A9B0B4A9B0B4ABB2B5FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFACB3B6A9B0B4A9B0B4ABB2B5FFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF84898C424546383A3B383B3C3E40427F
          8487FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF84898C42
          4546383A3B383B3C3E40427F8487FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF2A2B2C
          676B6D989EA1A9B0B4AAB1B4B9C1C4777C7E1B1D1D84898CFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFF2A2B2C676B6D989EA1A9B0B4AAB1B4B9C1C4777C7E1B1D
          1D84898CFFFFFFFFFFFFFFFFFFAEB5B9C6CED23E40420000000000001B1C1CA9
          B0B4AAB1B41213137A7E81FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFAEB5B9C6CED23E
          40420000000000001B1C1CA9B0B4AAB1B41213137A7E81FFFFFF9FA6A99FA6A9
          26282900000000000000000000000004040491979A868B8E1F2020FFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFF9FA6A99FA6A92628290000000000000000000000000404049197
          9A868B8E1F2020FFFFFF5B5F60868B8E000000434647C3CBCF00000000000000
          000080858837393A2F3132B4BBBEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF5B5F60868B8E00000043
          4647C3CBCF00000000000000000080858837393A2F3132B4BBBE969C9F252627
          0000000000002C2E2F090A0A020202000000383A3B2628297E83868B8D8EFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFF969C9F2526270000000000002C2E2F090A0A020202000000383A
          3B2628297E83868B8D8E4E515281868871757844474816171718191A15161650
          53555D6163888E9040434493989AFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4E515281868871757844
          474816171718191A1516165053555D6163888E9040434493989A93999C4B4D4F
          73787A757A7C949A9D9096999096997D83856A6E70525556A1A7AAFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFF93999C4B4D4F73787A757A7C949A9D9096999096997D83856A6E
          70525556A1A7AAFFFFFFFFFFFFFFFFFF80858873787A5255565255565255566E
          727484898CB8BFC3FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF80858873
          787A5255565255565255566E727484898CB8BFC3FFFFFFFFFFFF}
        NumGlyphs = 4
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
        Transparent = False
        FlatAlwaysEdge = True
        OnClick = ebExtClick
      end
      object paImage: TMxPanel
        Left = 31
        Top = 0
        Width = 138
        Height = 138
        BevelOuter = bvLowered
        Caption = '<image>'
        Color = clGray
        TabOrder = 0
        OnPaint = paImagePaint
      end
    end
    object paInfo: TPanel
      Left = 0
      Top = 185
      Width = 170
      Height = 99
      Align = alClient
      BevelOuter = bvNone
      Constraints.MinHeight = 99
      TabOrder = 3
      Visible = False
    end
  end
  object Panel4: TPanel
    Left = 0
    Top = 0
    Width = 177
    Height = 429
    Align = alClient
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object tvItems: TElTree
      Left = 0
      Top = 0
      Width = 177
      Height = 411
      Align = alClient
      AutoExpand = True
      CheckBoxGlyph.Data = {
        D6050000424DD60500000000000036000000280000003C000000080000000100
        180000000000A0050000120B0000120B00000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00
        0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF535353
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF535353FFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000000000FFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFF535353535353535353FFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFF000000000000000000FFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFF535353535353535353FFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FF000000000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF53
        5353535353535353535353535353FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000
        000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF5353535353
        53535353535353535353FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFF000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        535353FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000000000FFFFFFFFFF
        FF000000000000FFFFFFFFFFFFFFFFFF535353535353535353FFFFFFFFFFFF53
        5353535353FFFFFFFFFFFFFFFFFF000000000000000000FFFFFFFFFFFF000000
        000000FFFFFFFFFFFFFFFFFF535353535353535353FFFFFFFFFFFF5353535353
        53FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000000000FFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF535353535353535353FFFFFFFFFFFF
        FFFFFFFFFFFF000000000000FFFFFFFFFFFFFFFFFFFFFFFF000000000000FFFF
        FFFFFFFF535353535353FFFFFFFFFFFFFFFFFFFFFFFF535353535353FFFFFFFF
        FFFF000000000000FFFFFFFFFFFFFFFFFFFFFFFF000000000000FFFFFFFFFFFF
        535353535353FFFFFFFFFFFFFFFFFFFFFFFF535353535353FFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF535353FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000FFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFF535353535353FFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFF000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFF535353535353FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFF000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF535353535353FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFF000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        535353535353FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF535353FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000FFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF535353}
      Color = clWhite
      CustomCheckboxes = True
      CustomPlusMinus = True
      DrawFocusRect = False
      Flat = True
      FocusedSelectColor = 10526880
      FocusedSelectTextColor = clBlack
      FullRowSelect = False
      HeaderColor = 7368816
      HeaderHeight = 19
      HeaderHotTrack = False
      HeaderSections.Data = {
        F1FFFFFF070000000000000000000000FFFFFFFF000001010100000078000000
        000000001027000000010000206F2C0400000000000000000000000000000100
        0000000000000000000100000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000010000000001000000000000
        0000000000000000000000000000FFFFFFFF0000010101000000780000000000
        0000102700000001000018452904010000000000000000000000000001000000
        0000000000000001000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000100000000010000000000000000
        000000000000000000000000FFFFFFFF00000101010000007800000000000000
        1027000000010000AC2976060200000000000000000000000000010000000000
        0000000000010000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000001000000000100000000000000000000
        00000000000000000000FFFFFFFF000001010100000078000000000000001027
        000000010000D8CF160C03000000000000000000000000000100000000000000
        0000000100000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000010000000001000000000000000000000000
        0000000000000000FFFFFFFF0000010101000000780000000000000010270000
        00010000F0A92304040000000000000000000000000001000000000000000000
        0001000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000100000000010000000000000000000000000000
        000000000000FFFFFFFF00000101010000007800000000000000102700000001
        0000106126040500000000000000000000000000010000000000000000000001
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000001000000000100000000000000000000000000000000
        00000000FFFFFFFF000001010100000078000000000000001027000000010000
        1065720006000000000000000000000000000100000000000000000000010000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000010000000001000000000000000000000000}
      HorizontalLines = True
      HorzDivLinesColor = 7368816
      HorzScrollBarStyles.Width = 17
      HorzScrollBarStyles.ButtonSize = 14
      HorzScrollBarStyles.UseSystemMetrics = False
      HorzScrollBarStyles.ThemeMode = ttmNone
      LineHeight = 18
      LinesColor = clBtnShadow
      MinusPicture.Data = {
        F6000000424DF600000000000000360000002800000008000000080000000100
        180000000000C0000000120B0000120B00000000000000000000808080808080
        808080808080808080808080808080808080808080808080808080E0E0E08080
        80808080808080808080808080808080808080E0E0E080808080808080808080
        8080808080808080E0E0E0E0E0E0E0E0E0808080808080808080808080808080
        E0E0E0E0E0E0E0E0E0808080808080808080808080E0E0E0E0E0E0E0E0E0E0E0
        E0E0E0E0808080808080808080E0E0E0E0E0E0E0E0E0E0E0E0E0E0E080808080
        8080808080808080808080808080808080808080808080808080}
      MultiSelect = False
      PlusMinusTransparent = True
      PlusPicture.Data = {
        F6000000424DF600000000000000360000002800000008000000080000000100
        180000000000C0000000120B0000120B00000000000000000000808080808080
        8080808080808080808080808080808080808080808080808080808080808080
        80808080808080808080808080E0E0E0E0E0E080808080808080808080808080
        8080808080E0E0E0E0E0E0E0E0E0E0E0E0808080808080808080808080E0E0E0
        E0E0E0E0E0E0E0E0E0E0E0E0E0E0E0808080808080E0E0E0E0E0E0E0E0E0E0E0
        E0808080808080808080808080E0E0E0E0E0E080808080808080808080808080
        8080808080808080808080808080808080808080808080808080}
      HorzScrollTracking = True
      VertScrollTracking = True
      ShowLines = False
      SortMode = smAdd
      SortType = stCustom
      StoragePath = '\Tree'
      SortUseCase = False
      StripedOddColor = clGray
      StripedEvenColor = 8158332
      StripedItems = True
      TabOrder = 0
      Tracking = False
      TrackColor = 10526880
      VertDivLinesColor = 7368816
      VerticalLines = True
      VertScrollBarStyles.ShowTrackHint = True
      VertScrollBarStyles.Width = 17
      VertScrollBarStyles.ButtonSize = 14
      VertScrollBarStyles.UseSystemMetrics = False
      VertScrollBarStyles.ThemeMode = ttmNone
      ThemeMode = ttmNone
      TextColor = clBtnText
      BkColor = clGray
      OnItemChange = tvItemsItemChange
      OnItemFocused = tvItemsItemFocused
      OnCompareItems = tvItemsCompareItems
      OnDblClick = tvItemsDblClick
      OnKeyPress = tvItemsKeyPress
    end
    object paFind: TPanel
      Left = 0
      Top = 411
      Width = 177
      Height = 18
      Align = alBottom
      Alignment = taLeftJustify
      BevelOuter = bvNone
      Caption = 'Find:'
      Color = 10528425
      TabOrder = 1
      object edFind: TEdit
        Left = 25
        Top = 1
        Width = 125
        Height = 17
        AutoSelect = False
        AutoSize = False
        Color = 10526880
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 0
        OnChange = edFindChange
      end
    end
  end
  object fsStorage: TFormStorage
    IniSection = 'ChoseForm'
    UseRegistry = True
    OnSavePlacement = fsStorageSavePlacement
    OnRestorePlacement = fsStorageRestorePlacement
    StoredProps.Strings = (
      'ebExt.Down'
      'edFind.Text'
      'paRight.Width'
      'paMulti.Height')
    StoredValues = <
      item
        Name = 'EmitterDirX'
        Value = 0
      end
      item
        Name = 'EmitterDirY'
        Value = 0
      end
      item
        Name = 'EmitterDirZ'
        Value = 0
      end>
    Left = 296
    Top = 8
  end
end
