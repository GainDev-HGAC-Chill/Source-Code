USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefBS_Game]') AND [type] = N'U')
BEGIN
	CREATE TABLE [dbo].[TB_DefBS_Game](
		[f_BS_GAME_IDX] [int] NOT NULL,
		[f_MEMO] [nvarchar](100) NULL,
		[f_Ch_IsUse] [tinyint] NOT NULL,
		[f_Ch_ChannelTitle] [int] NOT NULL,
		[f_Ch_LevelMin] [int] NOT NULL,
		[f_Ch_LevelMax] [int] NOT NULL,
		[f_Ch_MaxUser] [int] NOT NULL,
		[f_Ch_W_Sunday] [tinyint] NOT NULL,
		[f_Ch_W_Monday] [tinyint] NOT NULL,
		[f_Ch_W_Tuesday] [tinyint] NOT NULL,
		[f_Ch_W_Wednesday] [tinyint] NOT NULL,
		[f_Ch_W_Thursday] [tinyint] NOT NULL,
		[f_Ch_W_Friday] [tinyint] NOT NULL,
		[f_Ch_W_Saturday] [tinyint] NOT NULL,
		[f_Ch_StartTime] [datetime] NOT NULL,
		[f_Ch_GameSec] [bigint] NOT NULL,
		[f_Game_GroundNo] [int] NOT NULL CONSTRAINT [DF_TB_DefBS_Game_f_SpecGround]  DEFAULT ((0)),
		[f_Game_PreOpenSec] [bigint] NOT NULL
	 CONSTRAINT [PK_TB_DefBS_Game] PRIMARY KEY CLUSTERED 
	(
		[f_BS_GAME_IDX] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefBS_Game]') and name = N'f_LvRewardIdx')
BEGIN
	ALTER TABLE [dbo].[TB_DefBS_Game] ADD f_LvRewardIdx INT NOT NULL CONSTRAINT DF_TB_DefBS_Gamef_LvRewardIdx DEFAULT 0
	ALTER TABLE [dbo].[TB_DefBS_Game] ADD f_PtRewardIdx INT NOT NULL CONSTRAINT DF_TB_DefBS_Gamef_PtRewardIdx DEFAULT 0
	ALTER TABLE [dbo].[TB_DefBS_Game] ADD f_TeamRewardIdx INT NOT NULL CONSTRAINT DF_TB_DefBS_Gamef_TeamRewardIdx DEFAULT 0
	ALTER TABLE [dbo].[TB_DefBS_Game] ADD f_BnsRewardIdx INT NOT NULL CONSTRAINT DF_TB_DefBS_Gamef_BnsRewardIdx DEFAULT 0
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefBS_Game]') and name = N'f_MapBagItemGroundNo')
BEGIN
	ALTER TABLE [dbo].[TB_DefBS_Game] ADD f_MapBagItemGroundNo INT NOT NULL CONSTRAINT DF_TB_DefBS_Game_f_MapBagItemGroundNo DEFAULT 0
	ALTER TABLE [dbo].[TB_DefBS_Game] ADD f_GenGroupGroundNo INT NOT NULL CONSTRAINT DF_TB_DefBS_Game_f_GenGroupGroundNo DEFAULT 0
	ALTER TABLE [dbo].[TB_DefBS_Game] ADD f_MonsterBagControlNo INT NOT NULL CONSTRAINT DF_TB_DefBS_Game_f_MonsterBagNo DEFAULT 0
END





ALTER TABLE dbo.TB_DefBS_Game
	DROP CONSTRAINT DF_TB_DefBS_Game_f_SpecGround
GO
ALTER TABLE dbo.TB_DefBS_Game
	DROP CONSTRAINT DF_TB_DefBS_Gamef_LvRewardIdx
GO
ALTER TABLE dbo.TB_DefBS_Game
	DROP CONSTRAINT DF_TB_DefBS_Gamef_PtRewardIdx
GO
ALTER TABLE dbo.TB_DefBS_Game
	DROP CONSTRAINT DF_TB_DefBS_Gamef_TeamRewardIdx
GO
ALTER TABLE dbo.TB_DefBS_Game
	DROP CONSTRAINT DF_TB_DefBS_Gamef_BnsRewardIdx
GO
ALTER TABLE dbo.TB_DefBS_Game
	DROP CONSTRAINT DF_TB_DefBS_Game_f_MapBagItemGroundNo
GO
ALTER TABLE dbo.TB_DefBS_Game
	DROP CONSTRAINT DF_TB_DefBS_Game_f_GenGroupGroundNo
GO
ALTER TABLE dbo.TB_DefBS_Game
	DROP CONSTRAINT DF_TB_DefBS_Game_f_MonsterBagNo
GO
CREATE TABLE dbo.Tmp_TB_DefBS_Game
	(
	f_NationCodeStr nvarchar(50) NOT NULL CONSTRAINT [DF_DefBS_Game_f_NationCodeStr]  DEFAULT ((0)),
	f_BS_GAME_IDX int NOT NULL,
	f_MEMO nvarchar(100) NULL,
	f_Ch_IsUse tinyint NOT NULL,
	f_Ch_ChannelTitle int NOT NULL,
	f_Ch_LevelMin int NOT NULL,
	f_Ch_LevelMax int NOT NULL,
	f_Ch_MaxUser int NOT NULL,
	f_Ch_W_Sunday tinyint NOT NULL,
	f_Ch_W_Monday tinyint NOT NULL,
	f_Ch_W_Tuesday tinyint NOT NULL,
	f_Ch_W_Wednesday tinyint NOT NULL,
	f_Ch_W_Thursday tinyint NOT NULL,
	f_Ch_W_Friday tinyint NOT NULL,
	f_Ch_W_Saturday tinyint NOT NULL,
	f_Ch_StartTime datetime NOT NULL,
	f_Ch_GameSec bigint NOT NULL,
	f_Game_GroundNo int NOT NULL,
	f_Game_PreOpenSec bigint NOT NULL,
	f_LvRewardIdx int NOT NULL,
	f_PtRewardIdx int NOT NULL,
	f_TeamRewardIdx int NOT NULL,
	f_BnsRewardIdx int NOT NULL,
	f_MapBagItemGroundNo int NOT NULL,
	f_GenGroupGroundNo int NOT NULL,
	f_MonsterBagControlNo int NOT NULL
	)  ON [PRIMARY]
GO
ALTER TABLE dbo.Tmp_TB_DefBS_Game SET (LOCK_ESCALATION = TABLE)
GO
DECLARE @v sql_variant 
SET @v = N'베틀 스퀘어, 게임의 기본 설정을 하는 테이블 (시간, 요일, 게임맵 등을 설정)'
EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefBS_Game', NULL, NULL
GO
ALTER TABLE dbo.Tmp_TB_DefBS_Game ADD CONSTRAINT
	DF_TB_DefBS_Game_f_SpecGround DEFAULT ((0)) FOR f_Game_GroundNo
GO
ALTER TABLE dbo.Tmp_TB_DefBS_Game ADD CONSTRAINT
	DF_TB_DefBS_Gamef_LvRewardIdx DEFAULT ((0)) FOR f_LvRewardIdx
GO
ALTER TABLE dbo.Tmp_TB_DefBS_Game ADD CONSTRAINT
	DF_TB_DefBS_Gamef_PtRewardIdx DEFAULT ((0)) FOR f_PtRewardIdx
GO
ALTER TABLE dbo.Tmp_TB_DefBS_Game ADD CONSTRAINT
	DF_TB_DefBS_Gamef_TeamRewardIdx DEFAULT ((0)) FOR f_TeamRewardIdx
GO
ALTER TABLE dbo.Tmp_TB_DefBS_Game ADD CONSTRAINT
	DF_TB_DefBS_Gamef_BnsRewardIdx DEFAULT ((0)) FOR f_BnsRewardIdx
GO
ALTER TABLE dbo.Tmp_TB_DefBS_Game ADD CONSTRAINT
	DF_TB_DefBS_Game_f_MapBagItemGroundNo DEFAULT ((0)) FOR f_MapBagItemGroundNo
GO
ALTER TABLE dbo.Tmp_TB_DefBS_Game ADD CONSTRAINT
	DF_TB_DefBS_Game_f_GenGroupGroundNo DEFAULT ((0)) FOR f_GenGroupGroundNo
GO
ALTER TABLE dbo.Tmp_TB_DefBS_Game ADD CONSTRAINT
	DF_TB_DefBS_Game_f_MonsterBagNo DEFAULT ((0)) FOR f_MonsterBagControlNo
GO
IF EXISTS(SELECT * FROM dbo.TB_DefBS_Game)
	 EXEC('INSERT INTO dbo.Tmp_TB_DefBS_Game (f_BS_GAME_IDX, f_MEMO, f_Ch_IsUse, f_Ch_ChannelTitle, f_Ch_LevelMin, f_Ch_LevelMax, f_Ch_MaxUser, f_Ch_W_Sunday, f_Ch_W_Monday, f_Ch_W_Tuesday, f_Ch_W_Wednesday, f_Ch_W_Thursday, f_Ch_W_Friday, f_Ch_W_Saturday, f_Ch_StartTime, f_Ch_GameSec, f_Game_GroundNo, f_Game_PreOpenSec, f_LvRewardIdx, f_PtRewardIdx, f_TeamRewardIdx, f_BnsRewardIdx, f_MapBagItemGroundNo, f_GenGroupGroundNo, f_MonsterBagControlNo)
		SELECT f_BS_GAME_IDX, f_MEMO, f_Ch_IsUse, f_Ch_ChannelTitle, f_Ch_LevelMin, f_Ch_LevelMax, f_Ch_MaxUser, f_Ch_W_Sunday, f_Ch_W_Monday, f_Ch_W_Tuesday, f_Ch_W_Wednesday, f_Ch_W_Thursday, f_Ch_W_Friday, f_Ch_W_Saturday, f_Ch_StartTime, f_Ch_GameSec, f_Game_GroundNo, f_Game_PreOpenSec, f_LvRewardIdx, f_PtRewardIdx, f_TeamRewardIdx, f_BnsRewardIdx, f_MapBagItemGroundNo, f_GenGroupGroundNo, f_MonsterBagControlNo FROM dbo.TB_DefBS_Game WITH (HOLDLOCK TABLOCKX)')
GO
DROP TABLE dbo.TB_DefBS_Game
GO
EXECUTE sp_rename N'dbo.Tmp_TB_DefBS_Game', N'TB_DefBS_Game', 'OBJECT' 
GO
ALTER TABLE dbo.TB_DefBS_Game ADD CONSTRAINT
	PK_TB_DefBS_Game PRIMARY KEY CLUSTERED 
	(
	f_NationCodeStr,
	f_BS_GAME_IDX
	) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]

GO
	