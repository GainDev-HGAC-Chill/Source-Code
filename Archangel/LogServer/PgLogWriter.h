#pragma once

#include "CEL/PgTask.h"

class PgLogWriter
	:	public PgTask<>
{
public:
	PgLogWriter(void);
	virtual ~PgLogWriter(void);


public:
	virtual void HandleMessage(SEventMessage *pkMsg);
};
#define g_kLogWriter SINGLETON_STATIC(PgLogWriter)
