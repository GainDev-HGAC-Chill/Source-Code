USE [DR2_Def]
GO

SET ANSI_NULLS ON
SET QUOTED_IDENTIFIER ON

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefItemSocket]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefItemSocket]
END
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefItemSocket]
AS
BEGIN
	SET NOCOUNT ON;
	
	SELECT [EquipPos], [LevelLimit], [Socket_Order], [SuccessRate], [SoulItemCount], [NeedMoney], [SocketItemNo], [RestorationItemNo], [ResetItemNo]
	FROM [dbo].[TB_DefItemSocket]
END

GO
