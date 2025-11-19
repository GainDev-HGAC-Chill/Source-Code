USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_ExpCard_Delete]    Script Date: 07/07/2009 18:17:50 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_ExpCard_Delete]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_ExpCard_Delete]

USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_ExpCard_Create]    Script Date: 07/07/2009 18:16:41 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO



-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_ExpCard_Create]
@ItemGuid UNIQUEIDENTIFIER,
@CurExp BIGINT,
@MaxExp BIGINT,
@ExpPer SMALLINT
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	INSERT INTO dbo.tb_ExpCard (ItemGuid,CurExp,MaxExp,ExpPer) VALUES(@ItemGuid,@CurExp,@MaxExp,@ExpPer)

END
