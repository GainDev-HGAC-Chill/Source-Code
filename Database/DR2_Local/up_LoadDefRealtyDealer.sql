USE [DR2_Local]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadDefRealtyDealer]    Script Date: 07/01/2009 19:07:32 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefRealtyDealer]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefRealtyDealer]
GO

USE [DR2_Local]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadDefRealtyDealer]    Script Date: 07/01/2009 19:07:47 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_LoadDefRealtyDealer]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [NpcGuid]
		  ,[GroundNo]
		  ,[Cost]
	  FROM [dbo].[TB_DefRealtyDealer]

END
GO