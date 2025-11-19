USE DR2_USER
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_Guild_Member_Proc_UpdateLastLogin]') AND type in (N'P'))
BEGIN
	DROP PROCEDURE [dbo].[UP_Guild_Member_Proc_UpdateLastLogin]
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		À°Á¤¹ü
-- Create date: 2009-10-26
-- Description:	
-- =============================================
CREATE PROCEDURE [dbo].[UP_Guild_Member_Proc_UpdateLastLogin]
	@CharacterGuid UNIQUEIDENTIFIER
AS
BEGIN
	SET NOCOUNT ON;

    UPDATE dbo.TB_Guild_Member SET [f_LastLoginDate] = GetDate() WHERE [CharacterGuid] = @CharacterGuid
END
GO
