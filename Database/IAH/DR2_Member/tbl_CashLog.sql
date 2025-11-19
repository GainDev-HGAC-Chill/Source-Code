USE DR2_Member
GO

ALTER TABLE [dbo].[tbl_CashLog] ADD
[f_usedmileage] [bigint] NULL,
[f_newmileage] [bigint] NULL,
[f_curmileage] [bigint] NULL
GO

ALTER TABLE [dbo].[TBL_CashLog] ADD [f_CashCode] [nvarchar](255) NULL
GO
