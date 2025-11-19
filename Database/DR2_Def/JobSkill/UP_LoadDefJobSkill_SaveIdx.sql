USE [DR2_Def]
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.UP_LoadDefJobSkill_SaveIdx') AND [type] IN (N'P'))
BEGIN
	DROP PROCEDURE dbo.UP_LoadDefJobSkill_SaveIdx
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE dbo.UP_LoadDefJobSkill_SaveIdx
AS
BEGIN
	SET NOCOUNT ON;
	SELECT [f_SaveIdx]
		,[f_Recipe_ItemNo]
		,[f_Resource_GroupNo]
		,[f_01Need_SkillNo]
		,[f_01Need_Expertness]
		,[f_02Need_SkillNo]
		,[f_02Need_Expertness]
		,[f_03Need_SkillNo]
		,[f_03Need_Expertness]
		,[f_Recipe_Price]
		,[f_Book_ItemNo]
		,[f_AlreadyLearn]
		,[f_ShowUser]
	FROM [dbo].[TB_DefJobSkill_SaveIdx]
END
GO
