@echo off
setlocal
cd /d "%~dp0"
set "PATH=E:\Git\usr\bin;C:\ProgramData\mingw64\mingw64\bin;%PATH%"

if not exist build mkdir build

echo [1/3] Pase 1 de LaTeX...
pdflatex -shell-escape -interaction=nonstopmode -include-directory="content/tex" -output-directory=build content/kactl.tex >nul

echo [2/3] Pase 2 de LaTeX (resolviendo indice y referencias cruzadas)...
pdflatex -shell-escape -interaction=nonstopmode -include-directory="content/tex" -output-directory=build content/kactl.tex >nul

echo [3/3] Copiando PDF generado...
copy /y build\kactl.pdf kactl.pdf >nul

echo ========================================================
echo KACTL compilado exitosamente con indice resuelto: kactl.pdf
echo ========================================================
endlocal
