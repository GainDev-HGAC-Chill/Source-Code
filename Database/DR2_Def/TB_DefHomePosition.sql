USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefHomePosition]    Script Date: 08/13/2009 16:14:27 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefHomePosition]') AND type in (N'U'))
DROP TABLE [dbo].[TB_DefHomePosition]