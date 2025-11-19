USE [DR2_User]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_SaveGuildEmporiaFunc]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_SaveGuildEmporiaFunc]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_SaveEmporiaFunction]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_SaveEmporiaFunction]
GO

CREATE PROCEDURE [dbo].[up_SaveEmporiaFunction]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : 엠포리아 기능 저장
// 작 성 자 : YonMy
// 작 성 일 : 2009-07-01
// 최종수정자 : 
// 수 정 일 : 
// 담 당 자 : YonMy
// N O T E : 
////////////////////////////////////////////////////////////////////////
*/
(
	@EmporiaID		uniqueidentifier,
	@Grade			tinyint,
	@FunctionNo		smallint,
	@HaveDate		datetime,
	@ExpirationDate	datetime,
	@ExtValue		bigint,
	@GuildGuid		uniqueidentifier,
	@UseExp			bigint
)
AS
SET XACT_ABORT ON
SET NOCOUNT ON

SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED

DECLARE @Ret int
SET @Ret = 0

BEGIN TRAN
	UPDATE	[dbo].[TB_Guild_Basic_Info] SET [CurrentExp] = [CurrentExp] - @UseExp
	WHERE	[GuildGuid] = @GuildGuid
		
	IF @@ERROR <> 0
	BEGIN
		SET @Ret = 99
		GOTO ErrorHandler	
	END
 
	IF EXISTS (SELECT 1 FROM [dbo].[TB_Emporia_Function] WHERE [EmporiaID] = @EmporiaID AND [Grade] = @Grade AND [FunctionNo] = @FunctionNo)
	BEGIN
	
		UPDATE	[dbo].[TB_Emporia_Function]
		SET		[HaveDate] = @HaveDate
			,	[ExpirationDate] = @ExpirationDate
			,	[ExtValue] = @ExtValue
		WHERE	[EmporiaID] = @EmporiaID AND [Grade] = @Grade AND [FunctionNo] = @FunctionNo
		
	END	
	ELSE
	BEGIN
	
		INSERT INTO [dbo].[TB_Emporia_Function]
			(
				[EmporiaID]
			,	[Grade]
			,	[FunctionNo]
			,	[HaveDate]
			,	[ExpirationDate]
			,	[ExtValue]
			)VALUES(
				@EmporiaID
			,	@Grade
			,	@FunctionNo
			,	@HaveDate
			,	@ExpirationDate
			,	@ExtValue
			)
	END
	
	IF @@ERROR = 0
	BEGIN 
		COMMIT TRAN
		RETURN @Ret
	END
	
	SET @Ret = 99
	
ErrorHandler:
ROLLBACK TRAN
RETURN @Ret
GO