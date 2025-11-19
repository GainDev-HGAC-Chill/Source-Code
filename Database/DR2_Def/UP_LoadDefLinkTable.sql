IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_LoadDefLinkTable]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[UP_LoadDefLinkTable]
GO

/****** Object:  StoredProcedure [dbo].[UP_LoadDefLinkTable]    Script Date: 07/09/2009 11:25:27 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[UP_LoadDefLinkTable]

AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

SELECT [LinkNo]
      ,[LinkType]
      ,[LinkValue]
      ,[Memo]
  FROM [dbo].[TB_DefLinkTable]

END

GO