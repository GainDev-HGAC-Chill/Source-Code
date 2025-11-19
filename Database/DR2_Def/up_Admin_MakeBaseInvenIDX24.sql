USE [DR2_Def]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Admin_MakeBaseInvenIDX24]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Admin_MakeBaseInvenIDX24]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_Admin_MakeBaseInvenIDX24]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	UPDATE dbo.TB_DefBaseCharacter2 SET f_InvExtend = 0x010C020C030C040C050006000C000D000E0000000000000000000000000000000000000000000000
END
