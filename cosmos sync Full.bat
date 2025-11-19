REM -- h 카피
xcopy /Y ..\Core\cosmos_src\include\*.h .\cosmos\include\*.h
xcopy /Y ..\Core\cosmos_src\include\ace\*.h .\cosmos\include\ace\*.h
xcopy /Y ..\Core\cosmos_src\include\BM\*.h .\cosmos\include\BM\*.h
xcopy /Y ..\Core\cosmos_src\include\CEL\*.h .\cosmos\include\CEL\*.h
xcopy /Y ..\Core\cosmos_src\include\CSIME\*.h .\cosmos\include\CSIME\*.h
xcopy /Y ..\Core\cosmos_src\include\CSMail\*.h .\cosmos\include\CSMail\*.h
xcopy /Y ..\Core\cosmos_src\include\cximage\*.h .\cosmos\include\cximage\*.h
xcopy /Y ..\Core\cosmos_src\include\DataPack\*.h .\cosmos\include\DataPack\*.h
xcopy /Y ..\Core\cosmos_src\include\freetype\*.h .\cosmos\include\freetype\*.h
xcopy /Y ..\Core\cosmos_src\include\loki\*.h .\cosmos\include\loki\*.h
xcopy /Y ..\Core\cosmos_src\include\lua\*.h .\cosmos\include\lua\*.h
xcopy /Y ..\Core\cosmos_src\include\lua_tinker\*.h .\cosmos\include\lua_tinker\*.h
xcopy /Y ..\Core\cosmos_src\include\LuaDev\*.h .\cosmos\include\LuaDev\*.h
xcopy /Y ..\Core\cosmos_src\include\lzo\*.h .\cosmos\include\lzo\*.h
xcopy /Y ..\Core\cosmos_src\include\RandomLib\*.h .\cosmos\include\RandomLib\*.h
xcopy /Y ..\Core\cosmos_src\include\SimpEnc\*.h .\cosmos\include\SimpEnc\*.h
xcopy /Y ..\Core\cosmos_src\include\tinyxml\*.h .\cosmos\include\tinyxml\*.h

REM -- inl 카피
xcopy /Y ..\Core\cosmos_src\include\*.inl .\cosmos\include\*.inl
xcopy /Y ..\Core\cosmos_src\include\ace\*.inl .\cosmos\include\ace\*.inl
xcopy /Y ..\Core\cosmos_src\include\BM\*.inl .\cosmos\include\BM\*.inl
xcopy /Y ..\Core\cosmos_src\include\CEL\*.inl .\cosmos\include\CEL\*.inl
xcopy /Y ..\Core\cosmos_src\include\CSIME\*.inl .\cosmos\include\CSIME\*.inl
xcopy /Y ..\Core\cosmos_src\include\CSMail\*.inl .\cosmos\include\CSMail\*.inl
xcopy /Y ..\Core\cosmos_src\include\cximage\*.inl .\cosmos\include\cximage\*.inl
xcopy /Y ..\Core\cosmos_src\include\DataPack\*.inl .\cosmos\include\DataPack\*.inl
xcopy /Y ..\Core\cosmos_src\include\freetype\*.inl .\cosmos\include\freetype\*.inl
xcopy /Y ..\Core\cosmos_src\include\loki\*.inl .\cosmos\include\loki\*.inl
xcopy /Y ..\Core\cosmos_src\include\lua\*.inl .\cosmos\include\lua\*.inl
xcopy /Y ..\Core\cosmos_src\include\lua_tinker\*.inl .\cosmos\include\lua_tinker\*.inl
xcopy /Y ..\Core\cosmos_src\include\LuaDev\*.inl .\cosmos\include\LuaDev\*.inl
xcopy /Y ..\Core\cosmos_src\include\lzo\*.inl .\cosmos\include\lzo\*.inl
xcopy /Y ..\Core\cosmos_src\include\RandomLib\*.inl .\cosmos\include\RandomLib\*.inl
xcopy /Y ..\Core\cosmos_src\include\SimpEnc\*.inl .\cosmos\include\SimpEnc\*.inl
xcopy /Y ..\Core\cosmos_src\include\tinyxml\*.inl .\cosmos\include\tinyxml\*.inl

REM -- Gamebryo 카피
REM xcopy /Y /R ..\Core\cosmos_src\include\GameBryo\SDK\win32\include\*.inl .\cosmos\GameBryo_2.2.2\include\*.inl
REM xcopy /Y /S ..\Core\cosmos_src\include\GameBryo\SDK\win32\lib\VC80\*.lib .\cosmos\GameBryo_2.2.2\lib\*.lib

REM -- Libs 카피
xcopy /Y ..\Core\cosmos_src\lib\*.lib .\cosmos\lib\*.lib
xcopy /Y ..\Core\cosmos_src\lib\*.pdb .\cosmos\lib\*.pdb
xcopy /Y ..\Core\cosmos_src\lib\*.idb .\cosmos\lib\*.idb
xcopy /Y ..\Core\cosmos_src\lib\*.dll .\cosmos\lib\*.dll
xcopy /Y ..\Core\cosmos_src\lib\*.dll .\cosmos\lib\*.exp

