USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_ExpCard_Delete]    Script Date: 07/07/2009 18:18:06 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_ExpCard_Delete]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_ExpCad_Delete]

USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_ExpCard_Delete]    Script Date: 07/07/2009 18:18:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_ExpCard_Delete]
@ItemGuid UNIQUEIDENTIFIER
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	DELETE FROM dbo.tb_ExpCard WHERE ItemGuid = @ItemGuid

END
