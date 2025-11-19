USE [DR2_Local]
GO


/****** Object:  Table [dbo].[TB_Common_CashItemPrice]    Script Date: 04/14/2009 11:43:57 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_Common_CashItemPrice]'))
BEGIN
	CREATE TABLE [dbo].[TB_Common_CashItemPrice](
		[Idx] [int] IDENTITY(1,1) NOT NULL,
		[CashItemIdx] [int] NOT NULL,
		[TimeType] [tinyint] NOT NULL,
		[ItemUseTime] [int] NOT NULL,
		[Cash] [int] NOT NULL,
		[IsDiscount] [bit] NOT NULL,
		[DiscountCash] [int] NULL,
		[ExtendCash] [int] NULL,
		[DiscountExtendCash] [int] NULL,
		[IsExtendDiscount] [bit] NULL
	) ON [PRIMARY]
END
GO

IF NOT EXISTS(SELECT * FROM sys.Columns WHERE object_id = OBJECT_ID(N'dbo.TB_Common_CashItemPrice') and [name] = N'IsOnlyMileage')
BEGIN
	ALTER TABLE [dbo].[TB_Common_CashItemPrice] ADD [IsOnlyMileage] [bit] NULL
END
GO

IF NOT EXISTS(SELECT * FROM sys.Columns WHERE object_id = OBJECT_ID(N'dbo.TB_Common_CashItemPrice') and [name] = N'PriceIdx')
BEGIN
	ALTER TABLE [dbo].[TB_Common_CashItemPrice] ADD [PriceIdx] [int] NULL
END
GO


IF NOT EXISTS(SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'dbo.TB_Common_CashItemPrice') and [name] = N'PK_TB_Common_CashItemPrice')
BEGIN
	SET XACT_ABORT ON
	
	SELECT row_number() over (order by idx) AS [NewIdx]
		,[CashItemIdx],[TimeType],[ItemUseTime],[Cash],[IsDiscount],[DiscountCash],[ExtendCash],[DiscountExtendCash],[IsExtendDiscount],[IsOnlyMileage],[PriceIdx]
		INTO #Tmp
		FROM [dbo].[TB_Common_CashItemPrice]

	TRUNCATE TABLE dbo.TB_Common_CashItemPrice

	SET IDENTITY_INSERT dbo.TB_Common_CashItemPrice ON
	INSERT INTO [dbo].[TB_Common_CashItemPrice] ([Idx],[CashItemIdx],[TimeType],[ItemUseTime],[Cash],[IsDiscount],[DiscountCash],[ExtendCash],[DiscountExtendCash],[IsExtendDiscount],[IsOnlyMileage],[PriceIdx])
		SELECT * FROM #Tmp
	SET IDENTITY_INSERT dbo.TB_Common_CashItemPrice OFF

	ALTER TABLE dbo.TB_Common_CashItemPrice ADD CONSTRAINT
	PK_TB_Common_CashItemPrice PRIMARY KEY CLUSTERED 
	(
	Idx
	) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
	SET XACT_ABORT OFF
END