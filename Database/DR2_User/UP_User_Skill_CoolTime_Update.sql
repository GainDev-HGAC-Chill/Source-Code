USE DR2_User
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_User_Skill_CoolTime_Update]') AND [type] IN (N'P'))
BEGIN
	DROP PROCEDURE [dbo].[UP_User_Skill_CoolTime_Update]
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[UP_User_Skill_CoolTime_Update]
	@CharacterID UNIQUEIDENTIFIER,
	@SkillNo INT,
	@CoolTime INT
AS
BEGIN
	SET NOCOUNT ON;
	INSERT INTO dbo.TB_User_Skill_CoolTime([CharacterID], [SkillNo], [CoolTime]) VALUES(@CharacterID, @SkillNo, @CoolTime)
END
GO
