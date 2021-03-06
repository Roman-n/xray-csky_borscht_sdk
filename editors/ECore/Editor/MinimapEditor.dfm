object TMinimapEditor: TTMinimapEditor
  Left = 360
  Top = 420
  Caption = 'TMinimapEditor'
  ClientHeight = 414
  ClientWidth = 585
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 333
    Width = 585
    Height = 81
    Align = alBottom
    BevelOuter = bvNone
    Color = 10528425
    TabOrder = 0
    ExplicitTop = 334
    ExplicitWidth = 593
    object btnLoad: TExtBtn
      Left = 0
      Top = 2
      Width = 57
      Height = 17
      Align = alNone
      BevelShow = False
      Caption = 'Load'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Kind = knNone
      ParentFont = False
      FlatAlwaysEdge = True
      OnClick = btnLoadClick
    end
    object MxLabel1: TMxLabel
      Left = 0
      Top = 29
      Width = 56
      Height = 13
      Caption = 'BoundRect'
    end
    object MxLabel2: TMxLabel
      Left = 72
      Top = 5
      Width = 39
      Height = 13
      Caption = 'LeftTop'
    end
    object MxLabel3: TMxLabel
      Left = 184
      Top = 5
      Width = 60
      Height = 13
      Caption = 'RightBottom'
    end
    object ElFloatSpinEditX1: TElFloatSpinEdit
      Left = 64
      Top = 24
      Width = 100
      Height = 21
      Cursor = crIBeam
      Increment = 1.000000000000000000
      LargeIncrement = 10.000000000000000000
      MaxValue = 10000.000000000000000000
      MinValue = -10000.000000000000000000
      OnChange = ElFloatSpinEditX1Change
      Ctl3D = True
      LineBorderActiveColor = clBlack
      LineBorderInactiveColor = clBlack
      ParentColor = False
      ParentCtl3D = False
      TabOrder = 0
    end
    object ElFloatSpinEditZ1: TElFloatSpinEdit
      Left = 64
      Top = 48
      Width = 100
      Height = 21
      Cursor = crIBeam
      Increment = 1.000000000000000000
      LargeIncrement = 10.000000000000000000
      MaxValue = 10000.000000000000000000
      MinValue = -10000.000000000000000000
      OnChange = ElFloatSpinEditX1Change
      Ctl3D = True
      LineBorderActiveColor = clBlack
      LineBorderInactiveColor = clBlack
      ParentColor = False
      ParentCtl3D = False
      TabOrder = 1
    end
    object ElFloatSpinEditX2: TElFloatSpinEdit
      Left = 184
      Top = 24
      Width = 100
      Height = 21
      Cursor = crIBeam
      Increment = 1.000000000000000000
      LargeIncrement = 10.000000000000000000
      MaxValue = 10000.000000000000000000
      MinValue = -10000.000000000000000000
      OnChange = ElFloatSpinEditX1Change
      Ctl3D = True
      LineBorderActiveColor = clBlack
      LineBorderInactiveColor = clBlack
      ParentColor = False
      ParentCtl3D = False
      TabOrder = 2
    end
    object ElFloatSpinEditZ2: TElFloatSpinEdit
      Left = 184
      Top = 48
      Width = 100
      Height = 21
      Cursor = crIBeam
      Increment = 1.000000000000000000
      LargeIncrement = 10.000000000000000000
      MaxValue = 10000.000000000000000000
      MinValue = -10000.000000000000000000
      OnChange = ElFloatSpinEditX1Change
      Ctl3D = True
      LineBorderActiveColor = clBlack
      LineBorderInactiveColor = clBlack
      ParentColor = False
      ParentCtl3D = False
      TabOrder = 3
    end
    object result_edit: TElAdvancedEdit
      Left = 296
      Top = 48
      Width = 265
      Height = 21
      ReadOnly = True
      TabOrder = 4
      Text = 'bound_rect='
    end
  end
  object imgPanel: TMxPanel
    Left = 0
    Top = 0
    Width = 585
    Height = 333
    Align = alClient
    Color = 10528425
    TabOrder = 1
    OnMouseDown = imgPanelMouseDown
    OnResize = imgPanelResize
    OnPaint = imgPanelPaint
    ExplicitWidth = 593
    ExplicitHeight = 334
  end
end
