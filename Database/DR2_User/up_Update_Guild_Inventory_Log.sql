USE [DR2_User]
GO

IF EXISTS( SELECT * FROM sys.objects WHERE [object_id] = OBJECT_ID(N'[dbo].[up_Update_Guild_Inventory_Log]') AND  [type] in ('P') )
BEGIN
	DROP PROCEDURE [dbo].[up_Update_Guild_Inventory_Log]
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

/*
////////////////////////////////////////////////////////////////////////
// Lasst Update by : 김동환
// Update date  : 2010-06-09
// Description : 길드금고 로그
// [PARAMETER] : 
// [RETURN] : 
// [REMARK]
////////////////////////////////////////////////////////////////////////
*/
CREATE PROCEDURE [dbo].[up_Update_Guild_Inventory_Log]
(	
	@GuildGuid uniqueidentifier,
	@ItemGuid uniqueidentifier,
	@Time DATETIME,
	@CharName nvarchar(20),
	@Type TINYINT,
	@ItemNo INT,
	@Count BIGINT
)
AS
SET NOCOUNT ON;

INSERT INTO dbo.TB_Guild_Inventory_Log
(
	[GuildGuid], [ItemGuid], [Date], [CharacterName], [Type], [ItemNo], [Count] 
)
VALUES
(
	@GuildGuid, @ItemGuid, @Time, @CharName, @Type, @ItemNo, @Count 
)


