USE DR2_Member
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.[UP_BS_Load_Game]') AND type in (N'P'))
BEGIN
	DROP PROCEDURE dbo.[UP_BS_Load_Game]
END

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_BattleSquare_Game]') AND type in (N'U'))
BEGIN
	DROP TABLE [dbo].[TB_BattleSquare_Game]
END

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_BattleSquare_MonRegen]') AND type in (N'U'))
BEGIN
	DROP TABLE [dbo].[TB_BattleSquare_MonRegen]
END

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_BattleSquare_Reward]') AND type in (N'U'))
BEGIN
	DROP TABLE [dbo].[TB_BattleSquare_Reward]
END
GO
