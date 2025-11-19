USE DR2_Def

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefBaseCharacter2]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefBaseCharacter2]
END 

set ANSI_NULLS ON
set QUOTED_IDENTIFIER ON
go


create Proc [dbo].[up_LoadDefBaseCharacter2]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명: [dbo].[up_LoadDefBaseCharacter]
// 작성자: 
// 작성일: 
// 파일명: 
// N O T E :  베이스캐릭터정보를로드한다.
//	2008-12-09 : 육정범종료퀘스트저장공간늘림
//	2009-03-12 : 이훈gmlv 삭제
//	2009-03-12 : 인밴토리확장/축소정보추가
////////////////////////////////////////////////////////////////////////
*/ 
AS

begin
	SELECT 
		f_NationCodeStr,
		f_Class,			
		f_State,
		f_Race,
		f_Lv,
		f_Exp,					--5
		f_Money,
		f_HP,
		f_MP,
		f_CP,
		f_ExtraSkillPoint,		--10
		f_Skills,
		f_RecentMap,
		f_RecentLocX,
		f_RecentLocY,
		f_RecentLocZ,			--15
		f_LastVillage,
		f_LastVillageLocX,
		f_LastVillageLocY,
		f_LastVillageLocZ,
		f_QuickSlot,			--20
		f_IngQuest,
		f_EndQuest,
		f_EndQuest2,
		f_EndQuestExt,
		f_EndQuestExt2,			--25
		f_InvExtend
		FROM [dbo].[TB_DefBaseCharacter2] with(nolock)
end

GO
