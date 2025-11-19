USE DR2_User

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_DeleteUserCharacterSub]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_DeleteUserCharacterSub]
END 

set ANSI_NULLS ON
set QUOTED_IDENTIFIER ON
go

/*
////////////////////////////////////////////////////////////////////////
// Lasst Update by : Eric Kim
// Update date  : 2008-08-07
// Description : 캐릭터의부수적인정보지우기
// [PARAMETER] : 
//	@CharacterGuid : character guid to delete
//  @RemoveAllData :
//		= 0 : DB에서Character정보를삭제하지않고, 삭제표시만하는경우
//		= 100 : DB에서Character 관련정보모두지우고자할때
// [RETURN] : 
// [REMARK]
// 이훈: 캐릭터삭제시받은메일중아이템있는메일은반송처리하도록수정
// 이훈: 아이템 바인드 정보 삭제
// 이훈: 캐릭터 카드 삭제 추가
// 이훈: 캐릭터 포탈 삭제 추가

////////////////////////////////////////////////////////////////////////
*/
set ANSI_NULLS ON
set QUOTED_IDENTIFIER ON
go


/*
////////////////////////////////////////////////////////////////////////
// Lasst Update by : Eric Kim
// Update date  : 2008-08-07
// Description : 캐릭터의부수적인정보지우기
// [PARAMETER] : 
//	@CharacterGuid : character guid to delete
//  @RemoveAllData :
//		= 0 : DB에서Character정보를삭제하지않고, 삭제표시만하는경우
//		= 100 : DB에서Character 관련정보모두지우고자할때
// [RETURN] : 
// [REMARK]
// 이훈: 캐릭터삭제시받은메일중아이템있는메일은반송처리하도록수정
// 이훈: 캐릭터 카드 삭제 추가
// 이훈: 캐릭터 포탈 삭제 추가
// 이훈: 예전 마켓 정보 테이블에서 데이터 지우는것 수정
// 2009-03-26 : Eric Kim, 없어진 TB_UserMailIndex 테이블 삭제
// 2009-08-21 : YonMy, Pet의 아이템 정보도 삭제하게 수정

////////////////////////////////////////////////////////////////////////
*/
CREATE PROCEDURE [dbo].[up_DeleteUserCharacterSub]
	@CharacterID uniqueidentifier,
	@RemoveAllData tinyint
AS
SET NOCOUNT ON
SET XACT_ABORT ON

BEGIN TRAN

	-- 자신에게전송된메일의유지시간을모두종료시킨다.
	-- 반송/삭제시킬수있도록이처리는실제데이터가삭제되든안되든동작해야함
	UPDATE [dbo].[tb_UserMail] SET LIMITTIME = GETDATE() WHERE toguid = @CharacterID

	IF @RemoveAllData = 100
	BEGIN
		-- 아래정보들은Character 정보가진짜로DB에서삭제될때만날린다.
		DELETE FROM [dbo].[TB_UserCharacter_Point] WHERE [CharacterID] = @CharacterID
		DELETE FROM [dbo].[TB_UserCharacter_Extern] WHERE [CharacterID] = @CharacterID
	
		DELETE FROM [dbo].[TB_UserItem_Enchant]
			WHERE [ItemGuid] IN
			(SELECT ItemGuid FROM [dbo].[TB_UserItem] WHERE [OwnerGUID] = @CharacterID)

		DELETE FROM [dbo].[TB_ExpCard] 
			WHERE [ItemGuid] IN
			(SELECT ItemGuid FROM [dbo].[TB_UserItem] WHERE [OwnerGUID] = @CharacterID)
			
		DELETE FROM [dbo].[TB_UserItem]
			WHERE [OwnerGUID] IN
			(SELECT PetID FROM [dbo].[TB_Pet] A INNER JOIN [dbo].[TB_UserItem] B ON A.[PetID] = B.[OwnerGUID] WHERE B.[OwnerGUID] = @CharacterID)
				
		DELETE FROM [dbo].[TB_Pet] 
			WHERE [PetID] IN
			(SELECT ItemGuid FROM [dbo].[TB_UserItem] WHERE [OwnerGUID] = @CharacterID)

		DELETE FROM [dbo].[TB_UserItem] WHERE [OwnerGUID] = @CharacterID

		DELETE FROM [dbo].[TB_Mission_Rank] WHERE [CharacterID] = @CharacterID

	-- 다른사람이보낸메일중에첨부물이있으면반송처리시킨다.
		declare @curdate datetime
		set @curdate = dateadd(day,3,getdate())

		insert into dbo.tb_usermail 
		SELECT	newid() as [mailguid],[FromGuid]
		,[FromGuid],[Title],[Note],[PaymentType],[ItemGuid],[Money],[SendTime],@curdate
		,0 as [ReadBit],1 as [ReturnBit],[AnnexBit],0 as [PaymentBit], [FromName]
		FROM [dbo].[TB_UserMail]
		WHERE 
		toguid = @CharacterID and annexbit = 0 and 
		(itemguid <> '00000000-0000-0000-0000-000000000000' or money <> 0) and ReturnBit = 0

		DELETE FROM [dbo].[TB_UserMail] WHERE [ToGuid] = @CharacterID
		DELETE FROM [dbo].[TB_UserMail] WHERE [FromGuid] = @CharacterID

		DELETE FROM [dbo].[TB_UserAchievements] WHERE [CharGuId] = @CharacterID
		DELETE FROM [dbo].[TB_UserCash_Rank] WHERE [CharGuId] = @CharacterID
		DELETE FROM [dbo].[TB_UserCashGift] WHERE [CharGuId] = @CharacterID
		DELETE FROM [dbo].[TB_UserDealings] WHERE [CharacterGuid] = @CharacterID
		DELETE FROM [dbo].[TB_UserMarket] WHERE [SellerGuid] = @CharacterID
		DELETE FROM [dbo].[TB_UserMarketInfo2] WHERE [CharGuId] = @CharacterID
		DELETE FROM [dbo].[TB_UserCouple] WHERE [CharacterGuid] = @CharacterID
		DELETE FROM [dbo].[TB_UserItem_UnbindDate] WHERE [CharacterGuid] = @CharacterID
		DELETE FROM [dbo].[TB_UserCharacter_Card] WHERE [CharacterGuid] = @CharacterID
		DELETE FROM [dbo].[TB_UserPortal] WHERE [CharacterGuid] = @CharacterID
		
		IF EXISTS(SELECT 1 FROM [dbo].[TB_UserJobSkill_Expertness] WHERE [f_CharGuid] = @CharacterID)
		BEGIN
			DELETE FROM [dbo].[TB_UserJobSkill_Expertness] WHERE [f_CharGuid] = @CharacterID
		END
		
	END

	DELETE FROM [dbo].[TB_Guild_Member] WHERE [CharacterGUID] = @CharacterID
	
	DELETE FROM [dbo].[TB_UserFriend] WHERE [OwnerMemberGuid] = @CharacterID OR [FriendMemberGuid] = @CharacterID
	IF EXISTS(SELECT 1 FROM [dbo].[TB_UserJobSkill_Exhaustion] WHERE [f_CharGuid] = @CharacterID)
	BEGIN
		DELETE FROM [dbo].[TB_UserJobSkill_Exhaustion] WHERE [f_CharGuid] = @CharacterID
	END
Commit Tran
















