@echo on

set CUR_DIR="%~dp0"

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x86

devenv "%~dp0\AnimationOverrider\AnimationOverrider.sln" /Build "Debug"

smfx pack "%~dp0\ExampleSMFXProjects\CaptainIdleOverride"  "C:\Pelit\Origin Games\SPORE Galactic Adventures\Data\CaptainIdleOverride.package"