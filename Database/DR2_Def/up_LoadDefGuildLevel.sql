USE DR2_DEF
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefGuildLevel2]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_LoadDefGuildLevel2]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefGuildLevel]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_LoadDefGuildLevel]
GO

/****** Object:  StoredProcedure [dbo].[up_LoadDefGuildLevel]    Script Date: 07/09/2009 11:25:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_LoadDefGuildLevel]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

    -- Insert statements for procedure here
	SELECT
       [GuildLv]
      ,[MaxMemberCount]
      ,[SkillPoint]
      ,[Exp]
      ,[Gold]
      ,[Item1]
      ,[Count1]
      ,[Item2]
      ,[Count2]
      ,[Item3]
      ,[Count3]
      ,[Item4]
      ,[Count4]
      ,[Item5]
      ,[Count5]
      ,[IntroText]
      ,[ResultText]
      ,[f_AutoChangeOwner1]
      ,[f_AutoChangeOwner2]
      ,[f_AutoChangeOwnerRun]
  FROM [dbo].[TB_DefGuildLevel] with(nolock)
END

GO