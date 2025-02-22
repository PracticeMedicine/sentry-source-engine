# sentry-source-engine
This repository contains the files needed to implement Sentry to the Source engine. This code was published in hope that this could help developers trace player's session when crashing.

**This will contain both x64 and x86 binaries of Sentry Native.**

## How do I add this into my sourcemod?
Here's the list of things you require before you continue on this tutorial:
- A existing Sentry project (see https://docs.sentry.io/product/sentry-basics/integrate-frontend/create-new-project on how to create a project)
- Source SDK 2013 code (duh)
- Visual Studio Community/Professional 2022 (you can download it here: https://visualstudio.microsoft.com) with Desktop development with C++ workload and C/C++ v143 MFC modules
- Python 3 (you need this for compiling the latest SDK 2013 code)

First, you need to add this in both of your client and server VPC scripts:
```vpc
	...
	$Include "$SRCDIR\game\shared\sentry.vpc"
	...
```

Recreate the client and server projects by running `createallprojects.bat` and open "everything.sln" with Visual Studio 2022.

Before you build the project, open the [sentry_mgr.cpp](src/game/shared/sentry/sentry_mgr.cpp) code and go to line 22.
Replace the `<your-dsn-link-here>` string with your Sentry project's DSN link (you can get it from `Project Settings -> Client Keys (DSN)`).

Right-click the solution and then "Build Solution" or press CTRL+SHIFT+B.

After everything was built with no errors, put everything on the [bin](src/thirdparty/sentry_native/bin) directory to your mod's "bin" directory.
