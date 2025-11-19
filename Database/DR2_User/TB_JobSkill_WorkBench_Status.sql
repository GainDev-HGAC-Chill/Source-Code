USE [DR2_User]
GO

/****** Object:  Table [dbo].[TB_JobSkill_WorkBench_Status]    Script Date: 09/03/2010 16:30:33 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_JobSkill_WorkBench_Status]') AND [type] in (N'U'))
BEGIN
CREATE TABLE [dbo].[TB_JobSkill_WorkBench_Status](
	[f_WorkBenchGuid] [uniqueidentifier] NOT NULL,
	[f_OwnerGuid] [uniqueidentifier] NOT NULL,
	[f_WorkBenchType] [int] NOT NULL,
	[f_ItemNo] [int] NOT NULL,
	[f_ItemGrade] [int] NOT NULL,
	[f_WorkBenchStatus] [int] NOT NULL,
	[f_RemainUpgradeCount] [int] NOT NULL,
	[f_TurnBeginTime] [datetime] NOT NULL,
	[f_TurnEndTime] [datetime] NOT NULL,
	[f_Duration] [int] NOT NULL,
 CONSTRAINT [PK_TB_JobSkill_WorkBench_Status] PRIMARY KEY CLUSTERED 
(
	[f_WorkBenchGuid] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
END
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_JobSkill_WorkBench_Status]') AND [name] = N'f_01SlotEleapsedTime')
BEGIN
	CREATE TABLE dbo.Tmp_TB_JobSkill_WorkBench_Status
		(
		f_WorkBenchGuid uniqueidentifier NOT NULL,
		f_ItemNo int NOT NULL,
		f_Duration int NOT NULL,
		f_01SlotItemNo int NOT NULL,
		f_01SlotEleapsedTime bigint NOT NULL,
		f_02SlotItemNo int NOT NULL,
		f_02SlotEleapsedTime bigint NOT NULL,
		f_03SlotItemNo int NOT NULL,
		f_03SlotEleapsedTime bigint NOT NULL,
		f_04SlotItemNo int NOT NULL,
		f_04SlotEleapsedTime bigint NOT NULL,
		f_05SlotItemNo int NOT NULL,
		f_05SlotEleapsedTime bigint NOT NULL,
		f_06SlotItemNo int NOT NULL,
		f_06SlotEleapsedTime bigint NOT NULL,
		f_07SlotItemNo int NOT NULL,
		f_07SlotEleapsedTime bigint NOT NULL,
		f_08SlotItemNo int NOT NULL,
		f_08SlotEleapsedTime bigint NOT NULL,
		f_09SlotItemNo int NOT NULL,
		f_09SlotEleapsedTime bigint NOT NULL,
		f_10SlotItemNo int NOT NULL,
		f_10SlotEleapsedTime bigint NOT NULL,
		f_CurUpgradeSlot int NOT NULL,
		f_IsHasTrouble tinyint NOT NULL,
		f_TroubleTime bigint NOT NULL,
		f_BlessSkillNo int NOT NULL,
		f_BlessValue int NOT NULL,
		f_DurationSec bigint NOT NULL
		)  ON [PRIMARY]
	
--	IF EXISTS(SELECT * FROM dbo.TB_JobSkill_WorkBench_Status)
--		 EXEC('INSERT INTO dbo.Tmp_TB_JobSkill_WorkBench_Status (f_WorkBenchGuid, f_ItemNo, f_Duration)
--			SELECT f_WorkBenchGuid, f_ItemNo, f_Duration FROM dbo.TB_JobSkill_WorkBench_Status WITH (HOLDLOCK TABLOCKX)')
--	
	DROP TABLE dbo.TB_JobSkill_WorkBench_Status
	
	EXECUTE sp_rename N'dbo.Tmp_TB_JobSkill_WorkBench_Status', N'TB_JobSkill_WorkBench_Status', 'OBJECT' 
	
	ALTER TABLE dbo.TB_JobSkill_WorkBench_Status ADD CONSTRAINT
		PK_TB_JobSkill_WorkBench_Status PRIMARY KEY CLUSTERED 
		(
		f_WorkBenchGuid
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
END

--IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_JobSkill_WorkBench_Status') and [name] = N'f_AccumExpertness')
--BEGIN
--	ALTER TABLE dbo.TB_JobSkill_WorkBench_Status ADD f_AccumExpertness int NOT NULL CONSTRAINT DF_TB_JobSkill_WorkBench_Status_f_AccumExpertness DEFAULT 0
--END

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_JobSkill_WorkBench_Status') and [name] = N'f_BlessValue')
BEGIN
	ALTER TABLE dbo.TB_JobSkill_WorkBench_Status DROP COLUMN f_BlessSkillNo
	ALTER TABLE dbo.TB_JobSkill_WorkBench_Status DROP COLUMN f_BlessValue
	ALTER TABLE dbo.TB_JobSkill_WorkBench_Status DROP COLUMN f_DurationSec
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_JobSkill_WorkBench_Status') and [name] = N'f_BlessDurationSec')
BEGIN
	ALTER TABLE dbo.TB_JobSkill_WorkBench_Status ADD f_BlessDurationSec bigint NOT NULL CONSTRAINT DF_TB_JobSkill_WorkBench_Status_f_BlessDurationSec DEFAULT 0
END

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_JobSkill_WorkBench_Status') and [name] = N'f_AccumExpertness')
BEGIN
	ALTER TABLE dbo.TB_JobSkill_WorkBench_Status DROP CONSTRAINT DF_TB_JobSkill_WorkBench_Status_f_AccumExpertness
	ALTER TABLE dbo.TB_JobSkill_WorkBench_Status DROP COLUMN f_AccumExpertness
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_JobSkill_WorkBench_Status') and [name] = N'f_BlessCharGuid')
BEGIN
	ALTER TABLE dbo.TB_JobSkill_WorkBench_Status ADD f_BlessCharGuid UNIQUEIDENTIFIER NOT NULL CONSTRAINT DF_TB_JobSkill_WorkBench_Status_f_BlessCharGuid DEFAULT N'00000000-0000-0000-0000-000000000000'
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'') and [name] = N'f_BlessSkillNo')
BEGIN
	ALTER TABLE dbo.TB_JobSkill_WorkBench_Status ADD f_BlessSkillNo int NOT NULL CONSTRAINT DF_TB_JobSkill_WorkBench_Status_f_BlessSkillNo DEFAULT 0
END