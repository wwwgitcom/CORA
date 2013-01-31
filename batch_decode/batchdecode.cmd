@echo off

for /F %%i in (%1) do (
  @echo decoding %%i
  ..\Release\Cora.exe FileName1=%%i_0.dmp FileName2=%%i_1.dmp
  @echo done...
  @echo 
)

@echo on
