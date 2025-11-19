USE [dr2_def]
GO
--1. 원하는 테이블의 원하는 최종적인 컬럼이 존재하지 않으면
IF not  EXISTS(SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME='TB_DefItemEnchantShift' AND COLUMN_NAME='f_NationCode')
BEGIN
	BEGIN TRY
	BEGIN TRAN
	--2. 템프테이블 생성
	CREATE TABLE #TEMP(
		[f_NationCode] [nvarchar](50) NOT NULL,
		[EquipType] [int] NOT NULL,
		[Memo] [nvarchar](100) NULL,
		[LevelLimit] [int] NOT NULL,
		[EnchnatGrade] [int] NOT NULL,
		[EnchantItemNo] [int] NOT NULL,
		[EnchantItemCount] [int] NOT NULL,
		[NeedMoney] [int] NOT NULL,
		[EnchantShiftGemNo] [int] NOT NULL,
		[EnchantShiftGemCount] [int] NOT NULL,
		[InsuranceItemNo] [int] NOT NULL,
		[EnchantShiftRatePlus2] [int] NOT NULL,
		[EnchantShiftRatePlus1] [int] NOT NULL,
		[EnchantShiftRateSame] [int] NOT NULL,
		[EnchantShiftRateMinus1] [int] NOT NULL,
		[EnchantShiftRateMinus2] [int] NOT NULL,
		[EnchantShiftRateDelete] [int] NOT NULL
	)
	INSERT INTO #TEMP(
	f_NationCode, EquipType,	Memo,	LevelLimit,	EnchnatGrade,
	EnchantItemNo,	EnchantItemCount,	NeedMoney,	EnchantShiftGemNo,	EnchantShiftGemCount,
	InsuranceItemNo,	EnchantShiftRatePlus2,	EnchantShiftRatePlus1,	EnchantShiftRateSame,
	EnchantShiftRateMinus1,	EnchantShiftRateMinus2,	EnchantShiftRateDelete
	)SELECT '0', EquipType,	Memo,	LevelLimit,	EnchnatGrade,
	EnchantItemNo,	EnchantItemCount,	NeedMoney,	EnchantShiftGemNo,	EnchantShiftGemCount,
	InsuranceItemNo,	EnchantShiftRatePlus2,	EnchantShiftRatePlus1,	EnchantShiftRateSame,
	EnchantShiftRateMinus1,	EnchantShiftRateMinus2,	EnchantShiftRateDelete
	FROM TB_DefItemEnchantShift
	
 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefItemEnchantShift_f_NationCode]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefItemEnchantShift] DROP CONSTRAINT [DF_TB_DefItemEnchantShift_f_NationCode]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefItemEnchantShift_EquipPos]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefItemEnchantShift] DROP CONSTRAINT [DF_TB_DefItemEnchantShift_EquipPos]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefItemEnchantShift_LevelLimit]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefItemEnchantShift] DROP CONSTRAINT [DF_TB_DefItemEnchantShift_LevelLimit]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefItemEnchantShift_EnchnatGrade]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefItemEnchantShift] DROP CONSTRAINT [DF_TB_DefItemEnchantShift_EnchnatGrade]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefItemEnchantShift_EnchnatItemNo]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefItemEnchantShift] DROP CONSTRAINT [DF_TB_DefItemEnchantShift_EnchnatItemNo]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefItemEnchantShift_EnchantItemCount]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefItemEnchantShift] DROP CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantItemCount]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefItemEnchantShift_NeedMoney]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefItemEnchantShift] DROP CONSTRAINT [DF_TB_DefItemEnchantShift_NeedMoney]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefItemEnchantShift_EnchantShiftGemNo]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefItemEnchantShift] DROP CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftGemNo]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefItemEnchantShift_EnchantShiftGemCount]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefItemEnchantShift] DROP CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftGemCount]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefItemEnchantShift_InsuranceItemNo]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefItemEnchantShift] DROP CONSTRAINT [DF_TB_DefItemEnchantShift_InsuranceItemNo]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefItemEnchantShift_EnchantShiftRatePlus2]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefItemEnchantShift] DROP CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftRatePlus2]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefItemEnchantShift_EnchantShiftRatePlus1]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefItemEnchantShift] DROP CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftRatePlus1]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefItemEnchantShift_EnchantShiftRateSame]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefItemEnchantShift] DROP CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftRateSame]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefItemEnchantShift_EnchantShiftRateMinus1]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefItemEnchantShift] DROP CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftRateMinus1]
END


IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefItemEnchantShift_EnchantShiftRateMinus2]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefItemEnchantShift] DROP CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftRateMinus2]
END

 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefItemEnchantShift_EnchantShiftRateDelete]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefItemEnchantShift] DROP CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftRateDelete]
END

 
/****** Object:  Table [dbo].[TB_DefItemEnchantShift]    Script Date: 07/05/2012 14:31:16 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefItemEnchantShift]') AND type in (N'U'))
DROP TABLE [dbo].[TB_DefItemEnchantShift]
 
CREATE TABLE [dbo].[TB_DefItemEnchantShift](
	[f_NationCode] [nvarchar](50) NOT NULL,
	[index] [int] IDENTITY(1,1) NOT FOR REPLICATION NOT NULL,
	[EquipType] [int] NOT NULL,
	[Memo] [nvarchar](100) NULL,
	[LevelLimit] [int] NOT NULL,
	[EnchnatGrade] [int] NOT NULL,
	[EnchantItemNo] [int] NOT NULL,
	[EnchantItemCount] [int] NOT NULL,
	[NeedMoney] [int] NOT NULL,
	[EnchantShiftGemNo] [int] NOT NULL,
	[EnchantShiftGemCount] [int] NOT NULL,
	[InsuranceItemNo] [int] NOT NULL,
	[EnchantShiftRatePlus2] [int] NOT NULL,
	[EnchantShiftRatePlus1] [int] NOT NULL,
	[EnchantShiftRateSame] [int] NOT NULL,
	[EnchantShiftRateMinus1] [int] NOT NULL,
	[EnchantShiftRateMinus2] [int] NOT NULL,
	[EnchantShiftRateDelete] [int] NOT NULL,
 CONSTRAINT [PK_TB_DefItemEnchantShift] PRIMARY KEY CLUSTERED 
(
	[f_NationCode] ASC,
	[EquipType] ASC,
	[LevelLimit] ASC,
	[EnchnatGrade] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]


EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Item EnchantShift' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefItemEnchantShift'

ALTER TABLE [dbo].[TB_DefItemEnchantShift] ADD  CONSTRAINT [DF_TB_DefItemEnchantShift_f_NationCode]  DEFAULT ((0)) FOR [f_NationCode]

ALTER TABLE [dbo].[TB_DefItemEnchantShift] ADD  CONSTRAINT [DF_TB_DefItemEnchantShift_EquipPos]  DEFAULT ((0)) FOR [EquipType]

ALTER TABLE [dbo].[TB_DefItemEnchantShift] ADD  CONSTRAINT [DF_TB_DefItemEnchantShift_LevelLimit]  DEFAULT ((0)) FOR [LevelLimit]

ALTER TABLE [dbo].[TB_DefItemEnchantShift] ADD  CONSTRAINT [DF_TB_DefItemEnchantShift_EnchnatGrade]  DEFAULT ((0)) FOR [EnchnatGrade]

ALTER TABLE [dbo].[TB_DefItemEnchantShift] ADD  CONSTRAINT [DF_TB_DefItemEnchantShift_EnchnatItemNo]  DEFAULT ((0)) FOR [EnchantItemNo]

ALTER TABLE [dbo].[TB_DefItemEnchantShift] ADD  CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantItemCount]  DEFAULT ((0)) FOR [EnchantItemCount]

ALTER TABLE [dbo].[TB_DefItemEnchantShift] ADD  CONSTRAINT [DF_TB_DefItemEnchantShift_NeedMoney]  DEFAULT ((0)) FOR [NeedMoney]

ALTER TABLE [dbo].[TB_DefItemEnchantShift] ADD  CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftGemNo]  DEFAULT ((0)) FOR [EnchantShiftGemNo]

ALTER TABLE [dbo].[TB_DefItemEnchantShift] ADD  CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftGemCount]  DEFAULT ((0)) FOR [EnchantShiftGemCount]

ALTER TABLE [dbo].[TB_DefItemEnchantShift] ADD  CONSTRAINT [DF_TB_DefItemEnchantShift_InsuranceItemNo]  DEFAULT ((0)) FOR [InsuranceItemNo]
ALTER TABLE [dbo].[TB_DefItemEnchantShift] ADD  CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftRatePlus2]  DEFAULT ((0)) FOR [EnchantShiftRatePlus2]

ALTER TABLE [dbo].[TB_DefItemEnchantShift] ADD  CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftRatePlus1]  DEFAULT ((0)) FOR [EnchantShiftRatePlus1]

ALTER TABLE [dbo].[TB_DefItemEnchantShift] ADD  CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftRateSame]  DEFAULT ((0)) FOR [EnchantShiftRateSame]

ALTER TABLE [dbo].[TB_DefItemEnchantShift] ADD  CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftRateMinus1]  DEFAULT ((0)) FOR [EnchantShiftRateMinus1]
ALTER TABLE [dbo].[TB_DefItemEnchantShift] ADD  CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftRateMinus2]  DEFAULT ((0)) FOR [EnchantShiftRateMinus2]

ALTER TABLE [dbo].[TB_DefItemEnchantShift] ADD  CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftRateDelete]  DEFAULT ((0)) FOR [EnchantShiftRateDelete]

--TEMP를 원테이블에...
INSERT INTO TB_DefItemEnchantShift(
	f_NationCode, EquipType,	Memo,	LevelLimit,	EnchnatGrade,
	EnchantItemNo,	EnchantItemCount,	NeedMoney,	EnchantShiftGemNo,	EnchantShiftGemCount,
	InsuranceItemNo,	EnchantShiftRatePlus2,	EnchantShiftRatePlus1,	EnchantShiftRateSame,
	EnchantShiftRateMinus1,	EnchantShiftRateMinus2,	EnchantShiftRateDelete
	)SELECT '0', EquipType,	Memo,	LevelLimit,	EnchnatGrade,
	EnchantItemNo,	EnchantItemCount,	NeedMoney,	EnchantShiftGemNo,	EnchantShiftGemCount,
	InsuranceItemNo,	EnchantShiftRatePlus2,	EnchantShiftRatePlus1,	EnchantShiftRateSame,
	EnchantShiftRateMinus1,	EnchantShiftRateMinus2,	EnchantShiftRateDelete
	FROM #TEMP

DROP TABLE #TEMP

COMMIT TRAN
END TRY
BEGIN CATCH
ROLLBACK TRAN
END CATCH
END

 