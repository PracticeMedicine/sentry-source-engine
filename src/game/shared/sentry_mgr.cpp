//=================== Copyright (c) 2025 The Aridity Team, all rights reserved. ===================//
//
// Purpose: Sentry integration
//
//=================================================================================================//

#include "cbase.h"

#ifdef _USE_SENTRY
#pragma warning ( disable : 4005 )
#pragma warning ( disable : 4700 )
#include "sentry.h"
#include "sentry_mgr.h"
//#include "steam/isteamnetworkingsockets.h"
#include <string>
#include "tier0/icommandline.h"

// memdbgon.h must be the last include in a cpp file!!!!
#include "tier0/memdbgon.h"

// replace this with your Sentry project's DSN link
#define SENTRY_DSN_LINK "<your-dsn-link-here>"
// replace this with anything you want
#define SENTRY_RELEASE "mymod@version"
// replace this with anything you want
#define SENTRY_ENVIRONMENT "development"

#ifdef _WIN32 // dw its gonna still work in the 64 bit config
#define SENTRY_CRASHPADEXE_NAME "aridity_crashpad.exe"
#else
#define SENTRY_CRASHPADEXE_NAME "aridity_crashpad"
#endif

CSentryMgr::CSentryMgr()
	: CAutoGameSystemPerFrame("sentry_manager")
{
}

bool CSentryMgr::Init() 
{
	sentry_options_t* options = sentry_options_new();
	sentry_options_set_dsn(options, SENTRY_DSN_LINK);

	sentry_value_t event = sentry_value_new_event();

#ifdef GAME_DLL
	char gamePath[256];
	engine->GetGameDir(gamePath, 256);
	Q_StripTrailingSlash(gamePath);

	char handlerPath[128];
	char dbPath[128];

	Q_snprintf(handlerPath, sizeof(handlerPath), "%s\\bin\\%s", gamePath, SENTRY_CRASHPADEXE_NAME);
	Q_snprintf(dbPath, sizeof(dbPath), "%s\\bin\\.sentry-native", gamePath);

	if(CommandLine()->FindParm("-sentry-handler-path"))
		Q_snprintf(handlerPath, sizeof(handlerPath), "%s\\%s", gamePath, CommandLine()->GetParm(CommandLine()->FindParm("-sentry-handler-path")));

	if(CommandLine()->FindParm("-sentry-db-path"))
		Q_snprintf(handlerPath, sizeof(handlerPath), "%s\\%s", gamePath, CommandLine()->GetParm(CommandLine()->FindParm("-sentry-db-path")));

	Q_StripTrailingSlash(handlerPath);
	Q_StripTrailingSlash(dbPath);

	sentry_value_t exc = sentry_value_new_exception("Exception/Crash", "An exception has been thrown - server");
#else
	const char* gamePath = engine->GetGameDirectory();

	char handlerPath[128];
	char dbPath[128];

	if (CommandLine()->FindParm("-sentry-handler-path"))
		Q_snprintf(handlerPath, sizeof(handlerPath), "%s\\%s", gamePath, CommandLine()->GetParm(CommandLine()->FindParm("-sentry-handler-path")));
	else
		Q_snprintf(handlerPath, sizeof(handlerPath), "%s\\bin\\%s", gamePath, SENTRY_CRASHPADEXE_NAME);

	if (CommandLine()->FindParm("-sentry-db-path"))
		Q_snprintf(handlerPath, sizeof(handlerPath), "%s\\%s", gamePath, CommandLine()->GetParm(CommandLine()->FindParm("-sentry-db-path")));
	else
		Q_snprintf(dbPath, sizeof(dbPath), "%s\\bin\\.sentry-native", gamePath);

	Q_StripTrailingSlash(handlerPath);
	Q_StripTrailingSlash(dbPath);

	sentry_value_t exc = sentry_value_new_exception("Exception/Crash", "An exception has been thrown - client");
#endif

	ConColorMsg(Color(54, 45, 89, 255), "[ Sentry ] Path to \"%s\": %s\n", SENTRY_CRASHPADEXE_NAME, handlerPath);
	ConColorMsg(Color(54, 45, 89, 255), "[ Sentry ] Path to Crashpad database cache: %s\n", dbPath);

	sentry_options_set_handler_path(options, handlerPath);
	sentry_options_set_database_path(options, dbPath);
	sentry_options_set_release(options, SENTRY_RELEASE);
	sentry_options_set_debug(options, 1);
	sentry_options_set_environment(options, SENTRY_ENVIRONMENT);

	sentry_value_set_stacktrace(exc, NULL, 0);
	sentry_event_add_exception(event, exc);

	sentry_capture_event(event);
	sentry_init(options);

#ifdef CLIENT_DLL
	ConColorMsg(Color(54, 45, 89, 255), "[ Sentry ] Sentry initialized - client\n");
#else
	ConColorMsg(Color(54, 45, 89, 255), "[ Sentry ] Sentry initialized - server\n");
#endif

	return true;
}

void CSentryMgr::Shutdown()
{
	sentry_close();
}

void CSentryMgr::Update( float frametime )
{
	/*SteamNetworkingIdentity netID;

	sentry_value_t user = sentry_value_new_object();
	if (SteamNetworkingSockets()->GetIdentity(&netID))
	{
		sentry_value_set_by_key(user, "id", sentry_value_new_string(std::to_string(netID.GetSteamID64()).c_str()));
	}*/
}

// capture events
void CSentryMgr::SentryInfo(const char* logger, const char* message)
{
	sentry_capture_event(sentry_value_new_message_event(
		/*   level */ SENTRY_LEVEL_INFO,
		/*  logger */ logger,
		/* message */ message
	));
}
void CSentryMgr::SentryWarn(const char* logger, const char* message)
{
	sentry_capture_event(sentry_value_new_message_event(
		/*   level */ SENTRY_LEVEL_WARNING,
		/*  logger */ logger,
		/* message */ message
	));
}
void CSentryMgr::SentryError(const char* logger, const char* message)
{
	sentry_capture_event(sentry_value_new_message_event(
		/*   level */ SENTRY_LEVEL_ERROR,
		/*  logger */ logger,
		/* message */ message
	));
}

static CSentryMgr s_SentryMgr;
CSentryMgr* GetSentryMgr() { return &s_SentryMgr; }
#endif
