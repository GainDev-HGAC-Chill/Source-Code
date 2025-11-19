USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_Update_TB_UserCharacter_RecentChannelState]    Script Date: 05/26/2011 23:37:16 ******/

IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Update_TB_UserCharacter_RecentChannelState]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Update_TB_UserCharacter_RecentChannelState]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_Update_TB_UserCharacter_RecentChannelState] 
	@CharacterID uniqueidentifier,
	@State smallint
AS
SET NOCOUNT ON
SET XACT_ABORT ON	

BEGIN
	UPDATE	[dbo].[TB_CharacterSub]
	SET		[f_RecentChannelState] = @State
	WHERE	[CharacterID] = @CharacterID
END