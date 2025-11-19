USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_Web_BaseItemInfo]    Script Date: 06/09/2010 14:15:43 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_Web_BaseItemInfo](
	[f_ItemNo] [int] NOT NULL,
	[f_ItemName] [nvarchar](100) NOT NULL,
	[f_IsEquipItem] [bit] NOT NULL,
	[f_MaxCount] [int] NOT NULL,
	[f_BasePhysAttackMin] [int] NOT NULL,
	[f_BasePhysAttackMax] [int] NOT NULL,
	[f_BaseMagicAttackMin] [int] NOT NULL,
	[f_BaseMagicAttackMax] [int] NOT NULL,
	[f_BasePhysDefence] [int] NOT NULL,
	[f_BaseMagicDefence] [int] NOT NULL,
 CONSTRAINT [PK_TB_Web_BaseItemInfo] PRIMARY KEY CLUSTERED 
(
	[f_ItemNo] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'아이템 번호' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Web_BaseItemInfo', @level2type=N'COLUMN',@level2name=N'f_ItemNo'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'장비냐?/아니냐?' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Web_BaseItemInfo', @level2type=N'COLUMN',@level2name=N'f_IsEquipItem'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'장비=최대 내구도, 기타=0' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Web_BaseItemInfo', @level2type=N'COLUMN',@level2name=N'f_MaxCount'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'물리 최소 공격력 (기타=0)' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Web_BaseItemInfo', @level2type=N'COLUMN',@level2name=N'f_BasePhysAttackMin'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'물리 최대 공격력 (기타=0)' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Web_BaseItemInfo', @level2type=N'COLUMN',@level2name=N'f_BasePhysAttackMax'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'마법 최소 공격력 (기타=0)' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Web_BaseItemInfo', @level2type=N'COLUMN',@level2name=N'f_BaseMagicAttackMin'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'마법 최대 공격력 (기타=0)' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Web_BaseItemInfo', @level2type=N'COLUMN',@level2name=N'f_BaseMagicAttackMax'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'물리 방어력 (기타=0)' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Web_BaseItemInfo', @level2type=N'COLUMN',@level2name=N'f_BasePhysDefence'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'마법 방어력 (기타=0)' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Web_BaseItemInfo', @level2type=N'COLUMN',@level2name=N'f_BaseMagicDefence'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'기획자가 설정한 아이템 기준 정보' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Web_BaseItemInfo'