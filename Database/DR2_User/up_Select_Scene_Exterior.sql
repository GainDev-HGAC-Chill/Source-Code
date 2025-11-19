USE DR2_USER
GO

/****** 개체:  StoredProcedure [dbo].[up_Select_Scene_Exterior]    스크립트 날짜: 07/17/2009 11:24:28 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Select_Scene_Exterior]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Select_Scene_Exterior]
GO

/****** 개체:  StoredProcedure [dbo].[up_Select_Scene_Exterior]    스크립트 날짜: 07/17/2009 11:24:28 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Select_Scene_Exterior]') AND type in (N'P', N'PC'))
BEGIN
EXEC dbo.sp_executesql @statement = N'
CREATE PROCEDURE [dbo].[up_Select_Scene_Exterior]
	@OpString		VARCHAR(8000) = ''''
AS
SET NOCOUNT ON	
SET XACT_ABORT ON

BEGIN

	--Option Depth 1추가
	DECLARE @I INT
	DECLARE @CHECKED_COUNT INT
	DECLARE @OwnerGuid UNIQUEIDENTIFIER
	
	SET @CHECKED_COUNT = LEN(@OpString) - LEN(REPLACE(@OpString,''|'',''''))	-- 자르는 기호가 몇개나 있는지.
	SET @CHECKED_COUNT  = @CHECKED_COUNT

--	print ''체크포인트'' ------------
--	print @CHECKED_COUNT ------------

	SET @I = 0
	WHILE @I < @CHECKED_COUNT
	BEGIN
		SET @OwnerGuid = SUBSTRING(@OpString, 1, CHARINDEX(''|'', @OpString)-1)
		SET @OpString = STUFF(@OpString, 1, CHARINDEX(''|'', @OpString), '''')
		
--		print @OwnerGuid

--		print ''돈다''

		SELECT A.ItemGuid, A.OwnerGuid, A.InvType, A.InvPos, A.ItemNo, A.Count, B.Enchant_01, B.Enchant_02, B.Enchant_03, B.Enchant_04, A.State, A.CreateDate 
				, ISNULL(B.Enchant_01,0) AS Enchant_01
				, ISNULL(B.Enchant_02,0) AS Enchant_02
				, ISNULL(B.Enchant_03,0) AS Enchant_03
				, ISNULL(B.Enchant_04,0) AS Enchant_04
			FROM TB_UserItem A LEFT JOIN dbo.TB_UserItem_Enchant B
			ON A.ItemGuid = B.ItemGuid
			WHERE OwnerGuid = @OwnerGuid

		SET @I = @I + 1
	END	

--정상종료
--	print ''정상 끝''

END'
END
GO