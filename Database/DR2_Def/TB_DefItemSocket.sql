USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefItemSocket]') AND [type] IN (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefItemSocket](
		[Index] [int] IDENTITY(1,1) NOT NULL,
		[EquipPos] [int] NOT NULL,
		[Memo] nvarchar(50) NULL,
		[LevelLimit] [int] NOT NULL,
		[Socket_Order] [int] NOT NULL,
		[SuccessRate] [int] NOT NULL,
		[SoulItemCount] [int] NOT NULL,
		[NeedMoney] [bigint] NOT NULL,
		[SocketItemNo] [int] NOT NULL,
		[RestorationItemNo] [int] NOT NULL,
		[ResetItemNo] [int] NOT NULL	
	 CONSTRAINT [PK_TB_DefItemSocket] PRIMARY KEY CLUSTERED 
	(
		[EquipPos], [LevelLimit], [Socket_Order]  ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END

GO
