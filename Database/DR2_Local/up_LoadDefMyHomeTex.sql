USE [DR2_Local]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadDefMyHomeTex]    Script Date: 08/31/2009 18:20:52 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefMyHomeTex]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefMyHomeTex]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_LoadDefMyHomeTex]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	SELECT AuctionLevelLimit,MyHomeTex FROM dbo.TB_DefMyHomeTex
END
