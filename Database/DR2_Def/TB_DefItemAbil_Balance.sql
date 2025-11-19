USE [DR2_Def]
GO

/****** Object:  Table [dbo].[TB_DefItemAbil]    Script Date: 02/17/2011 17:04:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemAbil_Balance') AND [name] = N'f_NationCodeStr')
BEGIN
	BEGIN TRANSACTION
	CREATE TABLE [dbo].[TB_DefItemAbil_Balance](
		[f_NationCodeStr] [nvarchar](50) NOT NULL CONSTRAINT [DF_TB_DefItemAbil_Balance_f_NationCodeStr]  DEFAULT (N'0'),
		[ItemAbilNo] [int] NOT NULL,
		[Memo] [nvarchar](100) NULL,
		[Type01] [int] NOT NULL,
		[Value01] [int] NOT NULL,
		[Type02] [int] NOT NULL,
		[Value02] [int] NOT NULL,
		[Type03] [int] NOT NULL,
		[Value03] [int] NOT NULL,
		[Type04] [int] NOT NULL,
		[Value04] [int] NOT NULL,
		[Type05] [int] NOT NULL,
		[Value05] [int] NOT NULL,
		[Type06] [int] NOT NULL,
		[Value06] [int] NOT NULL,
		[Type07] [int] NOT NULL,
		[Value07] [int] NOT NULL,
		[Type08] [int] NOT NULL,
		[Value08] [int] NOT NULL,
		[Type09] [int] NOT NULL,
		[Value09] [int] NOT NULL,
		[Type10] [int] NOT NULL,
		[Value10] [int] NOT NULL,
	 CONSTRAINT [PK_TB_DefItemAbil_Balance] PRIMARY KEY CLUSTERED 
	(
		[ItemAbilNo] ASC,
		[f_NationCodeStr] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]

	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Ability of Items(Balance)' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefItemAbil_Balance'

	COMMIT
END
