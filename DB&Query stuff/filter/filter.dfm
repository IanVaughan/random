�
 TFILTERFORM 0�  TPF0TfilterForm
filterFormLeftTop2WidthpHeight6CaptionTest FilterFont.CharsetDEFAULT_CHARSET
Font.ColorclWindowTextFont.Height�	Font.NameMS Sans Serif
Font.Style OnShowFormShowPixelsPerInch`
TextHeight TDBGridDBGrid1Left Top WidthhHeight� AlignalClient
DataSourceDataSource1TabOrder TitleFont.CharsetDEFAULT_CHARSETTitleFont.ColorclWindowTextTitleFont.Height�TitleFont.NameMS Sans SerifTitleFont.Style   TPanelPanel1Left Top� WidthhHeight)AlignalBottom
BevelOuterbvNoneTabOrder TSpeedButtongoLeft Top WidthyHeight)
GroupIndexCaption!Filter                           EnabledFlat	OnClickgoClick  TLabelLabel1Left&TopWidthHeightCaptionby  TSpeedButtonparamLeft~Top WidthsHeight)Captionparam                        Flat	OnClick
paramClick  TLabelLabel2Left� TopWidthHeightCaptionon  TEditEdit1Left6TopWidth7HeightTabOrder OnChangeEdit1Change	OnKeyDownEdit1KeyDown  TEdit	paramEditLeft� TopWidth1HeightTabOrderOnChangeparamEditChange	OnKeyDownparamEditKeyDown   	TDatabase	Database1	AliasNameBestDrv	Connected	DatabaseNamedbLoginPromptSessionNameDefaultLeftTop~  TQueryQuery1DatabaseNameBestDrvSQL.Stringsselect *from Route_Segmentswhere Fix_ID = :fixid Params.Data
     fixid        Left`Top~  TDataSourceDataSource1DataSetQuery1Left� Top~   