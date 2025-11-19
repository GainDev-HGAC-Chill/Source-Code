USE [DR2_local]
GO
/****** Object:  StoredProcedure [dbo].[UP_Load_LimitedItemControl]    Script Date: 05/21/2009 14:58:00 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_Load_LimitedItemControl]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[UP_Load_LimitedItemControl]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[UP_Load_LimitedItemControl]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [ObjectType]
		  ,[ObjectNo]
		  ,[EventNo]
		  ,[Rate]
	  FROM [dbo].[TB_LimitedItemControl]

END
