//=================== Copyright (c) 2025 The Aridity Team, all rights reserved. ===================//
//
// Purpose: Sentry integration
//
//=================================================================================================//

#ifndef SENTRY_MGR_H
#define SENTRY_MGR_H
#ifdef _WIN32
#pragma once
#endif

#ifdef _USE_SENTRY

#pragma warning ( disable : 4005 )

#include "igamesystem.h"

class CSentryMgr : public CAutoGameSystemPerFrame
{
public:
	CSentryMgr();

	virtual bool Init();
	virtual void Shutdown();

	virtual void LevelInitPreEntity() {};
	virtual void LevelShutdownPreEntity() {};

	virtual void Update( float frametime );

	void SentryInfo(const char *logger, const char* message);
	void SentryWarn(const char* logger, const char* message);
	void SentryError(const char* logger, const char* message);
};

extern CSentryMgr* GetSentryMgr();
#endif

#endif // !BF_SENTRY_MGR_H

