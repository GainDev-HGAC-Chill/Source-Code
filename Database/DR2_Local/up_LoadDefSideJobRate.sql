USE [DR2_Local]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadDefSideJobRate]    Script Date: 12/10/2009 16:54:15 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefSideJobRate]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefSideJobRate]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_LoadDefSideJobRate]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [SideJob]
		  ,[CostRate]
		  ,[SoulRate]
		  ,[SuccessRate]
		  ,[PayRate]
	  FROM [dbo].[TB_DefSideJobRate]

END
