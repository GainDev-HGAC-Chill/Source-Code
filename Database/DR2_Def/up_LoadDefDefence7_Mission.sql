USE [DR2_Def]
GO

SET ANSI_NULLS ON
SET QUOTED_IDENTIFIER ON

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefDefence7_Mission]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefDefence7_Mission]
END
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefDefence7_Mission]

AS
BEGIN
	SET NOCOUNT ON;
	
	SELECT [Mission_No],[Mission_Type],[Min_Level],[Max_Level],
			[Slot_F1], [Slot_F2], [Slot_F3], [Slot_F4], [Slot_F5],[Slot_F6],[Slot_F7],[Slot_F8],[Skill01],[Skill02],[Skill03],[Skill04],[Skill05],[Skill06],[Skill07],[Skill08]
	FROM [dbo].[TB_DefDefence7_Mission]
END

GO

