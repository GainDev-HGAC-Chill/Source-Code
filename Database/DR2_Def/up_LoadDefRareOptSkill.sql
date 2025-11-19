USE [DR2_Def]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadDefRareOptSkill]    Script Date: 07/10/2009 15:08:34 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefRareOptSkill]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefRareOptSkill]

USE [DR2_Def]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadDefRareOptSkill]    Script Date: 07/10/2009 15:08:42 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_LoadDefRareOptSkill]

AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [RareOptSkillNo]
		  ,[SkillSuccessControlNo]
		  ,[SkllLvSuccessControlNo]
		  ,[SkillIdx01]
		  ,[SkillIdx02]
		  ,[SkillIdx03]
		  ,[SkillIdx04]
		  ,[SkillIdx05]
		  ,[SkillIdx06]
		  ,[SkillIdx07]
		  ,[SkillIdx08]
		  ,[SkillIdx09]
		  ,[SkillIdx10]
	  FROM [dbo].[TB_DefRareOptSkill]
  
END
