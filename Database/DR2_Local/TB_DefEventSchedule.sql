USE [DR2_Local]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefEventSchedule]') )
BEGIN
	CREATE TABLE [dbo].[TB_DefEventSchedule](
		[IDX] [int] IDENTITY(1,1) NOT NULL,
		[Memo] [nvarchar](200) NULL,
		[EventType] [smallint] NOT NULL,
		[EventNo] [int] NOT NULL,
		[LevelMin] [smallint] NOT NULL,
		[LevelMax] [smallint] NOT NULL,
		[ClassLimitHuman] [bigint] NOT NULL,
		[ClassLimitDragon] [bigint] NOT NULL,
		[PartyMemberMin] [tinyint] NOT NULL,
		[ReqQuest] [int] NOT NULL,
		[ReqItemNo] [int] NOT NULL,
		[ReqItemCount] [tinyint] NOT NULL,
		[MaxMapUserNumber] [tinyint] NOT NULL,
		[UsableReviveItem] [tinyint] NOT NULL,
		[UsableConsumeItem] [tinyint] NOT NULL,
		[PKOption] [tinyint] NOT NULL,
		[MenuText] [nvarchar](200) NULL,
		[CyclingType] [tinyint] NOT NULL,
		[StartData] [datetime] NOT NULL,
		[EndDate] [datetime] NOT NULL,
		[StartTime] [datetime] NOT NULL,
		[EventPeriod] [int] NOT NULL,
		[DayofWeek] [nvarchar](100) NOT NULL
	 CONSTRAINT [PK_TB_DefEventSchedule] PRIMARY KEY CLUSTERED 
	(
		[IDX] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]
END

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefEventSchedule]') )
BEGIN

	ALTER TABLE [dbo].[TB_DefEventSchedule]
		DROP CONSTRAINT [PK_TB_DefEventSchedule]

	DROP TABLE [dbo].[TB_DefEventSchedule]
END

IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefEventSchedule]') )
BEGIN
	CREATE TABLE [dbo].[TB_DefEventSchedule](
		[IDX] [int] IDENTITY(1,1) NOT NULL,
		[Menu_Txt] [nvarchar](200) NULL,
		[Memo] [nvarchar](200) NULL,
		[Event_Type] [nvarchar](100) NULL,
		[Event_No] [int] DEFAULT(0) NOT NULL,
		[Event_Ground] [int] DEFAULT(0) NOT NULL,
		[Level_Min] [smallint] DEFAULT(0) NOT NULL,
		[Level_Max]	[smallint] DEFAULT(0) NOT NULL,
		[Class_Limit_Human] [bigint] DEFAULT(0) NOT NULL,
		[Class_Limit_Dragon] [bigint] DEFAULT(0) NOT NULL,
		[Party_Member_Min] [tinyint] DEFAULT(0) NOT NULL,
		[UserCount_Max] [smallint] DEFAULT(0) NOT NULL,
		[IS_PK] [tinyint] DEFAULT(0) NOT NULL,
		[Need_Quest] [int] DEFAULT(0) NOT NULL,
		[Need_Quest_State] [tinyint] DEFAULT(0) NOT NULL,
		[Need_ItemNo] [int] DEFAULT(0) NOT NULL,
		[Need_ItemCount] [tinyint] DEFAULT(0) NOT NULL,
		[Unusable_ConsumeItem] [tinyint] DEFAULT(0) NOT NULL,
		[Unusable_ReviveItem] [tinyint] DEFAULT(0) NOT NULL,
		[Start_Date] [datetime] NOT NULL,
		[Start_Time] [datetime] NOT NULL,
		[End_Date] [datetime] NOT NULL,
		[Event_Period] [int] DEFAULT(0) NOT NULL,
		[Event_Count] [tinyint] DEFAULT(0) NOT NULL,
		[DayofWeek] [nvarchar](100) NULL
	 CONSTRAINT [PK_TB_DefEventSchedule] PRIMARY KEY CLUSTERED 
	(
		[IDX] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]
END