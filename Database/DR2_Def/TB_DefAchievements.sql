USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefAchievements]    Script Date: 10/22/2009 18:51:44 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefAchievements') AND [name] = N'f_NationCodeStr')
BEGIN
	/* To prevent any potential data loss issues, you should review this script in detail before running it outside the context of the database designer.*/
	BEGIN TRANSACTION
	SET QUOTED_IDENTIFIER ON
	SET ARITHABORT ON
	SET NUMERIC_ROUNDABORT OFF
	SET CONCAT_NULL_YIELDS_NULL ON
	SET ANSI_NULLS ON
	SET ANSI_PADDING ON
	SET ANSI_WARNINGS ON
	COMMIT
	BEGIN TRANSACTION
	
	ALTER TABLE dbo.TB_DefAchievements
		DROP CONSTRAINT DF_TB_DefAchievements_Category
	
	ALTER TABLE dbo.TB_DefAchievements
		DROP CONSTRAINT DF_TB_DefAchievements_TitleNo
	
	ALTER TABLE dbo.TB_DefAchievements
		DROP CONSTRAINT DF_TB_DefAchievements_Value1
	
	ALTER TABLE dbo.TB_DefAchievements
		DROP CONSTRAINT DF_TB_DefAchievements_RankPoint
	
	CREATE TABLE dbo.Tmp_TB_DefAchievements
		(
		Idx int NOT NULL,
		f_NationCodeStr nvarchar(50) NOT NULL,
		Category int NOT NULL,
		TitleNo int NOT NULL,
		DiscriptionNo int NOT NULL,
		Memo nvarchar(50) NULL,
		Type int NOT NULL,
		Value int NOT NULL,
		ItemNo int NOT NULL,
		SaveIdx int NOT NULL,
		RankPoint int NULL,
		[Level] int NULL,
		SYear int NULL,
		SMonth tinyint NULL,
		SDay tinyint NULL,
		SHour tinyint NULL,
		SMinute tinyint NULL,
		EYear int NULL,
		EMonth tinyint NULL,
		EDay tinyint NULL,
		EHour tinyint NULL,
		EMinute tinyint NULL,
		UseTime int NULL,
		IsUse tinyint NULL
		)  ON [PRIMARY]
	
	DECLARE @v sql_variant 
	SET @v = N'업적 정의
	해당 테이블에 업적 정의 데이터가 입력되어 있어야 업적 달성이 가능하며 
	클라이언트 북 -> 업적 페이지에서 업적 리스트 열람이 가능 함'
	EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefAchievements', NULL, NULL

	ALTER TABLE dbo.Tmp_TB_DefAchievements ADD CONSTRAINT
		DF_TB_DefAchievements_f_NationCode DEFAULT N'0' FOR f_NationCodeStr
	
	ALTER TABLE dbo.Tmp_TB_DefAchievements ADD CONSTRAINT
		DF_TB_DefAchievements_Category DEFAULT ((0)) FOR Category
	
	ALTER TABLE dbo.Tmp_TB_DefAchievements ADD CONSTRAINT
		DF_TB_DefAchievements_TitleNo DEFAULT ((0)) FOR TitleNo
	
	ALTER TABLE dbo.Tmp_TB_DefAchievements ADD CONSTRAINT
		DF_TB_DefAchievements_Value1 DEFAULT ((0)) FOR Value
	
	ALTER TABLE dbo.Tmp_TB_DefAchievements ADD CONSTRAINT
		DF_TB_DefAchievements_RankPoint DEFAULT ((0)) FOR RankPoint
	
	IF EXISTS(SELECT * FROM dbo.TB_DefAchievements)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefAchievements (Idx, Category, TitleNo, DiscriptionNo, Memo, Type, Value, ItemNo, SaveIdx, RankPoint, [Level], SYear, SMonth, SDay, SHour, SMinute, EYear, EMonth, EDay, EHour, EMinute, UseTime, IsUse)
			SELECT Idx, Category, TitleNo, DiscriptionNo, Memo, Type, Value, ItemNo, SaveIdx, RankPoint, [Level], SYear, SMonth, SDay, SHour, SMinute, EYear, EMonth, EDay, EHour, EMinute, UseTime, IsUse FROM dbo.TB_DefAchievements WITH (HOLDLOCK TABLOCKX)')
	
	DROP TABLE dbo.TB_DefAchievements
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefAchievements', N'TB_DefAchievements', 'OBJECT' 
	
	ALTER TABLE dbo.TB_DefAchievements ADD CONSTRAINT
		PK_TB_DefAchievements_Idx PRIMARY KEY CLUSTERED 
		(
		Idx
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]

	
	COMMIT
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefAchievements') AND [name] = N'GroupNo')
BEGIN
	ALTER TABLE [dbo].[TB_DefAchievements] ADD [GroupNo] [int] NOT NULL CONSTRAINT DF_TB_DefAchievements_GroupNo DEFAULT (0)
END
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefAchievements') AND [name] = N'CustomValue1')
BEGIN
	ALTER TABLE [dbo].[TB_DefAchievements] ADD [CustomValue1] [bigint] NOT NULL CONSTRAINT DF_TB_DefAchievements_CustomValue1 DEFAULT (0)
END
GO

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefAchievements') AND [name] = N'CustomValue1')
BEGIN
	EXEC SP_RENAME N'dbo.TB_DefAchievements.CustomValue1', N'CustomValue', N'COLUMN'
END
GO

