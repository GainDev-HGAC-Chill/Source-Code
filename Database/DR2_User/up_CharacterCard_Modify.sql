USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_CharacterCard_Modify]    Script Date: 11/27/2009 17:49:47 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_CharacterCard_Modify]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_CharacterCard_Modify]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[up_CharacterCard_Modify]

@CharacterID UNIQUEIDENTIFIER,
@Year TINYINT,
@Sex TINYINT,
@Local INT,
@Comment NVARCHAR(50),
@Enable TINYINT,
@PopularPoint BIGINT,
@TodayPopularPoint BIGINT,
@Constellation TINYINT,
@Blood TINYINT,
@Hobby TINYINT,
@Style TINYINT,
@BGndNo INT

AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE dbo.TB_UserCharacter_Card 
	SET [year] = @Year, 
		[sex] = @Sex, 
		[local] = @Local, 
		[comment] = @Comment,
		[enable] = @Enable,
		[popularpoint] = @PopularPoint,
		[Todaypopularpoint] = @TodayPopularPoint,
		[Constellation] = @Constellation,
		[Blood] = @Blood,
		[Hobby] = @Hobby,
		[Style] = @Style,
		[BGndNo] = @BGndNo
	WHERE characterguid = @CharacterID
	
	SELECT @@ERROR

END


