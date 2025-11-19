USE DR2_USER
GO
/****** 개체:  StoredProcedure [dbo].[up_Item_Create]    스크립트 날짜: 07/17/2009 11:24:27 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Item_Create]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Item_Create]
GO

/****** 개체:  StoredProcedure [dbo].[up_Item_Create]    스크립트 날짜: 07/17/2009 11:24:27 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Item_Create]') AND type in (N'P', N'PC'))
BEGIN
EXEC dbo.sp_executesql @statement = N'CREATE PROCEDURE [dbo].[up_Item_Create]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : 아이템 프로세스
// 작 성 자 : 이훈
// 작 성 일 : 2008-10-20
// 최종수정자 : 이훈
// 수 정 일 : 2008-12-05
// 수정자 : 이훈 
// 아이템 수정 동작이 update 쿼리에서 delete + create 동작으로 바뀌면서 아이템 생성
// 시간이 매번 새로 갱신되어 기간제 아이템이 정상 동작 하지 않았음
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
	@State tinyint = null,
	@GenDate datetime = null
as
Set Nocount on
Set Xact_Abort On

BEGIN TRAN

	insert dbo.TB_UserItem	([ItemGuid],	[OwnerGuid]	,	[InvType]	,	[InvPos]	,	[ItemNo]	,	[Count]	,	[State]	,	[CreateDate]		)
	values	(@ItemGuid,	@OwnerGuid,	@InvType,	@InvPos,	@ItemNo,	@Count,	@State,	isnull(@GenDate,GetDate())	)

	IF @@ERROR <> 0
	BEGIN
		GOTO __ERROR
	END

	IF ISNULL(@Enchant1, 0) <> 0 OR ISNULL(@Enchant2, 0) <> 0 OR ISNULL(@Enchant3, 0) <> 0 OR ISNULL(@Enchant4, 0) <> 0
	BEGIN
		INSERT INTO [dbo].[TB_UserItem_Enchant]
				   ([ItemGuid]
				   ,[Enchant_01]
				   ,[Enchant_02]
				   ,[Enchant_03]
				   ,[Enchant_04])
			 VALUES
				   (@ItemGuid
				   ,ISNULL(@Enchant1, 0)
				   ,ISNULL(@Enchant2, 0)
				   ,ISNULL(@Enchant3, 0)
				   ,ISNULL(@Enchant4, 0))

		IF @@ERROR <> 0
		BEGIN
			GOTO __ERROR
		END
	END

COMMIT TRAN

	SELECT 0
	RETURN

__ERROR:

ROLLBACK TRAN

	SELECT 1

'
END
GO
