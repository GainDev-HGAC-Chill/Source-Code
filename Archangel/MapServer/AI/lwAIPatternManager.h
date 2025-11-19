#pragma once

LW_CLASS(PgAIPatternManager, AIPatternManager)
	bool Add(int iID, char const* pszName);
	bool AddActTransit(int iID, int iFrom, int iTo, int iWeight);
LW_CLASS_END;