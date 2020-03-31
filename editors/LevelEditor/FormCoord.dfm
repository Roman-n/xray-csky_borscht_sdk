object frmCoord: TfrmCoord
  Left = 299
  Top = 111
  BorderStyle = bsDialog
  Caption = 'FormCoord'
  ClientHeight = 44
  ClientWidth = 269
  Color = 10528425
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object ebCancel: TExtBtn
    Left = 192
    Top = 24
    Width = 73
    Height = 17
    Align = alNone
    BtnColor = 10528425
    Caption = 'Cancel'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    Transparent = False
    FlatAlwaysEdge = True
    OnClick = ebCancelClick
  end
  object ebOk: TExtBtn
    Left = 112
    Top = 24
    Width = 73
    Height = 17
    Align = alNone
    BtnColor = 10528425
    Caption = 'OK'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    Transparent = False
    FlatAlwaysEdge = True
    OnClick = ebOkClick
  end
  object edCoord: TEdit
    Left = 0
    Top = 0
    Width = 265
    Height = 21
    Color = 10526880
    TabOrder = 0
    Text = 'edCoord'
  end
end
