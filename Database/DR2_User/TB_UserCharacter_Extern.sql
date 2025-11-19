USE [DR2_User]
GO

IF  NOT EXISTS (SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'TB_UserCharacter_Extern'))
BEGIN
	SET ANSI_NULLS ON
	SET QUOTED_IDENTIFIER ON
	SET ANSI_PADDING ON
	CREATE TABLE [dbo].[TB_UserCharacter_Extern](
		[CharacterID] [uniqueidentifier] NOT NULL,
		[ChannelNo] [smallint] NOT NULL CONSTRAINT [DF_TB_UserCharacter_Extern_ChannelNo]  DEFAULT ((0)),
		[PvP_Point] [int] NOT NULL CONSTRAINT [DF_TB_UserCharacter_Extern_PvP_Point]  DEFAULT ((0)),
		[PvP_Win] [int] NOT NULL CONSTRAINT [DF_TB_UserCharacter_Extern_PvP_Win]  DEFAULT ((0)),
		[PvP_Draw] [int] NOT NULL CONSTRAINT [DF_TB_UserCharacter_Extern_PvP_Draw]  DEFAULT ((0)),
		[PvP_Lose] [int] NOT NULL CONSTRAINT [DF_TB_UserCharacter_Extern_PvP_Lose]  DEFAULT ((0)),
		[PvP_Kill] [bigint] NOT NULL CONSTRAINT [DF_TB_UserCharacter_Extern_PvP_Kill]  DEFAULT ((0)),
		[PvP_Death] [bigint] NOT NULL CONSTRAINT [DF_TB_UserCharacter_Extern_PvP_Death]  DEFAULT ((0)),
		[PvP_Win_Exercise] [int] NOT NULL CONSTRAINT [DF_TB_UserCharacter_Extern_PvP_Win_Exercise]  DEFAULT ((0)),
		[PvP_Draw_Exercise] [int] NOT NULL CONSTRAINT [DF_TB_UserCharacter_Extern_PvP_Draw_Exercise]  DEFAULT ((0)),
		[PvP_Lose_Exercise] [int] NOT NULL CONSTRAINT [DF_TB_UserCharacter_Extern_PvP_Lose_Exercise]  DEFAULT ((0)),
		[World01] [binary](32) NOT NULL CONSTRAINT [DF_TB_UserCharacter_Extern_World01]  DEFAULT (CONVERT([binary](32),(0),(0))),
		[OptionInfo] [binary](520) NOT NULL CONSTRAINT [DF_TB_UserCharacter_Extern_OptionInfo]  DEFAULT ((0)),
		[Mission_01] [binary](400) NOT NULL CONSTRAINT [DF_TB_UserCharacter_Extern_Mission01]  DEFAULT (CONVERT([binary](400),(0),(0))),
		[Mission_02] [binary](400) NOT NULL CONSTRAINT [DF_TB_UserCharacter_Extern_Mission02]  DEFAULT (CONVERT([binary](400),(0),(0))),
		[Achievements] [binary](250) NOT NULL CONSTRAINT [DF_TB_UserCharacter_Extern_Achievements]  DEFAULT (CONVERT([binary](250),(0),(0))),
		[LastUpdate] [datetime] NOT NULL,
	 CONSTRAINT [PK_TB_UserCharacter_Extern] PRIMARY KEY CLUSTERED 
	(
		[CharacterID] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]
	SET ANSI_PADDING OFF
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'캐릭터가 게임에서 달성한 업적의 정보 및 훈장 -> 아이템 변환 여부 정보를 기록 하고 있음' ,@level0type=N'SCHEMA', @level0name=N'dbo', @level1type=N'TABLE', @level1name=N'TB_UserCharacter_Extern', @level2type=N'COLUMN', @level2name=N'Achievements'
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'유저 정보' ,@level0type=N'SCHEMA', @level0name=N'dbo', @level1type=N'TABLE', @level1name=N'TB_UserCharacter_Extern'
END
ELSE
BEGIN

	IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_UserCharacter_Extern_PvP_Disconnect]') AND type = 'D')
	BEGIN
		ALTER TABLE [dbo].[TB_UserCharacter_Extern] DROP CONSTRAINT [DF_TB_UserCharacter_Extern_PvP_Disconnect]
		ALTER TABLE [dbo].[TB_UserCharacter_Extern] DROP COLUMN [PvP_DisConnect]
	END
	
	IF  NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_UserCharacter_Extern_PvP_Win_Exercise]') AND type = 'D')
	BEGIN
	
		ALTER TABLE [dbo].[TB_UserCharacter_Extern]
		ADD [PvP_Win_Exercise] [int] NOT NULL CONSTRAINT [DF_TB_UserCharacter_Extern_PvP_Win_Exercise] DEFAULT ((0))
	
		ALTER TABLE [dbo].[TB_UserCharacter_Extern]
		ADD [PvP_Draw_Exercise] [int] NOT NULL CONSTRAINT [DF_TB_UserCharacter_Extern_PvP_Draw_Exercise] DEFAULT ((0))
	
		ALTER TABLE [dbo].[TB_UserCharacter_Extern]
		ADD [PvP_Lose_Exercise] [int] NOT NULL CONSTRAINT [DF_TB_UserCharacter_Extern_PvP_Lose_Exercise] DEFAULT ((0))
	END

	IF NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_UserCharacter_Extern_Mission_Event]') AND type = 'D')
	BEGIN
		ALTER TABLE [dbo].[TB_UserCharacter_Extern] ADD 
			[Mission_Event] [int] NOT NULL CONSTRAINT [DF_TB_UserCharacter_Extern_Mission_Event] DEFAULT ((0))
	END

	IF NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_UserCharacter_Extern_Hidden_Open]') AND type = 'D')
	BEGIN
		ALTER TABLE [dbo].[TB_UserCharacter_Extern] ADD
			[Hidden_Open] [binary](125) NOT NULL CONSTRAINT [DF_TB_UserCharacter_Extern_Hidden_Open] DEFAULT (CONVERT([binary](125),(0),(0)))
		ALTER TABLE [dbo].[TB_UserCharacter_Extern] ADD
			[LastHiddenUpdate] [datetime] NOT NULL CONSTRAINT [DF_TB_UserCharacter_Extern_LastHiddenUpdate] DEFAULT (CONVERT(DATETIME, N'2000-01-01 00:00:00'))
	END
END
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_UserCharacter_Extern]') AND [name] = N'f_JobSkill_SaveIdx')
BEGIN
	ALTER TABLE [dbo].[TB_UserCharacter_Extern] ADD f_JobSkill_SaveIdx BINARY(128) NOT NULL
		CONSTRAINT DF_TB_UserCharacter_Extern_f_JobSkill_SaveIdx DEFAULT 0x0
END

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_UserCharacter_Extern]') AND [name] = N'f_JobSkill_Expertness')
BEGIN
	ALTER TABLE [dbo].[TB_UserCharacter_Extern] DROP CONSTRAINT DF_TB_UserCharacter_Extern_f_JobSkill_Expertness
	ALTER TABLE [dbo].[TB_UserCharacter_Extern] DROP COLUMN f_JobSkill_Expertness
END

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_UserCharacter_Extern]') AND [name] = N'f_JobSkill_SaveIdx' and max_length = 128)
BEGIN
	ALTER TABLE [dbo].[TB_UserCharacter_Extern] ALTER COLUMN f_JobSkill_SaveIdx BINARY(256) NOT NULL
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_UserCharacter_Extern]') AND [name] = N'f_JobSkill_HistoryItem')
BEGIN
	ALTER TABLE [dbo].[TB_UserCharacter_Extern] ADD f_JobSkill_HistoryItem BINARY(40) NOT NULL
		CONSTRAINT DF_TB_UserCharacter_Extern_f_JobSkill_HistoryItem DEFAULT 0x0
END

/*		COLUMN 추가 : 프리미엄 서비스 커스텀 데이터 저장	*/
IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_UserCharacter_Extern') AND [name] = N'PremiumCustomData')
BEGIN
	ALTER TABLE [dbo].[TB_UserCharacter_Extern] ADD [PremiumCustomData] varbinary(max)
END
