USE [DR2_Def]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadDefSkillIdxToSkillNo]    Script Date: 07/10/2009 15:09:12 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefSkillIdxToSkillNo]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefSkillIdxToSkillNo]

USE [DR2_Def]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadDefSkillIdxToSkillNo]    Script Date: 07/10/2009 15:09:19 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_LoadDefSkillIdxToSkillNo]

AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;


	SELECT [SkillIdx]
		  ,[SkillNo]
	  FROM [dbo].[TB_DefSkillIdxToSkillNo]
  
END
