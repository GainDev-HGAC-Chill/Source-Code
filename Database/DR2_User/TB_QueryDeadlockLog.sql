USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_QueryDeadlockLog]    Script Date: 01/12/2010 20:17:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_QueryDeadlockLog](
	[idx] [int] IDENTITY(1,1) NOT NULL,
	[SPName] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[ErrorCode] [int] NULL,
	[SpinCount] [int] NULL,
	[DeadlockDate] [datetime] NULL,
 CONSTRAINT [PK_TB_QueryDeadlockLog] PRIMARY KEY CLUSTERED 
(
	[idx] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
