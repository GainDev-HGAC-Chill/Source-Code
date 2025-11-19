USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_FriendList_Modify_SELECT]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_FriendList_Modify_SELECT]
GO

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
CREATE PROCEDURE [dbo].[up_FriendList_Modify_SELECT]
(
	@OwnerMemberGuid UNIQUEIDENTIFIER
)
AS

SET NOCOUNT ON;
SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED

	SELECT 
		[FriendGroupName], 
		[FriendMemberGuid], 
		B.[Name], 
		[FriendStatus],
		C.StreetNo,
		C.HouseNo
		FROM [dbo].[TB_UserFriend] AS A
		INNER JOIN [dbo].[TB_CharacterBasic] AS B ON A.FriendMemberGuid = B.CharacterID
		left join dbo.TB_User_MyHome_Base AS C on A.FriendMemberGuid = C.OwnerGuid
		WHERE [OwnerMemberGuid] = @OwnerMemberGuid;

	RETURN @@rowcount





