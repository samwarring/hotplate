echo ON

@set CMD=
@set CMD=cmake -G "Visual Studio 14 2015 Win64"
@set CMD=%CMD% -Dhotplate_CI_SERVICE=appveyor
@set CMD=%CMD% -Dhotplate_CI_BUILD_NUMBER=%APPVEYOR_BUILD_NUMBER%
@set CMD=%CMD% -Dhotplate_COMMIT=%APPVEYOR_REPO_COMMIT%
@set CMD=%CMD% -DBOOST_ROOT=C:\Libraries\boost_1_69_0
@set CMD=%CMD% -DBoost_USE_STATIC_LIBS=ON ..

%CMD%
