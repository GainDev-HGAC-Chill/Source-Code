USE [DR2_Def]
GO

/****** Object:  Table [dbo].[TB_DefEvent_JobSkill_Location]    Script Date: 12/12/2012 12:26:12 ******/
IF  not EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefEvent_JobSkill_Location]') AND type in (N'U'))
BEGIN

CREATE TABLE [dbo].[TB_DefEvent_JobSkill_Location](
       [IDX] [int] NOT NULL,
       [f_NationCodeStr] [nvarchar](50) NOT NULL,
       [Memo] [nvarchar](50) NULL,
       [Start_Date] [datetime] NOT NULL,
       [End_Date] [datetime] NOT NULL,
       [f_JobGrade] [int] NOT NULL,
       [RewardItemGroup] [int] NOT NULL,
       [Rate] [int] NOT NULL,
CONSTRAINT [PK_TB_DefEvent_JobSkill_Location] PRIMARY KEY CLUSTERED 
(
       [f_NationCodeStr] ASC,
       [f_JobGrade] ASC,
       [RewardItemGroup] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]


ALTER TABLE [dbo].[TB_DefEvent_JobSkill_Location] ADD  CONSTRAINT [DF_TB_DefEvent_JobSkill_Location_Rate]  DEFAULT ((0)) FOR [Rate]


END
