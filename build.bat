for /F "tokens=*" %%g in ('git describe --always --tags') do (set GIT_VERSION_RAW=%%g)
echo GIT_VERSION_RAW=%GIT_VERSION_RAW%
for /F "tokens=1 delims=- " %%a in ("%GIT_VERSION_RAW%") do (set GIT_VERSION=%%a)
echo GIT_VERSION=%GIT_VERSION%
for /F "tokens=*" %%g in ('git branch --show-current') do (set APP_BRANCH=%%g)
echo APP_BRANCH=%APP_BRANCH%
for /F "tokens=*" %%g in ('git rev-list --count HEAD') do (set APP_BUILD=%%g)
echo APP_BUILD=%APP_BUILD%
for /F "tokens=*" %%g in ('git rev-parse --short HEAD') do (set APP_COMMIT=%%g)
echo APP_COMMIT=%APP_COMMIT%
set APP_VERSION=%GIT_VERSION%.%APP_BUILD%
echo APP_VERSION=%APP_VERSION%
set RC_VERSION=%APP_VERSION:.=,%
echo RC_VERSION=%RC_VERSION%
set FULL_VERSION=%APP_VERSION%-%APP_BRANCH%-%APP_COMMIT%
echo FULL_VERSION=%FULL_VERSION%
msbuild.exe engine.sln /p:Configuration=Release /t:Clean,Build -target:xrGame -m
