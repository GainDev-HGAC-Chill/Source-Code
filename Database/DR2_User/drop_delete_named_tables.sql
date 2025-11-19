USE DR2_USER
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[[delete]]up_ChangeChrName]') AND type in (N'P', N'PC'))
DROP PROC [dbo].[[delete]]up_ChangeChrName]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[[delete]]up_SelectedCharacter_MarketDealings]') AND type in (N'P', N'PC'))
DROP PROC dbo.[[delete]]up_SelectedCharacter_MarketDealings]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].DROP PROC dbo.[[delete]]up_SelectedCharacter_MarketDealings]') AND type in (N'P', N'PC'))
DROP PROCEDURE dbo.[[delete]]up_SelectedCharacter_MarketDealings]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[[delete]]up_ChangeChrMap]') AND type in (N'P', N'PC'))
DROP PROC dbo.[[delete]]up_ChangeChrMap]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[[delete]]up_SelectedCharacter_MarketInfo]') AND type in (N'P', N'PC'))
DROP PROC dbo.[[delete]]up_SelectedCharacter_MarketInfo]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[[delete]]up_ChangeChrMap2]') AND type in (N'P', N'PC'))
DROP PROC dbo.[[delete]]up_ChangeChrMap2]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[[delete]]up_SelectedCharacter_MarketArticles]') AND type in (N'P', N'PC'))
DROP PROC dbo.[[delete]]up_SelectedCharacter_MarketArticles]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[[delete]]up_ChangeChrName2]') AND type in (N'P', N'PC'))
DROP PROC dbo.[[delete]]up_ChangeChrName2]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[[delete]]up_CheckName]') AND type in (N'P', N'PC'))
DROP PROC dbo.[[delete]]up_CheckName]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[[delete]]up_ChangeChrInfo2]') AND type in (N'P', N'PC'))
DROP PROC dbo.[[delete]]up_ChangeChrInfo2]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[[delete]]up_SelectedCharacter3]') AND type in (N'P', N'PC'))
DROP PROC dbo.[[delete]]up_SelectedCharacter3]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[[delete]]up_CheckName2]') AND type in (N'P', N'PC'))
DROP PROC dbo.[[delete]]up_CheckName2]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[[delete]]up_ChangeChrInfo]') AND type in (N'P', N'PC'))
DROP PROC dbo.[[delete]]up_ChangeChrInfo]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[[delete]]up_CreateCharacter]') AND type in (N'P', N'PC'))
DROP PROC dbo.[[delete]]up_CreateCharacter]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[[delete]]up_SelectedCharacter_Base]') AND type in (N'P', N'PC'))
DROP PROC dbo.[[delete]]up_SelectedCharacter_Base]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[[delete]]up_SelectedCharacter_Item]') AND type in (N'P', N'PC'))
DROP PROC dbo.[[delete]]up_SelectedCharacter_Item]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[[delete]]up_Post_GetMailItemInfo3_old]') AND type in (N'P', N'PC'))
DROP PROC dbo.[[delete]]up_Post_GetMailItemInfo3_old]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[[delete]]up_SelectedCharacter_Achievements]') AND type in (N'P', N'PC'))
DROP PROC dbo.[[delete]]up_SelectedCharacter_Achievements]
GO
