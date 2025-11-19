USE DR2_USER
GO

/****** 개체:  StoredProcedure [dbo].[up_Post_GetUserMailMin2]    스크립트 날짜: 07/17/2009 11:24:31 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Post_GetUserMailMin2]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Post_GetUserMailMin2]
GO

/****** ü:  StoredProcedure [dbo].[up_Post_GetUserMailMin2]    ũƮ ¥: 07/17/2009 11:24:31 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Post_GetUserMailMin2]') AND type in (N'P', N'PC'))
BEGIN
EXEC dbo.sp_executesql @statement = N'
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
create PROCEDURE [dbo].[up_Post_GetUserMailMin2]

@charguid uniqueidentifier

AS
BEGIN

set nocount on 

select isnull(min(mailindex),0) from dbo.tb_usermail where toguid = @charguid

END'
END
GO