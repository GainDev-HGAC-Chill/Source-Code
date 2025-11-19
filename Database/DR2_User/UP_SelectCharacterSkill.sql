IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_SelectCharacterSkill]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[UP_SelectCharacterSkill]
GO

/****** Object:  StoredProcedure [dbo].[UP_SelectCharacterSkill]    Script Date: 07/09/2009 11:31:51 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[UP_SelectCharacterSkill]

@CharGuid UNIQUEIDENTIFIER

AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [CharacterID]
		  ,[ExtraSkillPoint]
		  ,[Skills]
	  FROM [dbo].[TB_CharacterSub] WHERE CharacterID = @CharGuid
  
END



GO