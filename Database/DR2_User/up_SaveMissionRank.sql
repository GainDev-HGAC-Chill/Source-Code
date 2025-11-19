USE [DR2_User]
IF EXISTS(SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'up_SaveMissionRank'))
BEGIN
	DROP Proc [dbo].[up_SaveMissionRank]
END
GO

/****** Object:  StoredProcedure [dbo].[up_SaveMissionRank]    Script Date: 03/31/2009 14:04:53 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

/*
////////////////////////////////////////////////////////////////////////
// Lasst Update by : 
// Update date  : 
// Description : 
// [PARAMETER] : 
// [RETURN] : 
// [REMARK]
////////////////////////////////////////////////////////////////////////
*/
CREATE Proc [dbo].[up_SaveMissionRank]
(
	@MissionKey int,
	@Level tinyint,
	@Point int,
	@PlayTime int,
	@CharacterID uniqueidentifier,
	@Memo nvarchar(20),
	@UserLevel int,
	@Class tinyint,
	@RegistDate datetime
)
AS
Set Nocount on
Set Xact_Abort On

BEGIN
DECLARE @iErr int
SET @iErr = 0

	INSERT INTO [dbo].[TB_Mission_Rank]
	(
		[MissionKey],
		[Level],
		[Point],
		[PlayTime],
		[CharacterID],
		[Memo],
		[UserLevel],
		[Class],
		[Date]
	)
	values
	(
		@MissionKey,
		@Level,
		@Point,
		@PlayTime,
		@CharacterID,
		@Memo,
		@UserLevel,
		@Class,
		@RegistDate
	)
	IF @@ERROR <> 0
	BEGIN
		SET @iErr = 99
		GOTO RETURN_POS
	END

RETURN_POS:
	SELECT @iErr
	return @iErr
END



GO