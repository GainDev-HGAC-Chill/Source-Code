USE DR2_USER
GO


IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Post_GetUserMailMin]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Post_GetUserMailMin]
GO
