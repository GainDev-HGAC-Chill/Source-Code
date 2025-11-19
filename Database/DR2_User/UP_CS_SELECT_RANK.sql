USE [DR2_User]
IF EXISTS(SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'UP_CS_SELECT_RANK'))
BEGIN
	DROP PROCEDURE [dbo].[UP_CS_SELECT_RANK]
END
GO

/****** Object:  StoredProcedure [dbo].[UP_CS_SELECT_RANK]    Script Date: 03/31/2009 14:04:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[UP_CS_SELECT_RANK]

AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT TOP 10 B.Name,A.USEDCASH FROM DBO.TB_USERCASH_RANK AS A
	INNER JOIN DBO.TB_CharacterBasic AS B ON B.CharacterID = A.CharGuId
	WHERE ISVISABLE = 1
	ORDER BY USEDCASH DESC

END

GO