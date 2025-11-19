USE [DR2_User]
GO

IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_UserPortal_Delete]'))
BEGIN
	DROP PROCEDURE [dbo].[up_UserPortal_Delete]
END

/****** Object:  StoredProcedure [dbo].[up_UserPortal_Delete]    Script Date: 03/20/2009 14:21:04 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[up_UserPortal_Delete]

@PortalGuid UNIQUEIDENTIFIER

AS 
BEGIN

	DELETE FROM	[dbo].[TB_UserPortal] WHERE [PortalGuid] = @PortalGuid
	SELECT @@ERROR
                     
END
          