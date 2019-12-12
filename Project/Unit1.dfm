object Form1: TForm1
  Left = 0
  Top = 0
  AlphaBlend = True
  BorderStyle = bsSingle
  Caption = 'Lines'
  ClientHeight = 620
  ClientWidth = 788
  Color = 4605510
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MT Extra'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDesigned
  PixelsPerInch = 96
  TextHeight = 11
  object Label1: TLabel
    Left = 632
    Top = 40
    Width = 35
    Height = 84
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clHighlightText
    Font.Height = -67
    Font.Name = 'Trebuchet MS'
    Font.Style = []
    ParentFont = False
  end
  object nextStep: TLabel
    Left = 632
    Top = 141
    Width = 112
    Height = 20
    Cursor = crHandPoint
    AutoSize = False
    Caption = #1057#1083#1077#1076#1091#1102#1097#1080#1081' '#1093#1086#1076
    Color = clWhite
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWhite
    Font.Height = 20
    Font.Name = 'Corbel'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    OnClick = nextStepClick
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 2
    OnTimer = Timer1Timer
    Left = 760
    Top = 8
  end
  object Timer2: TTimer
    Enabled = False
    Interval = 2
    OnTimer = Timer2Timer
    Left = 760
    Top = 56
  end
  object Timer3: TTimer
    Enabled = False
    Interval = 40
    OnTimer = Timer3Timer
    Left = 760
    Top = 104
  end
  object Timer4: TTimer
    Enabled = False
    Interval = 30
    OnTimer = Timer4Timer
    Left = 760
    Top = 152
  end
  object MainMenu1: TMainMenu
    Left = 16
    Top = 16
    object N1: TMenuItem
      Caption = #1048#1075#1088#1072
      object N2: TMenuItem
        Caption = #1053#1086#1074#1072#1103' '#1080#1075#1088#1072
        OnClick = NewGame
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object ItemMenuSaveGame: TMenuItem
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1080#1075#1088#1091
        Enabled = False
      end
      object N5: TMenuItem
        Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100' '#1080#1075#1088#1091
      end
    end
    object N6: TMenuItem
      Caption = #1055#1086#1084#1086#1097#1100
      OnClick = ItemMenuHelpClick
    end
    object N7: TMenuItem
      Caption = #1057#1087#1088#1072#1074#1082#1072
      OnClick = ItemMenuRefClick
    end
    object N8: TMenuItem
      Caption = #1042#1099#1093#1086#1076
      OnClick = ExitClick
    end
  end
  object OpenTextFileDialog1: TOpenTextFileDialog
    Left = 64
    Top = 16
  end
end
