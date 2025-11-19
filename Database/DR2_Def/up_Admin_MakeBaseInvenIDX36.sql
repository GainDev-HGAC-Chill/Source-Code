USE [DR2_Def]
GO
/****** Object:  StoredProcedure [dbo].[up_Admin_MakeBaseInvenIDX36]    Script Date: 08/26/2009 15:41:54 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Admin_MakeBaseInvenIDX36]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Admin_MakeBaseInvenIDX36]

USE [DR2_Def]
GO
/****** Object:  StoredProcedure [dbo].[up_Admin_MakeBaseInvenIDX36]    Script Date: 08/26/2009 15:41:58 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_Admin_MakeBaseInvenIDX36]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	UPDATE dbo.TB_DefBaseCharacter2 SET f_InvExtend = 0x00000000000000000000000000000000000000000000000000000000000000000000000000000000
	
END
