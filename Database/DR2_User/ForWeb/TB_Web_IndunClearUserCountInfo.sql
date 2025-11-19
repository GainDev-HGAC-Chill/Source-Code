USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_Web_IndunClearUserCountInfo]    Script Date: 06/16/2010 18:16:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_Web_IndunClearUserCountInfo](
	[f_RealmNo] [int] NOT NULL,
	[f_GroundNo] [int] NOT NULL,
	[f_YesterdayCount] [bigint] NOT NULL,
	[f_TodayCount] [bigint] NOT NULL,
	[f_LastTodayUpdate] [datetime] NOT NULL,
 CONSTRAINT [PK_TB_Web_IndunClearUserCountInfo] PRIMARY KEY CLUSTERED 
(
	[f_RealmNo] ASC,
	[f_GroundNo] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'렐름 번호' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Web_IndunClearUserCountInfo', @level2type=N'COLUMN',@level2name=N'f_RealmNo'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'그라운드 번호' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Web_IndunClearUserCountInfo', @level2type=N'COLUMN',@level2name=N'f_GroundNo'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'어제 인원' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Web_IndunClearUserCountInfo', @level2type=N'COLUMN',@level2name=N'f_YesterdayCount'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'금일 인원' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Web_IndunClearUserCountInfo', @level2type=N'COLUMN',@level2name=N'f_TodayCount'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'마지막 업데이트 시간' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Web_IndunClearUserCountInfo', @level2type=N'COLUMN',@level2name=N'f_LastTodayUpdate'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'보스전(인던) 클리어한 유저수 정보' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Web_IndunClearUserCountInfo'