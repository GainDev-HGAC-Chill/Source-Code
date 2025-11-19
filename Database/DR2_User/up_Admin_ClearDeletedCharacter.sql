IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Admin_ClearDeletedCharacter]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_Admin_ClearDeletedCharacter]
GO

/****** Object:  StoredProcedure [dbo].[up_Admin_ClearDeletedCharacter]    Script Date: 07/09/2009 11:30:39 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE Proc [dbo].[up_Admin_ClearDeletedCharacter]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : [dbo].[up_Admin_ClearDeletedCharacter]
// 작 성 자 : Eric Kim
// 작 성 일 : 2006-11-25
// 파 일 명 : 
// N O T E :  지우진것으로 표시된 Character를 DB에서 삭제
// RETURN : Error code
//
////////////////////////////////////////////////////////////////////////
*/
(
	@Confirm nvarchar(10)	-- 실수를 방지하기 위한 확인 메시지 입력
)
AS
SET NOCOUNT ON
begin
DECLARE @Err int
DECLARE @CharacterGuid uniqueidentifier
Set @Err = 0

	IF @Confirm  <> 'ImSure'
	BEGIN
		print('This procedure will delete ALL MEMBER and CHARACTER')
		print('If you are convinced that you know well what you will do and you are sure')
		print('EXEC UP_ClearAllMember ImSure')
		return
	END

-- Transaction 을 시작할 필요가 없다.
-- Character Table 에는 있는데 Member Table에 없는 Character 정보 얻기
DECLARE DelCursor1 CURSOR FOR
	SELECT CharacterID FROM [dbo].[TB_CharacterBasic] WHERE [State] = 1

OPEN DelCursor1;
FETCH NEXT FROM DelCursor1 INTO @CharacterGuid
WHILE (@@FETCH_STATUS = 0)
BEGIN
	EXEC [dbo].[up_DeleteUserCharacter] @CharacterGuid, 1, N'', 1
	FETCH NEXT FROM DelCursor1 INTO @CharacterGuid
END
CLOSE DelCursor1;
DEALLOCATE DelCursor1;


RETURN @ERR
end


GO