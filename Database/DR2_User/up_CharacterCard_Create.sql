USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_CharacterCard_Create]    Script Date: 12/01/2009 18:16:34 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_CharacterCard_Create]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_CharacterCard_Create]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[up_CharacterCard_Create]

@CharacterID UNIQUEIDENTIFIER,
@Year TINYINT,
@Sex TINYINT,
@Local INT,
@Comment NVARCHAR(50),
@Enable TINYINT,
@PopularPoint BIGINT,
@TodayPopularPoint bigint,
@Constellation TINYINT,
@Blood TINYINT,
@Hobby TINYINT,
@Style TINYINT,
@BGndNo int

AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	IF EXISTS (SELECT 1 FROM dbo.TB_UserCharacter_Card WHERE characterguid = @CharacterID)
	BEGIN
	
		SELECT 1
		
	END
	ELSE
	BEGIN
		
		INSERT INTO dbo.TB_UserCharacter_Card 
		([characterguid],[year],[sex],[local],[popularpoint],[todaypopularpoint],[comment],[enable],[Constellation],[Blood],[Hobby],[Style],[BGndNo])
		VALUES(@CharacterID,@Year,@Sex,@Local,0,0,@Comment,1,@Constellation,@Blood,@Hobby,@Style,@BGndNo)
			
		SELECT @@ERROR
	END
END


