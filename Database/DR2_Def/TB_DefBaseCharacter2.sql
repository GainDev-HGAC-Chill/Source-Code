USE DR2_Def

/*
2009-03-10 이훈 퀵슬롯 확장 추가
*/

IF EXISTS (SELECT * FROM sys.all_objects WHERE NAME = 'DF_TB_DefBaseCharacter2_f_QuickSlot')
BEGIN
	ALTER TABLE [dbo].[TB_DefBaseCharacter2] DROP CONSTRAINT [DF_TB_DefBaseCharacter2_f_QuickSlot]
END

ALTER TABLE [dbo].[TB_DefBaseCharacter2] ALTER COLUMN [f_QuickSlot] [binary] (281) NOT NULL

ALTER TABLE [dbo].[TB_DefBaseCharacter2] ADD CONSTRAINT [DF_TB_DefBaseCharacter2_f_QuickSlot] DEFAULT (CONVERT([binary](281),(0),(0))) FOR [f_QuickSlot]


IF NOT EXISTS (SELECT * FROM sys.all_objects WHERE NAME = 'DF_TB_DefBaseCharacter2_f_InvExtend')
BEGIN
	ALTER TABLE [dbo].[TB_DefBaseCharacter2] ADD [f_InvExtend] [binary] (40) NOT NULL CONSTRAINT [DF_TB_DefBaseCharacter2_f_InvExtend] DEFAULT (CONVERT([binary](40),(0),(0)))
END

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefBaseCharacter2]') AND [Name] = 'f_GMLevel')
BEGIN
	ALTER TABLE [dbo].[TB_DefBaseCharacter2] DROP COLUMN [f_GMLevel]
END
GO


IF EXISTS(SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'DF_TB_DefBaseCharacter2_f_IngQuest'))
BEGIN
	ALTER TABLE [dbo].[TB_DefBaseCharacter2] DROP CONSTRAINT [DF_TB_DefBaseCharacter2_f_IngQuest]
END
GO
ALTER TABLE [dbo].[TB_DefBaseCharacter2] ALTER COLUMN [f_IngQuest] binary(300) NOT NULL
GO
ALTER TABLE [dbo].[TB_DefBaseCharacter2] ADD CONSTRAINT [DF_TB_DefBaseCharacter2_f_IngQuest] DEFAULT (CONVERT([binary](300),(0),(0))) For [f_IngQuest]
GO


IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefBaseCharacter2]') AND [Name] = 'f_EndQuestExt')
BEGIN
	ALTER TABLE [dbo].[TB_DefBaseCharacter2] ADD [f_EndQuestExt] [binary](260) NOT NULL CONSTRAINT [DF_TB_DefBaseCharacter2_f_EndQuestExt] DEFAULT (CONVERT([Binary](260),(0),(0)))
END

/*
	캐릭터 진행 퀘스트 정보 필드 확장( 현상수배 퀘스트) 2010.02.10 김동환
*/
IF EXISTS(SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'DF_TB_DefBaseCharacter2_f_IngQuest'))
BEGIN
	ALTER TABLE [dbo].[TB_DefBaseCharacter2] DROP CONSTRAINT [DF_TB_DefBaseCharacter2_f_IngQuest]
END
GO
ALTER TABLE [dbo].[TB_DefBaseCharacter2] ALTER COLUMN [f_IngQuest] binary(350) NOT NULL
GO
ALTER TABLE [dbo].[TB_DefBaseCharacter2] ADD CONSTRAINT [DF_TB_DefBaseCharacter2_f_IngQuest] DEFAULT (CONVERT([binary](350),(0),(0))) For [f_IngQuest]
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefBaseCharacter2]') AND [Name] = 'f_EndQuestExt2')
BEGIN
	ALTER TABLE [dbo].[TB_DefBaseCharacter2] ADD [f_EndQuestExt2] [binary](480) NOT NULL CONSTRAINT [DF_TB_DefBaseCharacter2_f_EndQuestExt2] DEFAULT (CONVERT([Binary](480),(0),(0)))
END
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefBaseCharacter2]') AND [Name] = 'f_NationCodeStr')
BEGIN
	ALTER TABLE dbo.TB_DefBaseCharacter2
	DROP CONSTRAINT DF_TB_DefBaseCharacter2_f_State
	
	ALTER TABLE dbo.TB_DefBaseCharacter2
		DROP CONSTRAINT DF_TB_DefBaseCharacter2_f_CP_1
	
	ALTER TABLE dbo.TB_DefBaseCharacter2
		DROP CONSTRAINT DF_TB_DefBaseCharacter2_f_Skills
	
	ALTER TABLE dbo.TB_DefBaseCharacter2
		DROP CONSTRAINT DF_TB_DefBaseCharacter2_f_QuickSlot
	
	ALTER TABLE dbo.TB_DefBaseCharacter2
		DROP CONSTRAINT DF_TB_DefBaseCharacter2_f_IngQuest
	
	ALTER TABLE dbo.TB_DefBaseCharacter2
		DROP CONSTRAINT DF_TB_DefBaseCharacter2_f_EndQuest
	
	ALTER TABLE dbo.TB_DefBaseCharacter2
		DROP CONSTRAINT DF_TB_DefBaseCharacter2_f_EndQuest2
	
	ALTER TABLE dbo.TB_DefBaseCharacter2
		DROP CONSTRAINT DF_TB_DefBaseCharacter2_f_InvExtend
	
	ALTER TABLE dbo.TB_DefBaseCharacter2
		DROP CONSTRAINT DF_TB_DefBaseCharacter2_f_EndQuestExt
	
	ALTER TABLE dbo.TB_DefBaseCharacter2
		DROP CONSTRAINT DF_TB_DefBaseCharacter2_f_EndQuestExt2
	
	CREATE TABLE dbo.Tmp_TB_DefBaseCharacter2
		(
		f_NationCodeStr nvarchar(50) NOT NULL,
		f_Class tinyint NOT NULL,
		f_State tinyint NOT NULL,
		f_Race int NOT NULL,
		f_Lv smallint NOT NULL,
		f_Exp bigint NOT NULL,
		f_Money bigint NOT NULL,
		f_HP int NOT NULL,
		f_MP int NOT NULL,
		f_CP int NOT NULL,
		f_ExtraSkillPoint smallint NOT NULL,
		f_Skills binary(450) NOT NULL,
		f_RecentMap int NOT NULL,
		f_RecentLocX float(53) NOT NULL,
		f_RecentLocY float(53) NOT NULL,
		f_RecentLocZ float(53) NOT NULL,
		f_LastVillage int NOT NULL,
		f_LastVillageLocX float(53) NOT NULL,
		f_LastVillageLocY float(53) NOT NULL,
		f_LastVillageLocZ float(53) NOT NULL,
		f_QuickSlot binary(281) NOT NULL,
		f_IngQuest binary(350) NOT NULL,
		f_EndQuest binary(130) NOT NULL,
		f_EndQuest2 binary(130) NOT NULL,
		f_Gender tinyint NOT NULL,
		f_HairStyle int NOT NULL,
		f_HairColor int NOT NULL,
		f_Face int NOT NULL,
		f_Jacket int NOT NULL,
		f_Gloves int NOT NULL,
		f_Pants int NOT NULL,
		f_Shoes int NOT NULL,
		f_InvExtend binary(40) NOT NULL,
		f_EndQuestExt binary(260) NOT NULL,
		f_EndQuestExt2 binary(480) NOT NULL
		)  ON [PRIMARY]
		
	EXECUTE sp_addextendedproperty N'MS_Description', N'Base character information
	- the new created character will be filled with this table such as HP, MP, Strength, etc ', N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefBaseCharacter2', NULL, NULL
	
	EXECUTE sp_addextendedproperty N'MS_Description', N'클래스 구분', N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefBaseCharacter2', N'COLUMN', N'f_Class'
	
	EXECUTE sp_addextendedproperty N'MS_Description', N'상태(지워지거나, 블럭되거나 등등)', N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefBaseCharacter2', N'COLUMN', N'f_State'
	
	ALTER TABLE dbo.Tmp_TB_DefBaseCharacter2 ADD CONSTRAINT
		DF_TB_DefBaseCharacter2_f_State DEFAULT ((0)) FOR f_State
	
	ALTER TABLE dbo.Tmp_TB_DefBaseCharacter2 ADD CONSTRAINT
		DF_TB_DefBaseCharacter2_f_CP_1 DEFAULT ((0)) FOR f_CP
	
	ALTER TABLE dbo.Tmp_TB_DefBaseCharacter2 ADD CONSTRAINT
		DF_TB_DefBaseCharacter2_f_Skills DEFAULT (CONVERT([binary](450),(0),(0))) FOR f_Skills
	
	ALTER TABLE dbo.Tmp_TB_DefBaseCharacter2 ADD CONSTRAINT
		DF_TB_DefBaseCharacter2_f_QuickSlot DEFAULT (CONVERT([binary](281),(0),(0))) FOR f_QuickSlot
	
	ALTER TABLE dbo.Tmp_TB_DefBaseCharacter2 ADD CONSTRAINT
		DF_TB_DefBaseCharacter2_f_IngQuest DEFAULT (CONVERT([binary](350),(0),(0))) FOR f_IngQuest
	
	ALTER TABLE dbo.Tmp_TB_DefBaseCharacter2 ADD CONSTRAINT
		DF_TB_DefBaseCharacter2_f_EndQuest DEFAULT (CONVERT([binary](130),(0),(0))) FOR f_EndQuest
	
	ALTER TABLE dbo.Tmp_TB_DefBaseCharacter2 ADD CONSTRAINT
		DF_TB_DefBaseCharacter2_f_EndQuest2 DEFAULT (CONVERT([binary](130),(0),(0))) FOR f_EndQuest2
	
	ALTER TABLE dbo.Tmp_TB_DefBaseCharacter2 ADD CONSTRAINT
		DF_TB_DefBaseCharacter2_f_InvExtend DEFAULT (CONVERT([binary](40),(0),(0))) FOR f_InvExtend
	
	ALTER TABLE dbo.Tmp_TB_DefBaseCharacter2 ADD CONSTRAINT
		DF_TB_DefBaseCharacter2_f_EndQuestExt DEFAULT (CONVERT([binary](260),(0),(0))) FOR f_EndQuestExt
	
	ALTER TABLE dbo.Tmp_TB_DefBaseCharacter2 ADD CONSTRAINT
		DF_TB_DefBaseCharacter2_f_EndQuestExt2 DEFAULT (CONVERT([binary](480),(0),(0))) FOR f_EndQuestExt2
	
	IF EXISTS(SELECT * FROM dbo.TB_DefBaseCharacter2)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefBaseCharacter2 (f_NationCodeStr, f_Class, f_State, f_Race, f_Lv, f_Exp, f_Money, f_HP, f_MP, f_CP, f_ExtraSkillPoint, f_Skills, f_RecentMap, f_RecentLocX, f_RecentLocY, f_RecentLocZ, f_LastVillage, f_LastVillageLocX, f_LastVillageLocY, f_LastVillageLocZ, f_QuickSlot, f_IngQuest, f_EndQuest, f_EndQuest2, f_Gender, f_HairStyle, f_HairColor, f_Face, f_Jacket, f_Gloves, f_Pants, f_Shoes, f_InvExtend, f_EndQuestExt, f_EndQuestExt2)
			SELECT 0, f_Class, f_State, f_Race, f_Lv, f_Exp, f_Money, f_HP, f_MP, f_CP, f_ExtraSkillPoint, f_Skills, f_RecentMap, f_RecentLocX, f_RecentLocY, f_RecentLocZ, f_LastVillage, f_LastVillageLocX, f_LastVillageLocY, f_LastVillageLocZ, f_QuickSlot, f_IngQuest, f_EndQuest, f_EndQuest2, f_Gender, f_HairStyle, f_HairColor, f_Face, f_Jacket, f_Gloves, f_Pants, f_Shoes, f_InvExtend, f_EndQuestExt, f_EndQuestExt2 FROM dbo.TB_DefBaseCharacter2 WITH (HOLDLOCK TABLOCKX)')
	
	DROP TABLE dbo.TB_DefBaseCharacter2
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefBaseCharacter2', N'TB_DefBaseCharacter2', 'OBJECT' 
END
GO