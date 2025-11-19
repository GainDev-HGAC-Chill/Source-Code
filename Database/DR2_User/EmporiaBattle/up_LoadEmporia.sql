USE [DR2_User]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadEmporia]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadEmporia]
GO

CREATE PROCEDURE [dbo].[up_LoadEmporia]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : 길드 엠포리아 불러오기(서버On시에 한번 사용)
// 작 성 자 : YonMy
// 작 성 일 : 2009-06-10
// 최종수정자 : 
// 수 정 일 : 
// 담 당 자 : YonMy
// N O T E : 
// 2009-06-29, YonMy 엠포리아 기능 정보 로드하게 추가
////////////////////////////////////////////////////////////////////////
*/
AS
SET XACT_ABORT ON
SET NOCOUNT ON

SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED

BEGIN
DECLARE @Err int

SET @Err = 0

	-- 1. TB_EmporiaPack Select
	SELECT	[EmporiaID]
		,	[State]
		,	[BattlePeriodsForWeeks]
		,	[BattleID]
		,	[BattleDate]
		,	[PrevBattleID]
	FROM	[dbo].[TB_EmporiaPack]
	
	-- 2. TB_EMPORIA
	SELECT	TB_EMPORIA.[EmporiaID]
		,	TB_EMPORIA.[Grade]
		,	TB_EMPORIA.[State]
		,	TB_EMPORIA.[OwnerGuildID]
		,	TB_EMPORIA.[HaveDate]
		,	TB_GUILD.[GuildName]
		,	TB_GUILD.[Emblem]
	FROM(	
			[dbo].[TB_Emporia] AS TB_EMPORIA
			LEFT OUTER JOIN
			[dbo].[TB_Guild_Basic_Info] AS TB_GUILD
		ON
			TB_EMPORIA.[OwnerGuildID] = TB_GUILD.[GuildGuid]
		) 
		
	-- 3. TB_Emporia_Function
	SELECT	[EmporiaID]
		,	[Grade]
		,	[FunctionNo]
		,	[HaveDate]
		,	[ExpirationDate]
		,	[ExtValue]
	FROM	[dbo].[TB_Emporia_Function]
	
	-- 4. Emporia Battle Select
	SELECT	TB_BATTLE.[EmporiaID]
		,	TB_BATTLE.[BattleID]
		,	TB_BATTLE.[GuildID]
		,	TB_BATTLE.[Exp]
		,	TB_BATTLE.[RegistDate]--5
		,	TB_GUILD.[GuildName]
		,	TB_GUILD.[Emblem]
		,	TB_BATTLE.[State]
	FROM (	
			[dbo].[TB_Emporia_ChallengeBattle] AS TB_BATTLE
			INNER JOIN
			[dbo].[TB_EmporiaPack] AS TB_PACK
		ON
			TB_BATTLE.[EmporiaID] = TB_PACK.[EmporiaID]
			AND	(	TB_BATTLE.[BattleID] = TB_PACK.[BattleID] 
				OR	TB_BATTLE.[BattleID] = TB_PACK.[PrevBattleID] 
				)
				
			INNER JOIN
			[dbo].[TB_Guild_Basic_Info] AS TB_GUILD
		ON
			TB_BATTLE.[GuildID] = TB_GUILD.[GuildGuid]
		) 

	-- 5. TB_Emporia_Tournament
	SELECT	TB_TOURNAMENT.[EmporiaID]
		,	TB_TOURNAMENT.[BattleID]
		,	TB_TOURNAMENT.[Index]
		,	TB_TOURNAMENT.[BattleDate]
		,	TB_TOURNAMENT.[WinGuildID]
		,	TB_TOURNAMENT.[LoseGuildID]
	FROM (
			[dbo].[TB_Emporia_Tournament] AS TB_TOURNAMENT
			INNER JOIN
			[dbo].[TB_EmporiaPack] AS TB_PACK
		ON
				TB_TOURNAMENT.[EmporiaID] = TB_PACK.[EmporiaID]
			AND	(	TB_TOURNAMENT.[BattleID] = TB_PACK.[BattleID] 
				OR	TB_TOURNAMENT.[BattleID] = TB_PACK.[PrevBattleID] 
				)
		)

	-- 6. TB_Emporia_Mercenary
	SELECT	TB_MERCENARY.[EmporiaID]
      ,		TB_MERCENARY.[BattleID]
      ,		TB_MERCENARY.[Index]
      ,		TB_MERCENARY.[JoinGuidID]
      ,		TB_MERCENARY.[CharacterGuid]
	FROM (
			[dbo].[TB_Emporia_Mercenary] AS TB_MERCENARY
			INNER JOIN
			[dbo].[TB_EmporiaPack] AS TB_PACK
		ON
				TB_MERCENARY.[EmporiaID] = TB_PACK.[EmporiaID]
			AND	TB_MERCENARY.[BattleID] = TB_PACK.[BattleID]
		)

	RETURN @Err
END	
GO