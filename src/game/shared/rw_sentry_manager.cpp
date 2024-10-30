//=================== Copyright (c) 2024 The Aridity Team, all rights reserved. ===================//
//
// Purpose: Sentry integration
//
//=================================================================================================//

#include "cbase.h"
#pragma warning ( disable : 4005 )
#pragma warning ( disable : 4700 )
#include "sentry.h"
#include "rw_sentry_manager.h"
#include "string"

CRWSentryMgr* g_SentryMgr = NULL;
CRWSentryMgr* RWSentryMgr() 
{
	return g_SentryMgr;
}

CRWSentryMgr::CRWSentryMgr()
{
	dsnLink = NULL; // unused
}
CRWSentryMgr::~CRWSentryMgr()
{
	delete dsnLink;
}

void CRWSentryMgr::Init() 
{
	sentry_options_t* options = sentry_options_new();
	sentry_options_set_dsn(options, "https://3e8ac4469aa6b58738c923d872796ac2@o4507485361668096.ingest.de.sentry.io/4508200806973520");

	sentry_value_t event = sentry_value_new_event();

#ifdef GAME_DLL
	char gamePath[256];
	engine->GetGameDir(gamePath, 256);
	Q_StripTrailingSlash(gamePath);

	std::string sGamePath = gamePath;
	std::string sHandlerPath = sGamePath.append("/bin/crashpad_handler.exe");
	std::string sDbPath = sGamePath.append(".sentry-native");

	const char *handlerPath = sHandlerPath.c_str();
	const char* dbPath = sDbPath.c_str();

	sentry_options_set_handler_path(options, handlerPath);
	sentry_options_set_database_path(options, dbPath);

	sentry_value_t exc = sentry_value_new_exception("Exception/Crash", "An exception has been thrown - server");
#else
	std::string sGamePath = engine->GetGameDirectory();
	std::string sHandlerPath = sGamePath.append("/bin/crashpad_handler.exe");
	std::string sDbPath = sGamePath.append(".sentry-native");

	const char* handlerPath = sHandlerPath.c_str();
	const char* dbPath = sDbPath.c_str();

	sentry_options_set_handler_path(options, handlerPath);
	sentry_options_set_database_path(options, dbPath);

	sentry_value_t exc = sentry_value_new_exception("Exception/Crash", "An exception has been thrown - client");
#endif
	sentry_options_set_release(options, "rw@0.0.1");
	sentry_options_set_debug(options, 1);
	sentry_options_set_environment(options, "production");

	sentry_value_set_stacktrace(exc, NULL, 0);
	sentry_event_add_exception(event, exc);

	sentry_capture_event(event);
	sentry_init(options);

#ifdef CLIENT_DLL
	ConColorMsg(Color(54, 45, 89, 255), "[ Sentry ] Sentry initialized - client\n");
#else
	ConColorMsg(Color(54, 45, 89, 255), "[ Sentry ] Sentry initialized - server\n");
#endif
}

void CRWSentryMgr::Shutdown()
{
	sentry_shutdown();
}

// logging
void CRWSentryMgr::SentryLog(char* message)
{
	ConMsg(message); // log through the app output also
	sentry_capture_event(sentry_value_new_message_event(
		/*   level */ SENTRY_LEVEL_INFO,
		/*  logger */ "CRWSentryMgr",
		/* message */ message
	));
}
void CRWSentryMgr::SentryWarn(char* message)
{
	ConMsg(message); // log through the app output also
	sentry_capture_event(sentry_value_new_message_event(
		/*   level */ SENTRY_LEVEL_WARNING,
		/*  logger */ "CRWSentryMgr",
		/* message */ message
	));
}
void CRWSentryMgr::SentryError(char* message)
{
	ConMsg(message); // log through the app output also
	sentry_capture_event(sentry_value_new_message_event(
		/*   level */ SENTRY_LEVEL_ERROR,
		/*  logger */ "CRWSentryMgr",
		/* message */ message
	));
}
