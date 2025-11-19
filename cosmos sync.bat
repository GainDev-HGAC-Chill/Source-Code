SET CORE_PATH=D:\Project\Dragonica\Core\cosmos_src\

REM xcopy /Y %CORE_PATH%include\ace\*.h .\cosmos\include\ace\*.h
REM xcopy /Y %CORE_PATH%include\ace\*.cpp .\cosmos\include\ace\*.cpp
REM xcopy /Y %CORE_PATH%include\ace\*.inl .\cosmos\include\ace\*.inl
REM xcopy /Y %CORE_PATH%include\ace\os_include\*.h .\cosmos\include\ace\os_include\*.h
REM xcopy /Y %CORE_PATH%include\ace\os_include\arpa\*.h .\cosmos\include\ace\os_include\arpa\*.h
REM xcopy /Y %CORE_PATH%include\ace\os_include\net\*.h .\cosmos\include\ace\os_include\net\*.h
REM xcopy /Y %CORE_PATH%include\ace\os_include\netinet\*.h .\cosmos\include\ace\os_include\netinet\*.h
REM xcopy /Y %CORE_PATH%include\ace\os_include\sys\*.h .\cosmos\include\ace\os_include\sys\*.h


REM xcopy /Y %CORE_PATH%include\lua\*.h .\cosmos\include\lua\*.h
REM xcopy /Y %CORE_PATH%include\lua_tinker\*.h .\cosmos\include\lua_tinker\*.h
REM xcopy /Y %CORE_PATH%include\tinyxml\*.h .\cosmos\include\tinyxml\*.h
REM xcopy /Y %CORE_PATH%include\loki\*.h .\cosmos\include\loki\*.h
REM xcopy /Y %CORE_PATH%include\freetype\*.h .\cosmos\include\freetype\*.h
REM xcopy /Y %CORE_PATH%include\LuaDev\*.h .\cosmos\include\LuaDev\*.h
REM xcopy /Y %CORE_PATH%include\ace\*.inl .\cosmos\include\ace\*.inl

xcopy /Y %CORE_PATH%include\CEL\*.h .\cosmos\include\CEL\*.h
xcopy /Y %CORE_PATH%include\BM\*.h .\cosmos\include\BM\*.h
xcopy /Y %CORE_PATH%include\CSIME\*.h .\cosmos\include\CSIME\*.h
xcopy /Y %CORE_PATH%include\DataPack\*.h .\cosmos\include\DataPack\*.h
REM xcopy /Y /R %CORE_PATH%include\GameBryo\SDK\win32\include\*.h .\cosmos\GameBryo_2.2.2\include\*.h

xcopy /Y %CORE_PATH%include\CEL\*.inl .\cosmos\include\CEL\*.inl
xcopy /Y %CORE_PATH%include\BM\*.inl .\cosmos\include\BM\*.inl
xcopy /Y %CORE_PATH%include\CSIME\*.inl .\cosmos\include\CSIME\*.inl
xcopy /Y %CORE_PATH%include\DataPack\*.inl .\cosmos\include\DataPack\*.inl
REM xcopy /Y /R %CORE_PATH%include\GameBryo\SDK\win32\include\*.inl .\cosmos\GameBryo_2.2.2\include\*.inl

xcopy /Y %CORE_PATH%include\CEL\*.hpp .\cosmos\include\CEL\*.hpp
xcopy /Y %CORE_PATH%include\BM\*.hpp .\cosmos\include\BM\*.hpp
xcopy /Y %CORE_PATH%include\CSIME\*.hpp .\cosmos\include\CSIME\*.hpp
xcopy /Y %CORE_PATH%include\DataPack\*.hpp .\cosmos\include\DataPack\*.hpp
REM xcopy /Y /R %CORE_PATH%include\GameBryo\SDK\win32\include\*.hpp .\cosmos\GameBryo_2.2.2\include\*.hpp

xcopy /Y %CORE_PATH%lib\*.lib .\cosmos\lib\*.lib
xcopy /Y %CORE_PATH%lib\*.pdb .\cosmos\lib\*.pdb
xcopy /Y %CORE_PATH%lib\*.idb .\cosmos\lib\*.idb
REM  xcopy /Y /S %CORE_PATH%include\GameBryo\SDK\win32\lib\VC80\*.lib .\cosmos\GameBryo_2.2.2\lib\*.lib
