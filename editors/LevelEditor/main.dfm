object frmMain: TfrmMain
  Left = 314
  Top = 248
  Width = 805
  Height = 465
  Color = clBtnFace
  Constraints.MinHeight = 446
  Constraints.MinWidth = 660
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  Menu = mmMainMenu
  OldCreateOrder = False
  Position = poDefault
  Scaled = False
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnMouseWheel = FormMouseWheel
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object spLeftBar: TSplitter
    Left = 555
    Top = 0
    Width = 4
    Height = 394
    Cursor = crHSplit
    Align = alRight
    Color = clMedGray
    ParentColor = False
    Visible = False
  end
  object paLeftBar: TPanel
    Left = 559
    Top = 0
    Width = 238
    Height = 394
    Align = alRight
    BevelInner = bvLowered
    BevelOuter = bvNone
    TabOrder = 0
    Visible = False
    object paTools: TPanel
      Left = 1
      Top = 1
      Width = 236
      Height = 16
      Align = alTop
      TabOrder = 0
      DesignSize = (
        236
        16)
      object APHeadLabel2: TLabel
        Left = 1
        Top = 1
        Width = 234
        Height = 13
        Align = alTop
        Alignment = taCenter
        Caption = 'Toolbar'
        Color = clGray
        ParentColor = False
        OnClick = TopClick
      end
      object sbToolsMin: TExtBtn
        Left = 223
        Top = 0
        Width = 11
        Height = 13
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
          FFFFFFFFFFFFFFFFFF000000FFFFFF000000FFFFFFFFFFFFFFFFFFFFFFFF0000
          00000000FFFFFF000000FFFFFFFFFFFFFFFFFF000000000000000000FFFFFF00
          0000FFFFFFFFFFFF000000000000000000000000FFFFFF000000FFFFFFFFFFFF
          FFFFFF000000000000000000FFFFFF000000FFFFFFFFFFFFFFFFFFFFFFFF0000
          00000000FFFFFF000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000FFFFFF00
          0000}
        ParentFont = False
        OnClick = sbToolsMinClick
      end
      object ebAllMin: TExtBtn
        Left = 3
        Top = 2
        Width = 11
        Height = 11
        Align = alNone
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        Glyph.Data = {
          AE000000424DAE00000000000000360000002800000006000000060000000100
          18000000000078000000120B0000120B00000000000000000000FFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          00000B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B0B00000B0B0B0B0B0B0B0B0B0B
          0B0B0B0B0B0B0B0B0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000}
        ParentFont = False
        OnClick = ebAllMinClick
      end
      object ebAllMax: TExtBtn
        Left = 15
        Top = 2
        Width = 11
        Height = 11
        Align = alNone
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        Glyph.Data = {
          AE000000424DAE00000000000000360000002800000006000000060000000100
          18000000000078000000120B0000120B00000000000000000000FFFFFFFFFFFF
          1C1C1C1C1C1CFFFFFFFFFFFF0000FFFFFFFFFFFF191919191919FFFFFFFFFFFF
          00001B1B1B1717170303030303031717171B1B1B00001B1B1B17171703030303
          03031717171B1B1B0000FFFFFFFFFFFF191919191919FFFFFFFFFFFF0000FFFF
          FFFFFFFF1C1C1C1C1C1CFFFFFFFFFFFF0000}
        ParentFont = False
        OnClick = ebAllMaxClick
      end
    end
  end
  object paBottomBar: TPanel
    Left = 0
    Top = 394
    Width = 797
    Height = 17
    Align = alBottom
    BevelInner = bvLowered
    BevelOuter = bvNone
    TabOrder = 1
  end
  object paMain: TPanel
    Left = 0
    Top = 0
    Width = 555
    Height = 394
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 2
    object paTopBar: TPanel
      Left = 0
      Top = 0
      Width = 25
      Height = 394
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 0
      Visible = False
    end
    object paRender: TPanel
      Left = 25
      Top = 0
      Width = 530
      Height = 394
      Align = alClient
      BevelOuter = bvNone
      Color = 4868682
      TabOrder = 1
      OnResize = paRenderResize
      object D3DWindow: TD3DWindow
        Left = 6
        Top = 6
        Width = 513
        Height = 371
        FocusedColor = 9502719
        UnfocusedColor = 9211020
        OnChangeFocus = D3DWindowChangeFocus
        BorderStyle = bsNone
        Color = 5592405
        TabOrder = 0
        OnKeyDown = D3DWindowKeyDown
        OnKeyPress = D3DWindowKeyPress
        OnKeyUp = D3DWindowKeyUp
        OnMouseDown = D3DWindowMouseDown
        OnMouseMove = D3DWindowMouseMove
        OnMouseUp = D3DWindowMouseUp
        OnResize = D3DWindowResize
        OnPaint = D3DWindowPaint
      end
    end
  end
  object fsStorage: TFormStorage
    IniSection = 'Main Form'
    Options = [fpPosition]
    RegistryRoot = prLocalMachine
    Version = 1
    OnSavePlacement = fsStorageSavePlacement
    StoredProps.Strings = (
      'paLeftBar.Tag'
      'paLeftBar.Width')
    StoredValues = <>
    Left = 161
    Top = 33
  end
  object tmRefresh: TTimer
    Enabled = False
    OnTimer = tmRefreshTimer
    Left = 129
    Top = 33
  end
  object mmMainMenu: TMainMenu
    Left = 192
    Top = 32
    object miFile: TMenuItem
      Caption = 'File'
      object miClear: TMenuItem
        Caption = 'Clear'
        OnClick = miClearClick
      end
      object miOpen: TMenuItem
        Caption = 'Open'
        OnClick = miOpenClick
      end
      object miSave: TMenuItem
        Caption = 'Save'
        OnClick = miSaveClick
      end
      object miSaveAs: TMenuItem
        Caption = 'Save As...'
        OnClick = miSaveAsClick
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object miOpenSelection: TMenuItem
        Caption = 'Open Selection'
        OnClick = miOpenSelectionClick
      end
      object miSaveSelection: TMenuItem
        Caption = 'Save Selection As...'
        OnClick = miSaveSelectionClick
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object miMakePack: TMenuItem
        Caption = 'Make Pack'
        OnClick = miMakePackClick
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object miQuit: TMenuItem
        Caption = 'Quit'
        OnClick = miQuitClick
      end
    end
    object Edit1: TMenuItem
      Caption = 'Edit'
      object miUndo: TMenuItem
        Caption = 'Undo'
        OnClick = miUndoClick
      end
      object miRedo: TMenuItem
        Caption = 'Redo'
        OnClick = miRedoClick
      end
      object N5: TMenuItem
        Caption = '-'
      end
      object miCut: TMenuItem
        Caption = 'Cut'
        OnClick = miCutClick
      end
      object miCopy: TMenuItem
        Caption = 'Copy'
        OnClick = miCopyClick
      end
      object miPaste: TMenuItem
        Caption = 'Paste'
        OnClick = miPasteClick
      end
      object miDelete: TMenuItem
        Caption = 'Delete'
        OnClick = miDeleteClick
      end
      object N6: TMenuItem
        Caption = '-'
      end
      object miSelectAll: TMenuItem
        Caption = 'Select All'
        OnClick = miSelectAllClick
      end
      object miDeselectAll: TMenuItem
        Caption = 'Deselect All'
        OnClick = miDeselectAllClick
      end
      object miInvertSelection: TMenuItem
        Caption = 'Invert Selection'
        OnClick = miInvertSelectionClick
      end
      object N7: TMenuItem
        Caption = '-'
      end
      object HideSelected1: TMenuItem
        Caption = 'Hide Selected'
        OnClick = HideSelected1Click
      end
      object HideUnselected1: TMenuItem
        Caption = 'Hide Unselected'
        OnClick = HideUnselected1Click
      end
      object HideAll1: TMenuItem
        Caption = 'Hide All'
        OnClick = HideAll1Click
      end
      object Unhideall1: TMenuItem
        Caption = 'Unhide all'
        OnClick = Unhideall1Click
      end
      object N21: TMenuItem
        Caption = '-'
      end
      object MultiRename1: TMenuItem
        Caption = 'Multi Rename'
        OnClick = MultiRename1Click
      end
      object N20: TMenuItem
        Caption = '-'
      end
      object Properties1: TMenuItem
        Caption = 'Properties'
        OnClick = Properties1Click
      end
    end
    object Scene1: TMenuItem
      Caption = 'Scene'
      object Options1: TMenuItem
        Caption = 'Options'
        OnClick = Options1Click
      end
      object N8: TMenuItem
        Caption = '-'
      end
      object Validate1: TMenuItem
        Caption = 'Validate'
        OnClick = Validate1Click
      end
      object N9: TMenuItem
        Caption = '-'
      end
      object SummaryInfo1: TMenuItem
        Caption = 'Summary Info'
        OnClick = SummaryInfo1Click
      end
      object HighlightTexture1: TMenuItem
        Caption = 'Highlight Texture...'
        OnClick = HighlightTexture1Click
      end
      object N10: TMenuItem
        Caption = '-'
      end
      object ClearDebugDraw1: TMenuItem
        Caption = 'Clear Debug Draw'
        OnClick = ClearDebugDraw1Click
      end
      object N11: TMenuItem
        Caption = '-'
      end
      object ExportentireSceneasObj1: TMenuItem
        Caption = 'Export entire Scene as Obj'
        OnClick = ExportentireSceneasObj1Click
      end
      object Exportselection1: TMenuItem
        Caption = 'Export selection as Obj'
        OnClick = Exportselection1Click
      end
      object N4: TMenuItem
        Caption = '-'
      end
      object miRun: TMenuItem
        Caption = 'Run'
        OnClick = miRunClick
      end
    end
    object Compile1: TMenuItem
      Caption = 'Compile'
      object miBuild: TMenuItem
        Caption = 'Build'
        OnClick = miBuildClick
      end
      object N12: TMenuItem
        Caption = '-'
      end
      object miMakeGame: TMenuItem
        Caption = 'Make Game'
        OnClick = miMakeGameClick
      end
      object miMakeDetails: TMenuItem
        Caption = 'Make Details'
        OnClick = miMakeDetailsClick
      end
      object miMakeHOM: TMenuItem
        Caption = 'Make HOM'
        OnClick = miMakeHOMClick
      end
      object miMakeSoundOccluder: TMenuItem
        Caption = 'Make Sound Occluder'
        OnClick = miMakeSoundOccluderClick
      end
      object miMakeAIMap: TMenuItem
        Caption = 'Make AI-Map'
        OnClick = miMakeAIMapClick
      end
      object N13: TMenuItem
        Caption = '-'
      end
      object ImportErrorList1: TMenuItem
        Caption = 'Import Error List'
        OnClick = ImportErrorList1Click
      end
      object ExportErrorList1: TMenuItem
        Caption = 'Export Error List'
        OnClick = ExportErrorList1Click
      end
      object ClearErrorList1: TMenuItem
        Caption = 'Clear Error List'
        OnClick = ClearErrorList1Click
      end
      object N22: TMenuItem
        Caption = '-'
      end
      object miCompileLevel: TMenuItem
        Caption = 'Compile level'
        OnClick = miCompileLevelClick
      end
      object miCompileDetails: TMenuItem
        Caption = 'Compile details'
        OnClick = miCompileDetailsClick
      end
      object miCompileAIMap: TMenuItem
        Caption = 'Compile AI-map'
        OnClick = miCompileAIMapClick
      end
      object miCompileSpawn: TMenuItem
        Caption = 'Compile spawn'
        OnClick = miCompileSpawnClick
      end
    end
    object Objects1: TMenuItem
      Caption = 'Objects'
      object LibraryEditor1: TMenuItem
        Caption = 'Library Editor'
        OnClick = LibraryEditor1Click
      end
      object N14: TMenuItem
        Caption = '-'
      end
      object ReloadObjects1: TMenuItem
        Caption = 'Reload Objects'
        OnClick = ReloadObjects1Click
      end
      object CleanLibrary1: TMenuItem
        Caption = 'Clean Library'
        OnClick = CleanLibrary1Click
      end
      object ClipEditor1: TMenuItem
        Caption = 'Clip Editor'
        OnClick = ClipEditor1Click
      end
    end
    object Images1: TMenuItem
      Caption = 'Images'
      object ImageEditor1: TMenuItem
        Caption = 'Image Editor'
        OnClick = ImageEditor1Click
      end
      object N15: TMenuItem
        Caption = '-'
      end
      object ReloadTextures1: TMenuItem
        Caption = 'Reload Textures'
        OnClick = ReloadTextures1Click
      end
      object N16: TMenuItem
        Caption = '-'
      end
      object SychronizeTextures1: TMenuItem
        Caption = 'Sychronize Textures'
        OnClick = SychronizeTextures1Click
      end
      object CheckNewTextures1: TMenuItem
        Caption = 'Check New Textures'
        OnClick = CheckNewTextures1Click
      end
      object N17: TMenuItem
        Caption = '-'
      end
      object EditMinimap1: TMenuItem
        Caption = 'Edit Minimap'
        OnClick = EditMinimap1Click
      end
      object SynchronizeTHM1: TMenuItem
        Caption = 'Synchronize THM'
        OnClick = SynchronizeTHM1Click
      end
    end
    object Sounds1: TMenuItem
      Caption = 'Sounds'
      object SoundEditor1: TMenuItem
        Caption = 'Sound Editor'
        OnClick = SoundEditor1Click
      end
      object N18: TMenuItem
        Caption = '-'
      end
      object SynchronizeSounds1: TMenuItem
        Caption = 'Synchronize Sounds'
        OnClick = SynchronizeSounds1Click
      end
      object N19: TMenuItem
        Caption = '-'
      end
      object RefreshEnvironmentLibrary1: TMenuItem
        Caption = 'Refresh Environment Library'
        OnClick = RefreshEnvironmentLibrary1Click
      end
      object RefreshEnvironmentGeometry1: TMenuItem
        Caption = 'Refresh Environment Geometry'
        OnClick = RefreshEnvironmentGeometry1Click
      end
      object LoadSoundOccluder1: TMenuItem
        Caption = 'Load Sound Occluder'
        OnClick = LoadSoundOccluder1Click
      end
    end
    object Other1: TMenuItem
      Caption = 'Other'
      object LightAnimEditor1: TMenuItem
        Caption = 'Light Anim Editor'
        OnClick = LightAnimEditor1Click
      end
      object ObjectList1: TMenuItem
        Caption = 'Object List'
        OnClick = ObjectList1Click
      end
      object Preferences1: TMenuItem
        Caption = 'Preferences'
        OnClick = Preferences1Click
      end
      object N23: TMenuItem
        Caption = '-'
      end
      object About1: TMenuItem
        Caption = 'About...'
        OnClick = About1Click
      end
    end
  end
end
