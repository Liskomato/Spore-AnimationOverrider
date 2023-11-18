@echo on

set CUR_DIR="%~dp0"
mkdir "%CUR_DIR%\obj"

copy "%CUR_DIR%\ModInfo.xml" "%CUR_DIR%\obj\"

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x86

devenv "%~dp0\AnimationOverrider\AnimationOverrider.sln" /Build "Release"

copy "%programdata%\SPORE ModAPI Launcher Kit\mLibs\AnimationOverrider.dll" "%CUR_DIR%\obj\"

smfx pack "%~dp0\ExampleSMFXProjects\CaptainIdleOverride"  "%~dp0\obj\CaptainIdleOverride.package"

cd "%CUR_DIR%\obj\"

"C:\Program Files\7-Zip\7z" a -tzip %CUR_DIR%\AnimationOverrider.sporemod *

cd "%CUR_DIR%"

rmdir /s /q "%CUR_DIR%\obj\"