//=================== Copyright (c) 2024 The Aridity Team, all rights reserved. ===================//
//
// Purpose: Sentry integration
//
//=================================================================================================//

#ifndef RW_SENTRY_MGR_H
#define RW_SENTRY_MGR_H
#ifdef _WIN32
#pragma once
#endif

#pragma warning ( disable : 4005 )

class CRWSentryMgr 
{
	DECLARE_CLASS_NOBASE(CRWSentryMgr);

public:
	CRWSentryMgr();
	~CRWSentryMgr();

	void Init();
	void Shutdown();

	void SentryLog(char* message);
	void SentryWarn(char* message);
	void SentryError(char* message);

private:
	char* dsnLink;
};

extern CRWSentryMgr* RWSentryMgr();

#endif // !RW_SENTRY_MGR_H

