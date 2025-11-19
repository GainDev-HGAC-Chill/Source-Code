USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_Update_TB_UserCharacter_RecentChannel]    Script Date: 05/26/2011 23:37:16 ******/

IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Update_TB_UserCharacter_RecentChannel]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Update_TB_UserCharacter_RecentChannel]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_Update_TB_UserCharacter_RecentChannel] 
	@CharacterID uniqueidentifier,
	@ValueChannel smallint,
	@ValueNo int,
	@ValueX float,
	@ValueY float,
	@ValueZ float
AS
SET NOCOUNT ON
SET XACT_ABORT ON	

BEGIN
	UPDATE	[dbo].[TB_CharacterSub]
	SET		[f_RecentChannel] = @ValueChannel
	,		[f_RecentChannelMap] = @ValueNo
	,		[f_RecentChannelLocX] = @ValueX
	,		[f_RecentChannelLocY] = @ValueY
	,		[f_RecentChannelLocZ] = @ValueZ
	WHERE	[CharacterID] = @CharacterID
END