USE [DR2_Def]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadDefHomePosition]    Script Date: 08/13/2009 10:31:30 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefHomePosition]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefHomePosition]
go
