USE [DR2_User]
IF NOT EXISTS(SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'TB_Mission_Rank'))
BEGIN
	CREATE TABLE [dbo].[TB_Mission_Rank](
		[IDX] [int] IDENTITY(1,1) NOT NULL,
		[Group] [int] NOT NULL CONSTRAINT [DF_TB_Mission_Rank_Group]  DEFAULT ((0)),
		[MissionKey] [int] NOT NULL,
		[Level] [tinyint] NOT NULL,
		[CharacterID] [uniqueidentifier] NOT NULL,
		[Name] [nvarchar](20) NOT NULL,
		[Memo] [nvarchar](20) NULL,
		[UserLevel] [int] NOT NULL,
		[Class] [tinyint] NOT NULL,
		[Point] [int] NOT NULL,
		[PlayTime] [int] NOT NULL,
		[Date] [datetime] NOT NULL,
	 CONSTRAINT [PK_TB_Mission_Rank_1] PRIMARY KEY NONCLUSTERED 
	(
		[IDX] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Mission ranking information' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Mission_Rank'
END
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
GO
ALTER TABLE dbo.TB_Mission_Rank
	DROP COLUMN Name
GO
COMMIT
