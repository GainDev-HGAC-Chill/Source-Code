USE DR2_User
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Guild_Entrance_Cancel]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Guild_Entrance_Cancel]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	길드가입 신청취소
-- =============================================
CREATE PROCEDURE [dbo].[up_Guild_Entrance_Cancel]	
	@CharacterGuid uniqueidentifier
AS
BEGIN
	SET NOCOUNT ON;
	DELETE FROM dbo.TB_Guild_Applicant 
	WHERE CharacterGuid = @CharacterGuid
	SET NOCOUNT OFF;
END
GO
