USE [DR2_Member]
GO

/****** Object:  Table [dbo].[TB_Event_Type]    Script Date: 11/18/2009 12:21:10 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_Event_Type](
	[f_EventKey] [int] NOT NULL,
	[f_StartDate] [datetime] NOT NULL,
	[f_EndDate] [datetime] NOT NULL,
	[f_Memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[f_Title] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[f_Discriptino] [nvarchar](200) COLLATE Korean_Wansung_CI_AS NULL,
	[f_Idx] [int] NOT NULL,
 CONSTRAINT [PK_TB_Event_Type] PRIMARY KEY CLUSTERED 
(
	[f_EventKey] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]



begin tran
alter table [dbo].[TB_Event_Type] add f_Tmp int null
go

if @@error <> 0
begin
	rollback tran
	return
end

update [dbo].[TB_Event_Type] set f_Tmp = f_idx
go

if @@error <> 0
begin
	rollback tran
	return
end

alter table [dbo].[TB_Event_Type] drop column f_IDX
go

if @@error <> 0
begin
	rollback tran
	return
end

exec sp_rename '[dbo].[TB_Event_Type].f_Tmp','f_Idx','column'

if @@error <> 0
begin
	rollback tran
	return
end

alter table [dbo].[TB_Event_Type] alter column [f_IDX] int not null
go

if @@error <> 0
begin
	rollback tran
	return
end

commit tran