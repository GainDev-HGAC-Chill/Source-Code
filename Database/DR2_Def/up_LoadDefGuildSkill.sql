IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefGuildSkill3]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_LoadDefGuildSkill3]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefGuildSkill]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_LoadDefGuildSkill]
GO

/****** Object:  StoredProcedure [dbo].[up_LoadDefGuildSkill]    Script Date: 07/09/2009 11:25:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author: 
-- Create date: 2008.5.11
-- Description:	20080912 - GuildExp Ãß°¡
-- =============================================
CREATE PROCEDURE [dbo].[up_LoadDefGuildSkill]
AS
BEGIN
	SET NOCOUNT ON;

	SELECT
       [GuildLv]
      ,[SkillNo]
      ,[SkillPoint]
      ,[Gold]
      ,[GuildExp]
      ,[Item1]
      ,[Count1]
      ,[Item2]
      ,[Count2]
  FROM [dbo].[TB_DefGuildSkill] with(nolock)
END

GO