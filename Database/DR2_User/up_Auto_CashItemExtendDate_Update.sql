USE DR2_USER
GO
/****** 개체:  StoredProcedure [dbo].[up_Auto_CashItemExtendDate_Update]    스크립트 날짜: 07/17/2009 11:24:24 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Auto_CashItemExtendDate_Update]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Auto_CashItemExtendDate_Update]
GO

/****** 개체:  StoredProcedure [dbo].[up_Auto_CashItemExtendDate_Update]    스크립트 날짜: 07/17/2009 11:24:24 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Auto_CashItemExtendDate_Update]') AND type in (N'P', N'PC'))
BEGIN
EXEC dbo.sp_executesql @statement = N'-- =============================================
-- Author:		김상록
-- Create date: <Create Date,,>
-- Description:	자동 캐시 연장 업데이트
-- =============================================
CREATE PROCEDURE [dbo].[up_Auto_CashItemExtendDate_Update]
	@ChangeTime	int
AS
BEGIN
	SET NOCOUNT ON

	--변경
	UPDATE dbo.TB_UserItem SET
		   CreateDate = ( CASE WHEN GETDATE() < DATEADD(hh, @ChangeTime, CreateDate) THEN
								GETDATE()
						ELSE
							DATEADD(hh, @ChangeTime, CreateDate)
						END )
		   WHERE ItemGuid IN (
					SELECT A.ItemGuid
					FROM dbo.TB_UserItem A LEFT JOIN dbo.TB_UserItem_Enchant B
					ON A.ItemGuid = B.ItemGuid
					WHERE ISNULL(B.Enchant_02, 0) <> 0 --캐시아이템아닌것제외
					AND ''1'' = SUBSTRING(dbo.udf_Web_ConvertRadix(ISNULL(B.Enchant_02, 0), 2), 32,1)  -- 사용시간제한아이템아닌것제외
					AND ''000000000'' <> SUBSTRING(dbo.udf_Web_ConvertRadix(ISNULL(B.Enchant_02, 0), 2), 33, 9) -- 시간값이인것제외
				 )


	
END




' 
END
GO