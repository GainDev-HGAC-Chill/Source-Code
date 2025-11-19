USE [DR2_local]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS ( SELECT 1 FROM sys.all_objects WHERE OBJECT_ID = OBJECT_ID( N'dbo.TB_ChannelEffect' ) )
BEGIN
CREATE TABLE [dbo].[TB_ChannelEffect](
	[f_Idx] [int] NOT NULL,
	[f_EffectId] [int] NOT NULL,
	[f_Memo] [nvarchar](100) NOT NULL,
	[f_Realm] [smallint] NOT NULL,
	[f_Channel] [smallint] NOT NULL,
	[f_Min_Lv] [smallint] NOT NULL,
	[f_Max_Lv] [smallint] NOT NULL,
 CONSTRAINT [PK_TB_ChannelEffect] PRIMARY KEY CLUSTERED 
(
	[f_Realm] ASC,
	[f_Channel] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
END
GO