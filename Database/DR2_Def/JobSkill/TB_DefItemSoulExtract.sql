USE [DR2_Def]
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefItemSoulExtract]') and [type] in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefItemSoulExtract](
		[f_Index] [int] NOT NULL,
		[f_EquipPos] [int] NOT NULL,
		[f_Memo] [nvarchar](50) NULL,
		[f_LevelLimit] [int] NOT NULL,
		[f_SuccessRate] [int] NOT NULL,
		[f_ExtractItemNo] [int] NOT NULL,
		[f_ResultItemNo] [int] NOT NULL,
	CONSTRAINT [PK_TB_DefItemSoulExtract] PRIMARY KEY CLUSTERED 
		(
			[f_EquipPos]  ASC,
			[f_LevelLimit]  ASC
		)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]
END
GO

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemSoulExtract') and [name] = N'f_EquipType')
BEGIN
	EXECUTE sp_rename N'dbo.TB_DefItemSoulExtract.f_EquipType', N'Tmp_f_EquipPos', 'COLUMN' 
	EXECUTE sp_rename N'dbo.TB_DefItemSoulExtract.Tmp_f_EquipPos', N'f_EquipPos', 'COLUMN' 
END
GO