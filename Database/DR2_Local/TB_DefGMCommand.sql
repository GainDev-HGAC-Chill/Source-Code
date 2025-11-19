USE [DR2_Local]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefGmCommand]'))
BEGIN
	CREATE TABLE [dbo].[TB_DefGmCommand](
		[CmdNo] [int] NOT NULL,
		[Memo] [nvarchar](100) NULL,
		[Level] [tinyint] NOT NULL,
	 CONSTRAINT [PK_TB_DefGmCommand] PRIMARY KEY CLUSTERED 
	(
		[CmdNo] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON)
	)ON [PRIMARY]

	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'GM Command list' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefGmCommand'
END
GO

ALTER TABLE [dbo].[TB_DefGmCommand] ADD  CONSTRAINT [DF_TB_DefGmCommand_Level]  DEFAULT ((0)) FOR [Level]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefGmCommand]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefGmCommand]
GO

CREATE PROCEDURE [dbo].[up_LoadDefGmCommand]
AS

DECLARE @Ret INT
SET @Ret = 0

BEGIN

	SELECT	[CmdNo],[Level]
	FROM 	[dbo].[TB_DefGmCommand] with(nolock)
END

RETURN @Ret
GO

TRUNCATE TABLE [TB_DefGmCommand]
GO

