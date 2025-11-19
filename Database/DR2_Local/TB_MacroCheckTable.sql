USE [DR2_Local]
GO


/****** Object:  Table [dbo].[TB_MacroCheckTable]    Script Date: 03/23/2009 21:00:27 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

ALTER TABLE [dbo].[TB_MacroCheckTable] ADD
[MacroReleaseTime] [int] NULL,
[MacroCheckCount] [int] NULL,
[MacroPopupMax] [int] NULL,
[MacroInputTime] [int] NULL
GO

ALTER TABLE [dbo].[TB_MacroCheckTable] DROP
COLUMN [MovedZoneCount],
COLUMN [UsedSkillCount],
COLUMN [UsedItemCount],
COLUMN [MonsterKillCount],
COLUMN [MonsterLevel],
COLUMN [ZoneX],
COLUMN [ZoneY],
COLUMN [ZoneZ]
GO

DELETE FROM [dbo].[TB_MacroCheckTable]
INSERT INTO [dbo].[TB_MacroCheckTable] ([MacroCheckTime],[MacroReleaseTime],[MacroCheckCount],[MacroPopupMax],[MacroInputTime]) VALUES(60,120,30,60,120)
GO