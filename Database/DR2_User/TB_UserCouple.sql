USE [DR2_User]
IF  NOT EXISTS (SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'TB_UserCouple'))
BEGIN
	/****** Object:  Table [dbo].[TB_UserCouple]    Script Date: 07/09/2009 21:15:27 ******/
	SET ANSI_NULLS ON
	SET QUOTED_IDENTIFIER ON
	CREATE TABLE [dbo].[TB_UserCouple](
		[CharacterGuid] [uniqueidentifier] NOT NULL,
		[CoupleCharGuid] [uniqueidentifier] NOT NULL,
		[StartDate] [datetime] NULL,
		[Status] [tinyint] NULL,
		[LimitDate] [datetime] NULL,
	 CONSTRAINT [PK_TB_UserCouple] PRIMARY KEY CLUSTERED 
	(
		[CharacterGuid] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]

	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'커플 정보 주인 캐릭터Guid' ,@level0type=N'SCHEMA', @level0name=N'dbo', @level1type=N'TABLE', @level1name=N'TB_UserCouple', @level2type=N'COLUMN', @level2name=N'CharacterGuid'
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'커플 대상의 캐릭터 Guid' ,@level0type=N'SCHEMA', @level0name=N'dbo', @level1type=N'TABLE', @level1name=N'TB_UserCouple', @level2type=N'COLUMN', @level2name=N'CoupleCharGuid'
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'기간제한 커플이면 제한 날자가 기록 된다' ,@level0type=N'SCHEMA', @level0name=N'dbo', @level1type=N'TABLE', @level1name=N'TB_UserCouple', @level2type=N'COLUMN', @level2name=N'LimitDate'
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'사용자 캐릭터 커뮤니티 / 커플 정보' ,@level0type=N'SCHEMA', @level0name=N'dbo', @level1type=N'TABLE', @level1name=N'TB_UserCouple'
END

GO

/* 연인 관련 커플 퀘스트 추가 Table [dbo].[TB_UserCouple] Script Date: 07/09/2009 21:15:27 */
IF NOT EXISTS (SELECT * FROM sys.all_objects WHERE NAME = 'DF_TB_UserCouple_DeleteQuest')
ALTER TABLE [dbo].[TB_UserCouple] ADD 
	[DeleteQuest] [int] NOT NULL CONSTRAINT [DF_TB_UserCouple_DeleteQuest]  DEFAULT ((0)),
	[SweetHeartQuestTime] [bigint] NOT NULL CONSTRAINT [DF_TB_UserCouple_SweetHeartQuestTime]  DEFAULT ((0)),
	[LearnSkill] [int] NOT NULL CONSTRAINT [DF_TB_UserCouple_LearnSkill]  DEFAULT ((0)),
	[CouplePanaltyLimitDate] [datetime] NULL	
GO

ALTER TABLE [dbo].[TB_UserCouple] ADD
	[ColorGuid] [uniqueidentifier] NOT NULL CONSTRAINT [DF_TB_UserCouple_ColorGuid] DEFAULT ('00000000-0000-0000-0000-000000000000')
GO
