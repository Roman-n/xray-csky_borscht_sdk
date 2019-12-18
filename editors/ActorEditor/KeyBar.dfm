object frmKeyBar: TfrmKeyBar
  Left = 88
  Top = 841
  Align = alTop
  BorderIcons = []
  BorderStyle = bsNone
  ClientHeight = 84
  ClientWidth = 1057
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
  ExplicitWidth = 320
  ExplicitHeight = 240
  PixelsPerInch = 96
  TextHeight = 13
  object Panel6: TPanel
    Left = 0
    Top = 0
    Width = 1057
    Height = 24
    Align = alClient
    BevelInner = bvLowered
    Color = 10528425
    TabOrder = 0
    object lbCurrentTime: TMxLabel
      Left = 2
      Top = 2
      Width = 24
      Height = 20
      Align = alLeft
      Alignment = taCenter
      AutoSize = False
      Caption = '...'
      Color = 10528425
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      ShadowColor = 13158600
      ShadowPos = spRightBottom
      Transparent = True
    end
    object Panel1: TPanel
      Left = 948
      Top = 2
      Width = 107
      Height = 20
      Align = alRight
      BevelOuter = bvNone
      Color = 10528425
      TabOrder = 0
      object Label1: TLabel
        Left = 2
        Top = 4
        Width = 25
        Height = 13
        Caption = 'LOD:'
      end
      object seLOD: TMultiObjSpinEdit
        Left = 30
        Top = 4
        Width = 37
        Height = 14
        LWSensitivity = 0.100000000000000000
        ButtonKind = bkLightWave
        Increment = 0.010000000000000000
        MaxValue = 1.000000000000000000
        ValueType = vtFloat
        Value = 1.000000000000000000
        BorderStyle = bsNone
        Color = 10526880
        TabOrder = 0
        OnLWChange = seLODLWChange
        OnExit = seLODExit
        OnKeyPress = seLODKeyPress
      end
      object spinTimeFactor: TMultiObjSpinEdit
        Left = 69
        Top = 5
        Width = 36
        Height = 14
        LWSensitivity = 0.020000000000000000
        ButtonKind = bkLightWave
        Increment = 0.010000000000000000
        MaxValue = 10.000000000000000000
        MinValue = 0.010000000000000000
        ValueType = vtFloat
        Value = 1.000000000000000000
        BorderStyle = bsNone
        Color = 10526880
        TabOrder = 1
        OnLWChange = spinTimeFactorLWChange
        OnExit = spinTimeFactorExit
        OnKeyPress = spinTimeFactorKeyPress
      end
    end
    object Panel2: TPanel
      Left = 26
      Top = 2
      Width = 922
      Height = 20
      Align = alClient
      BevelOuter = bvNone
      Color = 10528425
      TabOrder = 1
      object Panel3: TPanel
        Left = 0
        Top = 0
        Width = 35
        Height = 290
        BevelOuter = bvNone
        Color = 10528425
        TabOrder = 0
        object stStartTime: TStaticText
          Left = 0
          Top = 0
          Width = 35
          Height = 290
          Align = alClient
          AutoSize = False
          BorderStyle = sbsSunken
          Color = 10526880
          Font.Charset = DEFAULT_CHARSET
          Font.Color = 12582911
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentColor = False
          ParentFont = False
          TabOrder = 0
        end
      end
      object Panel4: TPanel
        Left = 0
        Top = 0
        Width = 887
        Height = 20
        Align = alClient
        BevelOuter = bvNone
        Color = 10528425
        TabOrder = 1
        object Gradient1: TGradient
          Left = 0
          Top = 0
          Width = 887
          Height = 20
          BeginColor = 6118749
          EndColor = 11777977
          FillDirection = fdUpToBottom
          NumberOfColors = 32
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          Caption = ' '
          TextTop = 5
          TextLeft = 12
          Border = True
          BorderWidth = 1
          BorderColor = 8226442
          Align = alClient
          object anm_track: TElTrackBar
            Left = 23
            Top = 1
            Width = 863
            Height = 18
            Max = 100
            Page = 50
            Position = 50
            TickPosition = tpNone
            ThumbType = tstBox
            TrackColor = 10528425
            ThumbWidth = 5
            ActiveBorderType = fbtLine
            InactiveBorderType = fbtFlat
            Align = alClient
            Color = clGray
            ParentColor = False
            TabOrder = 0
          end
          object auto_ch: TElCheckBox
            Left = 1
            Top = 1
            Width = 22
            Height = 18
            State = cbChecked
            Checked = True
            Flat = True
            FlatAlways = True
            TabOrder = 1
            Color = clInactiveCaptionText
            ParentColor = False
            Align = alLeft
          end
        end
      end
      object Panel5: TPanel
        Left = 887
        Top = 0
        Width = 35
        Height = 20
        Align = alRight
        BevelOuter = bvNone
        Color = 10528425
        TabOrder = 2
        object stEndTime: TStaticText
          Left = 0
          Top = 0
          Width = 35
          Height = 20
          Align = alClient
          AutoSize = False
          BorderStyle = sbsSunken
          Color = 10526880
          Font.Charset = DEFAULT_CHARSET
          Font.Color = 12582911
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentColor = False
          ParentFont = False
          TabOrder = 0
        end
      end
    end
  end
  object PanelCh1: TMxPanel
    Left = 0
    Top = 24
    Width = 1057
    Height = 15
    Align = alBottom
    TabOrder = 1
    OnPaint = PanelCh1Paint
    object Label2: TLabel
      Left = 5
      Top = 1
      Width = 18
      Height = 13
      Caption = 'Left'
    end
    object BtnUpCh1: TElGraphicButton
      Left = 974
      Top = 1
      Width = 41
      Height = 13
      Caption = 'Up'
      Align = alRight
      OnClick = BtnUpCh1Click
    end
    object BtnDownCh1: TElGraphicButton
      Left = 1015
      Top = 1
      Width = 41
      Height = 13
      Caption = 'Down'
      Align = alRight
      OnClick = BtnDownCh1Click
    end
    object BtnDelCh1: TElGraphicButton
      Left = 933
      Top = 1
      Width = 41
      Height = 13
      Caption = 'Del'
      Align = alRight
      OnClick = BtnDelCh1Click
    end
  end
  object PanelCh2: TMxPanel
    Left = 0
    Top = 39
    Width = 1057
    Height = 15
    Align = alBottom
    TabOrder = 2
    OnPaint = PanelCh2Paint
    object Label3: TLabel
      Left = 5
      Top = 1
      Width = 25
      Height = 13
      Caption = 'Right'
    end
    object BtnUpCh2: TElGraphicButton
      Left = 974
      Top = 1
      Width = 41
      Height = 13
      Caption = 'Up'
      Align = alRight
      OnClick = BtnUpCh2Click
    end
    object BtnDownCh2: TElGraphicButton
      Left = 1015
      Top = 1
      Width = 41
      Height = 13
      Caption = 'Down'
      Align = alRight
      OnClick = BtnDownCh2Click
    end
    object BtnDelCh2: TElGraphicButton
      Left = 933
      Top = 1
      Width = 41
      Height = 13
      Caption = 'Del'
      Align = alRight
      OnClick = BtnDelCh2Click
    end
  end
  object PanelCh3: TMxPanel
    Left = 0
    Top = 54
    Width = 1057
    Height = 15
    Align = alBottom
    TabOrder = 3
    OnPaint = PanelCh3Paint
    object Label4: TLabel
      Left = 5
      Top = 1
      Width = 24
      Height = 13
      Caption = 'Left2'
    end
    object BtnUpCh3: TElGraphicButton
      Left = 974
      Top = 1
      Width = 41
      Height = 13
      Caption = 'Up'
      Align = alRight
      OnClick = BtnUpCh3Click
    end
    object BtnDownCh3: TElGraphicButton
      Left = 1015
      Top = 1
      Width = 41
      Height = 13
      Caption = 'Down'
      Align = alRight
      OnClick = BtnDownCh3Click
    end
    object BtnDelCh3: TElGraphicButton
      Left = 933
      Top = 1
      Width = 41
      Height = 13
      Caption = 'Del'
      Align = alRight
      OnClick = BtnDelCh3Click
    end
  end
  object PanelCh4: TMxPanel
    Left = 0
    Top = 69
    Width = 1057
    Height = 15
    Align = alBottom
    TabOrder = 4
    OnPaint = PanelCh4Paint
    object Label5: TLabel
      Left = 5
      Top = 1
      Width = 31
      Height = 13
      Caption = 'Right2'
    end
    object BtnUpCh4: TElGraphicButton
      Left = 974
      Top = 1
      Width = 41
      Height = 13
      Caption = 'Up'
      Align = alRight
      OnClick = BtnUpCh4Click
    end
    object BtnDownCh4: TElGraphicButton
      Left = 1015
      Top = 1
      Width = 41
      Height = 13
      Caption = 'Down'
      Align = alRight
      OnClick = BtnDownCh4Click
    end
    object BtnDelCh4: TElGraphicButton
      Left = 933
      Top = 1
      Width = 41
      Height = 13
      Caption = 'Del'
      Align = alRight
      OnClick = BtnDelCh4Click
    end
  end
end
