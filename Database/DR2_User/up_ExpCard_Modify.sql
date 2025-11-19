USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_ExpCard_Modify]    Script Date: 07/07/2009 18:18:44 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_ExpCard_Modify]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_ExpCard_Modify]

USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_ExpCard_Modify]    Script Date: 07/07/2009 18:18:49 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_ExpCard_Modify]
@ItemGuid UNIQUEIDENTIFIER,
@CurExp BIGINT,
@MaxExp BIGINT,
@ExpPer SMALLINT
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	UPDATE dbo.TB_ExpCard SET CurExp = @CurExp,MaxExp = @MaxExp,ExpPer = @ExpPer WHERE ItemGuid = @ItemGuid

END
