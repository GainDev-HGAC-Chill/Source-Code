USE [DR2_SiteConfig]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Add_DefIPForAccept]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Add_DefIPForAccept]
GO

CREATE PROCEDURE [dbo].[up_Add_DefIPForAccept]
@StartIP nvarchar(20),
@EndIP nvarchar(20),
@NationKey nvarchar(50),
@NationName nvarchar(50),
@ExpireDate datetime
AS
BEGIN

	INSERT INTO [dbo].[TB_IP_ForAccept]
			   ( [StartIP]
			   ,[EndIP]
			   ,[NationKey]
			   ,[NationName]
			   ,[ExpireDate] )
		 VALUES
			   (@StartIP, @EndIP, @NationKey, @NationName, @ExpireDate)
END