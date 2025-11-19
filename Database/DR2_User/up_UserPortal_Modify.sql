USE [DR2_User]
GO

IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_UserPortal_Modify]'))
BEGIN
	DROP PROCEDURE [dbo].[up_UserPortal_Modify]
END

/****** Object:  StoredProcedure [dbo].[up_UserPortal_Modify]    Script Date: 03/20/2009 14:23:18 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[up_UserPortal_Modify]

@PortalGuid UNIQUEIDENTIFIER,
@Comment NVARCHAR(50),
@GroundNo INT,
@x FLOAT,
@y FLOAT,
@z FLOAT

AS 
BEGIN

	UPDATE		[dbo].[TB_UserPortal]
			   SET [PortalGuid] = @PortalGuid
			   ,[Comment] = @Comment
			   ,[GroundNo] = @GroundNo
			   ,[x] = @x
			   ,[y] = @y
			   ,[z] = @z

	WHERE [PortalGuid] = @PortalGuid
	           
	SELECT @@ERROR
                     
END
          