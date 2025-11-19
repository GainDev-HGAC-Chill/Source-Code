USE DR2_User
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Guild_Entrance_Process]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Guild_Entrance_Process]

SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		김동환
-- Create date: <Create Date,,>
-- Description: 1: 수락, 2: 거절, 3: 완료
-- =============================================
CREATE PROCEDURE [dbo].[up_Guild_Entrance_Process]
	@CharacterGuid uniqueidentifier,
	@Flag TINYINT
AS
BEGIN
	SET NOCOUNT ON;	
		IF @Flag < 3
		BEGIN
			UPDATE dbo.TB_Guild_Applicant SET IsAcceptanceState = @Flag
			WHERE [CharacterGuid] = @CharacterGuid
		END
		ELSE
		BEGIN
			DELETE FROM dbo.TB_Guild_Applicant
			WHERE [CharacterGuid] = @CharacterGuid
		END
	SET NOCOUNT OFF;
END
GO
