USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_Item_Modify]    Script Date: 01/12/2010 20:18:17 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Item_Modify]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Item_Modify]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_Item_Modify]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : 아이템 프로세스
// 작 성 자 : Richard Kim(tigerjune@barunsoninter.com)
// 작 성 일 : 2007-11-23
// 최종수정자 : 이훈
// 수 정 일 : 2008-11-07
// 파 일 명 : 
// N O T E : 
//
////////////////////////////////////////////////////////////////////////
*/ 
	@ItemGuid	uniqueidentifier=null,
	@OwnerGuid	uniqueidentifier = null,
	@InvType tinyint = null,
	@InvPos tinyint = null,
	@ItemNo int = null,
	@Count smallint = null,
	@Enchant1 bigint = null,
	@Enchant2 bigint = null,
	@Enchant3 bigint = null,
	@Enchant4 bigint = null,
	@State tinyint = NULL,
	@GenDate DATETIME = NULL
as
Set Nocount on
Set Xact_Abort ON

DECLARE @Tries tinyint
SET @Tries = 1

WHILE @Tries <= 3
BEGIN
	BEGIN TRAN
	BEGIN TRY
		
		UPDATE dbo.TB_UserItem SET [OwnerGuid]=@OwnerGuid	, [InvType]=@InvType, [InvPos]=@InvPos, 
		[ItemNo]=@ItemNo, [Count]=@Count, [State]=@State, [CreateDate]=@GenDate
		Where ItemGuid = @ItemGuid
		
		IF ISNULL(@Enchant1, 0) <> 0 OR ISNULL(@Enchant2, 0) <> 0 OR ISNULL(@Enchant3, 0) <> 0 OR ISNULL(@Enchant4, 0) <> 0
		BEGIN

			if exists(select 1 from dbo.[TB_UserItem_Enchant] where ItemGuid = @ItemGuid)
			begin
				UPDATE dbo.[TB_UserItem_Enchant] SET [Enchant_01]=ISNULL(@Enchant1, 0), [Enchant_02]=ISNULL(@Enchant2, 0),
				[Enchant_03]=ISNULL(@Enchant3, 0),[Enchant_04]=ISNULL(@Enchant4, 0) Where ItemGuid = @ItemGuid
			end
			else
			begin
				INSERT INTO [dbo].[TB_UserItem_Enchant]([ItemGuid],[Enchant_01],[Enchant_02],[Enchant_03],[Enchant_04])
				 VALUES (@ItemGuid,ISNULL(@Enchant1, 0),ISNULL(@Enchant2, 0),ISNULL(@Enchant3, 0),ISNULL(@Enchant4, 0))
			end

		END
		ELSE
		BEGIN
			if exists(select 1 from dbo.[TB_UserItem_Enchant] where ItemGuid = @ItemGuid)
			BEGIN
				DELETE FROM dbo.[TB_UserItem_Enchant] where ItemGuid = @ItemGuid
			END
		END

		COMMIT
		SELECT 0
		RETURN
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN		
		SET @Tries = @Tries + 1

		-->> 데드락 발생 로그 기록 차후 데드락 문제가 해결되면 지워 주자
		insert into dbo.tb_deadlocklog (spname,errorcode,spincount, deadlockdate) 
		values('up_Item_Modify', ERROR_NUMBER(), @Tries, getdate())
		--<< 데드락 발생 로그 기록 차후 데드락 문제가 해결되면 지워 주자

		CONTINUE
	END CATCH;

	SELECT 1
END
