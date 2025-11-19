USE DR2_Member
GO

IF EXISTS(SELECT 1 FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.[UP_BS_Init_Status]') AND type in (N'P'))
BEGIN
	DROP PROCEDURE dbo.[UP_BS_Init_Status]
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		À°Á¤¹ü
-- Create date: 2009-09-15
-- Description:	
-- =============================================
CREATE PROCEDURE dbo.[UP_BS_Init_Status]
	@RealmNo int
AS
BEGIN
	SET NOCOUNT ON;

    -- Insert statements for procedure here
	DELETE FROM [dbo].[TB_BattleSquare_Status] WHERE [f_RealmNo] = @RealmNo
END
GO
