USE DR2_Def

ALTER TABLE [dbo].[TB_DefMission_Result] ADD
[f_RankSSS] [int] NOT NULL CONSTRAINT [DF_TB_DefMission_Result_f_RankSSS] DEFAULT ((0)),
[f_RankSS] [int] NOT NULL CONSTRAINT [DF_TB_DefMission_Result_f_RankSS] DEFAULT ((0)),
[f_ResultCountMinSSS] [int] NOT NULL CONSTRAINT [DF_TB_DefMission_Result_f_ResultCountMinS2] DEFAULT ((0)),
[f_ResultCountMaxSSS] [int] NOT NULL CONSTRAINT [DF_TB_DefMission_Result_f_ResultCountMaxS2] DEFAULT ((0)),
[f_ResultCountMinSS] [int] NOT NULL CONSTRAINT [DF_TB_DefMission_Result_f_ResultCountMinS1] DEFAULT ((0)),
[f_ResultCountMaxSS] [int] NOT NULL CONSTRAINT [DF_TB_DefMission_Result_f_ResultCountMaxS1] DEFAULT ((0))
GO