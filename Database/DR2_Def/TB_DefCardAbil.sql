USE DR2_Def

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id=OBJECT_ID(N'[dbo].[TB_DefCardAbil]')) 
BEGIN

CREATE TABLE [dbo].[TB_DefCardAbil]
(
[Idx] [int] NOT NULL IDENTITY(1, 1),
[memo] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NULL,
[Constellation] [tinyint] NOT NULL,
[Sports] [tinyint] NOT NULL,
[Hobby] [tinyint] NOT NULL,
[Style] [tinyint] NOT NULL,
[AbilType] [smallint] NOT NULL,
[Value] [int] NOT NULL
)

ALTER TABLE [dbo].[TB_DefCardAbil] ADD CONSTRAINT [PK_TB_DefCardAbil] PRIMARY KEY CLUSTERED ([Idx])

END
GO


ALTER TABLE [dbo].[TB_DefCardAbil] DROP COLUMN [Sports]
GO

ALTER TABLE [dbo].[TB_DefCardAbil] ADD [Blood] [tinyint] NOT NULL DEFAULT(0)
GO
