object frmOneColor: TfrmOneColor
  Left = 556
  Top = 385
  Align = alTop
  BorderIcons = []
  BorderStyle = bsNone
  ClientHeight = 58
  ClientWidth = 196
  Color = 10528425
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  Scaled = False
  OnClose = FormClose
  DesignSize = (
    196
    58)
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 0
    Top = 0
    Width = 195
    Height = 58
    Anchors = [akLeft, akTop, akRight, akBottom]
  end
  object Bevel2: TBevel
    Left = 1
    Top = 1
    Width = 193
    Height = 56
    Anchors = [akLeft, akTop, akRight, akBottom]
    Style = bsRaised
  end
  object mcColor: TMultiObjColor
    Left = 3
    Top = 15
    Width = 23
    Height = 39
    Anchors = [akLeft, akTop, akBottom]
    Shape = stRoundRect
    OnMouseDown = mcColorMouseDown
  end
  object ebMultiRemove: TExtBtn
    Left = 3
    Top = 2
    Width = 23
    Height = 13
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
  object tvDOList: TElTree
    Left = 27
    Top = 2
    Width = 166
    Height = 54
    Cursor = crDefault
    LeftPosition = 0
    DragCursor = crDrag
    AlwaysKeepSelection = False
    AutoCollapse = False
    AutoExpand = True
    Anchors = [akLeft, akTop, akRight, akBottom]
    DockOrientation = doNoOrient
    DefaultSectionWidth = 120
    BorderStyle = bsNone
    BorderSides = [ebsLeft, ebsRight, ebsTop, ebsBottom]
    DragAllowed = True
    DrawFocusRect = False
    ExplorerEditMode = False
    Flat = True
    FocusedSelectColor = 10526880
    FocusedSelectTextColor = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    FullRowSelect = False
    GradientSteps = 64
    HeaderHeight = 19
    HeaderHotTrack = False
    HeaderSections.Data = {
      F4FFFFFF0700000048B0530A00000000FFFFFFFF000001010100315C78000000
      000000001027000000010031BC55640E0000000000002E5C0000000000000172
      000000000000000000010000000000005C7872536572766572456E7469746965
      733B2E2E5C2E2E5C7872456E67696E653B456469743B663A5C50524F4752417E
      315C626F726C616E645C434255494C4490000000010000000001000000000000
      00000000000048B0530A00000000FFFFFFFF000001010100315C780000000000
      000010270000000100315C598B0D0100000000002E5C00000000000001720000
      00000000000000010000000000005C7872536572766572456E7469746965733B
      2E2E5C2E2E5C7872456E67696E653B456469743B663A5C50524F4752417E315C
      626F726C616E645C434255494C44900000000100000000010000000000000000
      0000000048B0530A00000000FFFFFFFF000001010100315C7800000000000000
      10270000000100310CC9BA0C0200000000002E5C000000000000017200000000
      0000000000010000000000005C7872536572766572456E7469746965733B2E2E
      5C2E2E5C7872456E67696E653B456469743B663A5C50524F4752417E315C626F
      726C616E645C434255494C449000000001000000000100000000000000000000
      000048B0530A00000000FFFFFFFF000001010100315C78000000000000001027
      000000010031A0727F0D0300000000002E5C0000000000000172000000000000
      000000010000000000005C7872536572766572456E7469746965733B2E2E5C2E
      2E5C7872456E67696E653B456469743B663A5C50524F4752417E315C626F726C
      616E645C434255494C4490000000010000000001000000000000000000000000
      48B0530A00000000FFFFFFFF000001010100315C780000000000000010270000
      000100318C58E70E0400000000002E5C00000000000001720000000000000000
      00010000000000005C7872536572766572456E7469746965733B2E2E5C2E2E5C
      7872456E67696E653B456469743B663A5C50524F4752417E315C626F726C616E
      645C434255494C449000000001000000000100000000000000000000000048B0
      530A00000000FFFFFFFF000001010100315C7800000000000000102700000001
      0031CC78BD0C0500000000002E5C000000000000017200000000000000000001
      0000000000005C7872536572766572456E7469746965733B2E2E5C2E2E5C7872
      456E67696E653B456469743B663A5C50524F4752417E315C626F726C616E645C
      434255494C449000000001000000000100000000000000000000000048B0530A
      00000000FFFFFFFF000001010100315C78000000000000001027000000010031
      9C6D900C0600000000002E5C0000000000000172000000000000000000010000
      000000005C7872536572766572456E7469746965733B2E2E5C2E2E5C7872456E
      67696E653B456469743B663A5C50524F4752417E315C626F726C616E645C4342
      55494C4490000000010000000001000000000000000000000000}
    HeaderFont.Charset = DEFAULT_CHARSET
    HeaderFont.Color = clWindowText
    HeaderFont.Height = -11
    HeaderFont.Name = 'MS Sans Serif'
    HeaderFont.Style = []
    HorizontalLines = True
    HorzDivLinesColor = 7368816
    HorzScrollBarStyles.ShowTrackHint = False
    HorzScrollBarStyles.Width = 17
    HorzScrollBarStyles.ButtonSize = 14
    HorzScrollBarStyles.UseSystemMetrics = False
    HorzScrollBarStyles.UseXPThemes = False
    IgnoreEnabled = False
    IncrementalSearch = False
    ItemIndent = 9
    KeepSelectionWithinLevel = False
    LineBorderActiveColor = clBlack
    LineBorderInactiveColor = clBlack
    LineHeight = 16
    LinesColor = clBtnShadow
    MouseFrameSelect = True
    MultiSelect = False
    OwnerDrawMask = '~~@~~'
    ParentFont = False
    PlusMinusTransparent = True
    ScrollbarOpposite = False
    ScrollTracking = True
    ShowButtons = False
    ShowLeafButton = False
    ShowLines = False
    ShowRootButtons = False
    StoragePath = '\Tree'
    TabOrder = 0
    TabStop = True
    Tracking = False
    TrackColor = clBlack
    VertScrollBarStyles.ShowTrackHint = True
    VertScrollBarStyles.Width = 17
    VertScrollBarStyles.ButtonSize = 14
    VertScrollBarStyles.UseSystemMetrics = False
    VertScrollBarStyles.UseXPThemes = False
    VirtualityLevel = vlNone
    UseXPThemes = False
    TextColor = clBtnText
    BkColor = clGray
    OnItemFocused = tvDOListItemFocused
    OnDragDrop = tvDOListDragDrop
    OnDragOver = tvDOListDragOver
    OnStartDrag = tvDOListStartDrag
  end
end
