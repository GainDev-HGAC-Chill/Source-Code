IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Change_Character_Skill2]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_Change_Character_Skill2]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Change_Character_Skill]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_Change_Character_Skill]
GO

/****** Object:  StoredProcedure [dbo].[up_Change_Character_Skill]    Script Date: 07/09/2009 11:36:51 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_Change_Character_Skill]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : [up_Update_UserSkill]
// 작 성 자 : 최연승
// 작 성 일 : 2008-07-28
// 최종수정자 : Eric Kim
// 수 정 일 : 2008-10-07
// 파 일 명 :
// N O T E : OrderDB로 들어온 스킬 수정 관련 처리 SP 기존 up_Web_Admin_SkillUser_Update과 동일
//	2008-10-07 : Table 이름 변경 적용
//
////////////////////////////////////////////////////////////////////////
*/
	@ProcMethod	 nvarchar(100) = null,
	@SkillNoText nvarchar(1000) = null,
	@MemberID uniqueidentifier,
	@CharacterID uniqueidentifier,
	@SkillPoint	 smallint
AS
BEGIN

	SET NOCOUNT ON;

	DECLARE @SQL nvarchar(4000)		
	DECLARE @SQL_Params nvarchar(1000)	

	DECLARE @SkillBinary binary(450)
	DECLARE @SkillText varchar(450)
	DECLARE @TempSkillNo varchar(15)

	-- ':' 문자로 Split한다.
	DECLARE @CURRENT_SkillNo INT
	DECLARE @I INT
	DECLARE @CHECKED_COUNT INT
	
	DECLARE @Err int

	SET @Err = 0


	/*If @ProcMethod = 'ALLSKILL' --모든 최고 스킬
	BEGIN

		DECLARE @TempTable TABLE (SkillNo int, SkillNoBinary binary(4), SkillNoText varchar(15))
		
		INSERT @TempTable (SkillNo, SkillNoBinary)
		SELECT MAX(skillno), CONVERT(binary(4), MAX(skillno))  FROM [DR2_Def].[dbo].[TB_DefSkill]
			GROUP BY ParentSkill,  [DR2_Def].[dbo].udf_getStrName(NameNo)

		UPDATE @TempTable SET
			SkillNoText = SUBSTRING(SUBSTRING(sys.fn_varbinTohexstr(SkillNoBinary), 3, len(sys.fn_varbinTohexstr(SkillNoBinary))),7,2) + SUBSTRING(SUBSTRING(sys.fn_varbinTohexstr(SkillNoBinary), 3, len(sys.fn_varbinTohexstr(SkillNoBinary))),5,2) + SUBSTRING(SUBSTRING(sys.fn_varbinTohexstr(SkillNoBinary), 3, len(sys.fn_varbinTohexstr(SkillNoBinary))),3,2) + SUBSTRING(SUBSTRING(sys.fn_varbinTohexstr(SkillNoBinary), 3, len(sys.fn_varbinTohexstr(SkillNoBinary))),1,2) 

		-- 임시 테이블에 바이너리 업데이트 에러
		IF @@error <> 0
		BEGIN
			SET @Err = 1;
			GOTO ErrorHandler;
		END

		SET @SkillText = ''
		SET @TempSkillNo = 0
		SET @I = 0
		
		WHILE @I < (SELECT COUNT(*) FROM @TempTable)
		BEGIN
			SET @TempSkillNo = (SELECT TOP 1 SkillNo FROM @TempTable WHERE SkillNo > @TempSkillNo ORDER BY SkillNo ASC)
			SET @SkillText = @SkillText + (SELECT SkillNoText FROM @TempTable WHERE SkillNo = @TempSkillNo)

			SET @I = @I + 1

			If @I > 70
			BEGIN
				BREAK
			END
		END 

		SET @SQL = ' SET @SkillBinary = 0x' + @SkillText + ' '
		SET @SQL_Params = ' @SkillBinary Binary(450) OUTPUT '

		EXEC sp_executesql @SQL, @SQL_Params, @SkillBinary OUTPUT
		
		UPDATE TB_CharacterSub SET
			Skills = @SkillBinary
		WHERE CharacterID = @CharacterID

		--실테이블에 업데이트 에러
		IF @@error <> 0
		BEGIN
			SET @Err = 2;
			GOTO ErrorHandler;
		END

	END*/

	If @ProcMethod = 'SELSKILL' --선택 스킬 저장
	BEGIN	

		SET @I = 0	
		SET @SkillText = ''	
		
		SET @CHECKED_COUNT = LEN(@SkillNoText) - LEN(REPLACE(@SkillNoText,':',''))
		
		WHILE @I < @CHECKED_COUNT
		BEGIN
		
			SET @CURRENT_SkillNo = SUBSTRING(@SkillNoText, 1, CHARINDEX(':', @SkillNoText)-1)
			SET @SkillNoText = STUFF(@SkillNoText, 1, CHARINDEX(':', @SkillNoText), '')	

			SET @TempSkillNo = sys.fn_varbinTohexstr(CONVERT(Binary(4), @CURRENT_SkillNo))
			SET @TempSkillNo = SUBSTRING(@TempSkillNo, 3, len(@TempSkillNo))--0x를 떼낸 스트링

			SET @SkillText = @SkillText + SUBSTRING(@TempSkillNo,7,2) + SUBSTRING(@TempSkillNo,5,2) + SUBSTRING(@TempSkillNo,3,2) + SUBSTRING(@TempSkillNo,1,2)
			
			SET @I = @I + 1
		END

		SET @SQL = ' SET @SkillBinary = 0x' + @SkillText + ' '
		SET @SQL_Params = ' @SkillBinary Binary(450) OUTPUT '

		EXEC sp_executesql @SQL, @SQL_Params, @SkillBinary OUTPUT

		if @SkillPoint > 0
		begin
			UPDATE [dbo].[TB_CharacterSub] SET
				Skills = @SkillBinary,
				ExtraSkillPoint = @SkillPoint			
			WHERE CharacterID = @CharacterID
		end else
		begin
			UPDATE [dbo].[TB_CharacterSub] SET
				Skills = @SkillBinary	
			WHERE CharacterID = @CharacterID
		end
		

		-- 실테이블 업데이트 에러
		IF @@error <> 0
		BEGIN
			SET @Err = 3;
			GOTO ErrorHandler;
		END
	END

ErrorHandler:
	select @Err
--	RETURN @Err
END


GO