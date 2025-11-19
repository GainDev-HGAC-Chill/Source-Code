IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_UserPortal_Create]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_UserPortal_Create]
GO

/****** Object:  StoredProcedure [dbo].[up_UserPortal_Create]    Script Date: 07/09/2009 11:32:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_UserPortal_Create]

@CharacterID UNIQUEIDENTIFIER,
@PortalGuid UNIQUEIDENTIFIER,
@Comment NVARCHAR(50),
@GroundNo INT,
@x FLOAT,
@y FLOAT,
@z FLOAT

AS 
BEGIN

	INSERT INTO [dbo].[TB_UserPortal]
			   ([CharacterGuid]
			   ,[PortalGuid]
			   ,[Comment]
			   ,[GroundNo]
			   ,[x]
			   ,[y]
			   ,[z])
		 VALUES
			   (@CharacterID
			   ,@PortalGuid
			   ,@Comment
			   ,@GroundNo
			   ,@x
			   ,@y
			   ,@z)
	           
	SELECT @@ERROR
                     
END
          

GO