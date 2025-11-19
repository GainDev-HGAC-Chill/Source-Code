USE DR2_USER
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET XACT_ABORT ON

BEGIN TRAN


IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_UserItem_Enchant]') AND type in (N'U'))
BEGIN

	--테이블TB_UserItem_Enchant을생성
	CREATE TABLE [dbo].[TB_UserItem_Enchant](
		[ItemGuid] [uniqueidentifier] NOT NULL,
		[Enchant_01] [bigint] NOT NULL,
		[Enchant_02] [bigint] NOT NULL,
		[Enchant_03] [bigint] NOT NULL DEFAULT ((0)),
		[Enchant_04] [bigint] NOT NULL DEFAULT ((0)),
	 CONSTRAINT [PK_TB_UserItem_Enchant] PRIMARY KEY CLUSTERED 
	(
		[ItemGuid] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]

	--테이블TB_UserItem_Enchant에Enchant_01,Enchant_02의값을추가, 4는으로세팅
	insert into TB_UserItem_Enchant(ItemGuid, Enchant_01,Enchant_02)
	(select itemguid, enchant_01, enchant_02 from TB_UserItem where enchant_01 >0 or enchant_02 >0)

	--테이블TB_UserItem 에서컬럼Enchant_01, Enchant_02을제거
	alter table TB_UserItem
	drop column Enchant_01, Enchant_02

END

COMMIT TRAN
GO
