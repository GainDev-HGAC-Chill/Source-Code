USE [DR2_Def]
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_LoadDefJobSkill_Shop]') and [type] in (N'P'))
BEGIN
	DROP PROCEDURE [dbo].[UP_LoadDefJobSkill_Shop]
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[UP_LoadDefJobSkill_Shop]
AS
BEGIN
	SET NOCOUNT ON;

	SELECT [NationCodeStr]
		,[f_IDX] 
		,[f_Job_Category]
		,[f_Kind_Category]
		,[f_ItemNo]
		,[f_Price]
		,[f_NPC_Guid]
		,[f_TimeType]
		,[f_UseTime]
	FROM [dbo].[TB_DefJobSkill_Shop]
	WHERE [f_ShowUser] = 1
END
GO