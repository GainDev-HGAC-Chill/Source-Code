USE [DR2_User]
IF EXISTS(SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'up_FriendList_Modify_Add'))
BEGIN
	DROP PROCEDURE [dbo].[up_FriendList_Modify_Add]
END
GO


/****** Object:  StoredProcedure [dbo].[up_FriendList_Modify_Add]    Script Date: 03/31/2009 14:04:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


/*
////////////////////////////////////////////////////////////////////////
// Lasst Update by : 육정범
// Update date  : 2008-10-21
// Description : 친구 DB아이템 수정
// [PARAMETER] : 
// [RETURN] : 
// [REMARK]
//	2008-10-21 : 육정범, ADD/ DEL/ MODIFY/ SELECT 로 분리
//	2008-10-07 : Eric Kim, Character DB 가 둘로 나누어진 것 적용
//	2008-06-03 : <하승봉>
////////////////////////////////////////////////////////////////////////
*/
CREATE PROCEDURE [dbo].[up_FriendList_Modify_Add]
(
	@OwnerMemberGuid UNIQUEIDENTIFIER,
	@FriendGroupName nvarchar(20),
	@FriendMemberGuid UNIQUEIDENTIFIER,
	@ChatStatus INT
)
AS

SET XACT_ABORT ON;
SET NOCOUNT ON;
DECLARE @Err INT;
DECLARE @SystemError INT;



	DECLARE @RetGuid UNIQUEIDENTIFIER;
	SET @Err = 0;

	--내가 이 DB에 있는지?
	IF NOT EXISTS ( SELECT 1 FROM [dbo].[TB_CharacterBasic] WHERE [CharacterID] = @OwnerMemberGuid )
	BEGIN
		SET @Err = 301;--오류
		GOTO __rollback_tran;
	END

	--있다면 중복은 아닌지?
	IF EXISTS (SELECT 1 FROM [dbo].[TB_UserFriend] WHERE [OwnerMemberGuid] = @OwnerMemberGuid AND [FriendMemberGuid] = @FriendMemberGuid )
	BEGIN
		SET @Err = 302;--오류
		GOTO __rollback_tran;
	END

	--내 목록에 추가
	INSERT INTO [dbo].[TB_UserFriend]
		([OwnerMemberGuid], [FriendGroupName], [FriendMemberGuid], [FriendStatus])
		VALUES ( @OwnerMemberGuid, @FriendGroupName, @FriendMemberGuid, @ChatStatus);
	
	SET @SystemError = @@ERROR
	IF @SystemError <> 0
	BEGIN
		SET @Err = 303;--오류
		GOTO __rollback_tran;
	END

	SET @Err = 1;
	GOTO __commit_tran;


__commit_tran:
BEGIN
	SELECT @Err, @OwnerMemberGuid, @SystemError
	RETURN @Err
END

__rollback_tran:
BEGIN
	SELECT @Err, @OwnerMemberGuid
	RETURN @Err
END



GO