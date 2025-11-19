USE [DR2_Local]
GO

/****** Object:  Table [dbo].[TB_TreasureChest]    Script Date: 12/06/2010 14:23:34 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.TB_TreasureChest') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[TB_TreasureChest](
	[BoxItemNo] [int] NOT NULL,
	[KeyItemNo] [int] NOT NULL,
	[memo] [nvarchar](50) NULL,
	[ResultItemNo] [int] NULL,
	[ResultItemCount] [smallint] NULL,
	[TimeType] [tinyint] NULL,
	[UseTime] [smallint] NULL,
	[Rarity] [tinyint] NULL,
	[EnchantType] [tinyint] NULL,
	[EnchantLevel] [tinyint] NULL,
	[Rate] [int] NULL,
	[Idx] [int] IDENTITY(1,1) NOT NULL,
	[Broadcast] [tinyint] NULL,
 CONSTRAINT [PK_TB_TreasureChest] PRIMARY KEY CLUSTERED 
(
	[Idx] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
END
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.[TB_TreasureChest]') and name = N'f_NationCodeStr')
BEGIN
	EXECUTE sp_rename N'dbo.TB_TreasureChest', N'Tmp_TB_TreasureChest', 'OBJECT'

	CREATE TABLE [dbo].[TB_TreasureChest](
		[f_NationCodeStr] [nvarchar](50) NOT NULL CONSTRAINT [DF_DefTreasureChest_f_NationCodeStr]  DEFAULT ((0)),
		[BoxItemNo] [int] NOT NULL,
		[KeyItemNo] [int] NOT NULL,
		[memo] [nvarchar](50) NULL,
		[ResultItemNo] [int] NULL,
		[ResultItemCount] [smallint] NULL,
		[TimeType] [tinyint] NULL,
		[UseTime] [smallint] NULL,
		[Rarity] [tinyint] NULL,
		[EnchantType] [tinyint] NULL,
		[EnchantLevel] [tinyint] NULL,
		[Rate] [int] NULL,
		[Idx] [int] IDENTITY(1,1) NOT NULL,
		[Broadcast] [tinyint] NULL,
	 CONSTRAINT [PK_TB_TreasureChest2] PRIMARY KEY CLUSTERED 
	(
		[Idx] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]

	CREATE NONCLUSTERED INDEX IX_TreasureChest ON [dbo].[TB_TreasureChest]
	(
		f_NationCodeStr,
		BoxItemNo,
		KeyItemNo,
		ResultItemNo,
		ResultItemCount
	) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]

	INSERT INTO [TB_TreasureChest]
           ([BoxItemNo],[KeyItemNo],[memo],[ResultItemNo],[ResultItemCount],[TimeType],[UseTime],[Rarity],[EnchantType],[EnchantLevel],[Rate],[Broadcast])
     SELECT [BoxItemNo],[KeyItemNo],[memo],[ResultItemNo],[ResultItemCount],[TimeType],[UseTime],[Rarity],[EnchantType],[EnchantLevel],[Rate],[Broadcast] FROM Tmp_TB_TreasureChest

	DROP TABLE [dbo].[Tmp_TB_TreasureChest]
END
GO
