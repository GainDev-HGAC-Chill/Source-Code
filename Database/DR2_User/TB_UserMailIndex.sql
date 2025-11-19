USE DR2_User

-- 사용하지 않는 예전 마켓 테이블 삭제

IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_UserMailIndex]'))
BEGIN
	DROP TABLE [dbo].[TB_UserMailIndex]
END
GO