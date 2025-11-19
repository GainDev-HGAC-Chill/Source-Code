USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ARITHABORT ON
GO
SET NUMERIC_ROUNDABORT OFF
GO
SET CONCAT_NULL_YIELDS_NULL ON
GO
SET ANSI_PADDING ON
GO
SET ANSI_WARNINGS ON
GO

IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefJobSkill_Tool]') AND [type] IN (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefJobSkill_Tool](
		[f_ItemNo] [int] NOT NULL,
		[f_ToolType] [int] NOT NULL,
		[f_Memo] nvarchar(50) NULL,
		[f_GatherType] int NULL,
		[f_01Need_Skill_No] [int] NOT NULL,
		[f_01Need_Skill_Expertness] [int] NOT NULL,
		[f_02Need_Skill_No] [int] NOT NULL,
		[f_02Need_Skill_Expertness] [int] NOT NULL,
		[f_03Need_Skill_No] [int] NOT NULL,
		[f_03Need_Skill_Expertness] [int] NOT NULL,
		[f_GetCount] [int] NOT NULL,
		[f_Option_TurnTime] [int] NOT NULL,
		[f_Option_CoolTime] [int] NOT NULL,
		[f_Option_User_Exhaustion] [int] NOT NULL
	 CONSTRAINT [PK_TB_DefJobSkill_Tool] PRIMARY KEY CLUSTERED 
	(
		[f_ItemNo] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefJobSkill_Tool') and [name] = N'f_GatherType')
BEGIN
	CREATE TABLE dbo.Tmp_TB_DefJobSkill_Tool(
		f_ItemNo int NOT NULL,
		f_ToolType int NOT NULL,
		f_Memo nvarchar(50) NULL,
		f_GatherType int NOT NULL,
		f_01Need_Skill_No int NOT NULL,
		f_01Need_Skill_Expertness int NOT NULL,
		f_02Need_Skill_No int NOT NULL,
		f_02Need_Skill_Expertness int NOT NULL,
		f_03Need_Skill_No int NOT NULL,
		f_03Need_Skill_Expertness int NOT NULL,
		f_GetCount int NOT NULL,
		f_Option_TurnTime int NOT NULL,
		f_Option_CoolTime int NOT NULL,
		f_Option_User_Exhaustion int NOT NULL
	)  ON [PRIMARY]
	
	IF EXISTS(SELECT * FROM dbo.TB_DefJobSkill_Tool)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefJobSkill_Tool (f_ItemNo, f_ToolType, f_Memo, f_01Need_Skill_No, f_01Need_Skill_Expertness, f_02Need_Skill_No, f_02Need_Skill_Expertness, f_03Need_Skill_No, f_03Need_Skill_Expertness, f_GetCount, f_Option_TurnTime, f_Option_CoolTime, f_Option_User_Exhaustion)
			SELECT f_ItemNo, f_ToolType, f_Memo, f_01Need_Skill_No, f_01Need_Skill_Expertness, f_02Need_Skill_No, f_02Need_Skill_Expertness, f_03Need_Skill_No, f_03Need_Skill_Expertness, f_GetCount, f_Option_TurnTime, f_Option_CoolTime, f_Option_User_Exhaustion FROM dbo.TB_DefJobSkill_Tool WITH (HOLDLOCK TABLOCKX)')
	
	DROP TABLE dbo.TB_DefJobSkill_Tool
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefJobSkill_Tool', N'TB_DefJobSkill_Tool', 'OBJECT' 
	
	ALTER TABLE dbo.TB_DefJobSkill_Tool ADD CONSTRAINT
		PK_TB_DefJobSkill_Tool PRIMARY KEY CLUSTERED 
		(
		f_ItemNo
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefJobSkill_Tool') and [name] = N'f_GetCount_Max')
BEGIN
	SET XACT_ABORT ON
	CREATE TABLE dbo.Tmp_TB_DefJobSkill_Tool
		(
		f_ItemNo int NOT NULL,
		f_ToolType int NOT NULL,
		f_Memo nvarchar(50) NULL,
		f_GatherType int NOT NULL,
		f_01Need_Skill_No int NOT NULL,
		f_01Need_Skill_Expertness int NOT NULL,
		f_02Need_Skill_No int NOT NULL,
		f_02Need_Skill_Expertness int NOT NULL,
		f_03Need_Skill_No int NOT NULL,
		f_03Need_Skill_Expertness int NOT NULL,
		f_GetCount int NOT NULL,
		f_GetCount_Max int NOT NULL,
		f_Option_TurnTime int NOT NULL,
		f_Option_CoolTime int NOT NULL,
		f_Option_User_Exhaustion int NOT NULL
		)  ON [PRIMARY]
	
	IF EXISTS(SELECT * FROM dbo.TB_DefJobSkill_Tool)
	BEGIN
		 INSERT INTO dbo.Tmp_TB_DefJobSkill_Tool (f_ItemNo, f_ToolType, f_Memo, f_GatherType, f_01Need_Skill_No, f_01Need_Skill_Expertness, f_02Need_Skill_No, f_02Need_Skill_Expertness, f_03Need_Skill_No, f_03Need_Skill_Expertness, f_GetCount, f_GetCount_Max, f_Option_TurnTime, f_Option_CoolTime, f_Option_User_Exhaustion)
			SELECT f_ItemNo, f_ToolType, f_Memo, f_GatherType, f_01Need_Skill_No, f_01Need_Skill_Expertness, f_02Need_Skill_No, f_02Need_Skill_Expertness, f_03Need_Skill_No, f_03Need_Skill_Expertness, f_GetCount, f_GetCount, f_Option_TurnTime, f_Option_CoolTime, f_Option_User_Exhaustion FROM dbo.TB_DefJobSkill_Tool WITH (HOLDLOCK TABLOCKX)
	END
	
	DROP TABLE dbo.TB_DefJobSkill_Tool

	EXECUTE sp_rename N'dbo.Tmp_TB_DefJobSkill_Tool', N'TB_DefJobSkill_Tool', 'OBJECT' 

	ALTER TABLE dbo.TB_DefJobSkill_Tool ADD CONSTRAINT
		PK_TB_DefJobSkill_Tool PRIMARY KEY CLUSTERED 
		(
		f_ItemNo
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
	SET XACT_ABORT OFF
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefJobSkill_Tool') and [name] = N'f_Result_No_Min')
BEGIN
	SET XACT_ABORT ON
	ALTER TABLE dbo.TB_DefJobSkill_Tool ADD
		f_Result_No_Min int NOT NULL CONSTRAINT DF_TB_TB_DefJobSkill_Tool_f_Result_No_Min DEFAULT 1,
		f_Result_No_Max int NOT NULL CONSTRAINT DF_TB_TB_DefJobSkill_Tool_f_Result_No_Max DEFAULT 1
	SET XACT_ABORT OFF
END