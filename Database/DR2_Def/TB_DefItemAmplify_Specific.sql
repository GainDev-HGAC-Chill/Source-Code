USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id=OBJECT_ID(N'[dbo].[TB_DefItemAmplify_Specific]')) 
BEGIN
	CREATE TABLE [dbo].[TB_DefItemAmplify_Specific](
		[f_NationCodeStr] [nvarchar](50) NOT NULL,
		[EquipPos] [int] NOT NULL,
		[memo] [nvarchar](100) NULL,
		[Abil_Type] [smallint] NOT NULL,
		[AmplifyRate_Specific] [int] NOT NULL
	) ON [PRIMARY]
END
GO

IF EXISTS (SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefItemAmplify_Specific]') and name = N'EquipPos')
BEGIN
	exec sp_rename N'[dbo].[TB_DefItemAmplify_Specific].EquipPos', N'EquipType', N'COLUMN'
END