USE DR2_Member
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.[UP_EventQuest_Init_Status]') AND Type in (N'P'))
BEGIN
	DROP PROCEDURE dbo.[UP_EventQuest_Init_Status]
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE dbo.[UP_EventQuest_Init_Status]
	@RealmNo INT
AS
BEGIN
	SET NOCOUNT ON;

	INSERT INTO [dbo].[TB_EventQuest_Status] 
		([f_RealmNo],[f_Enable],[f_Status])	
		VALUES (@RealmNo,1,0)
END
GO
