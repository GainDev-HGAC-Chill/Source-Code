USE [DR2_Def]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefSkillExtendItem]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefSkillExtendItem]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefSkillExtendItem]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT 	   [ExtendIdx]
		  ,[SkillNo01]
		  ,[SkillNo02]
		  ,[SkillNo03]
		  ,[SkillNo04]
		  ,[SkillNo05]
		  ,[SkillNo06]
		  ,[SkillNo07]
		  ,[SkillNo08]
		  ,[SkillNo09]
		  ,[SkillNo10]
	  FROM [dbo].[TB_DefSkillExtendItem]

END
