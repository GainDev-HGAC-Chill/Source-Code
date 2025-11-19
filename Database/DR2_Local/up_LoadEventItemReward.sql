USE [DR2_Local]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadEventItemReward]    Script Date: 11/04/2009 16:32:19 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadEventItemReward]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadEventItemReward]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_LoadEventItemReward]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT 
	[EventItemNo]
	,[ResultItemNo]
	,[ResultItemCount]
	,[TimeType]
	,[UseTime]
	,[Rarity]
	,[EnchantType]
	,[EnchantLevel]
	,[Rate]
	,[Broadcast]
	FROM [dbo].[TB_EventItemReward]

END
