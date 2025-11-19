USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_BattleSquare_Mode]    Script Date: 09/08/2009 20:32:16 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefBattleSquare_Mode]') AND [type] = N'U')
BEGIN
	DROP TABLE [dbo].[TB_DefBattleSquare_Mode]
END
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefBattleSquare_ItemPoint]') AND [type] = N'U')
BEGIN
	DROP TABLE [dbo].[TB_DefBattleSquare_ItemPoint]
END
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_BattleSquare_Game]') AND [type] = N'U')
BEGIN
	DROP TABLE [dbo].[TB_BattleSquare_Game]
END
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_BattleSquare_MonRegen]') AND [type] = N'U')
BEGIN
	DROP TABLE [dbo].[TB_BattleSquare_MonRegen]
END
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_BattleSquare_Reward]') AND [type] = N'U')
BEGIN
	DROP TABLE [dbo].[TB_BattleSquare_Reward]
END
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.[UP_LoadDefBattleSquare_ItemPoint]') AND type in (N'P'))
BEGIN
	DROP PROCEDURE dbo.[UP_LoadDefBattleSquare_ItemPoint]
END
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.[UP_LoadDefBattleSquare_Mode]') AND type in (N'P'))
BEGIN
	DROP PROCEDURE dbo.[UP_LoadDefBattleSquare_Mode]
END

/*
	2010-02-07 Eric Kim, Battlesquare renewal
		Table rename
*/
USE [DR2_Def]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefBattleSquare_Game]') AND type in (N'U'))
	DROP TABLE [dbo].[TB_DefBattleSquare_Game]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefBattleSquare_Item]') AND type in (N'U'))
	DROP TABLE [dbo].[TB_DefBattleSquare_Item]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefBattleSquare_PrivateLevelReward]') AND type in (N'U'))
	DROP TABLE [dbo].[TB_DefBattleSquare_PrivateLevelReward]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefBattleSquare_PrivateReward]') AND type in (N'U'))
	DROP TABLE [dbo].[TB_DefBattleSquare_PrivateReward]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefBattleSquare_WinBonusReward]') AND type in (N'U'))
	DROP TABLE [dbo].[TB_DefBattleSquare_WinBonusReward]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefBattleSquare_WinTeamReward]') AND type in (N'U'))
	DROP TABLE [dbo].[TB_DefBattleSquare_WinTeamReward]
GO

