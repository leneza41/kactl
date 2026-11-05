# Script de compilacion de KACTL para Windows (PowerShell + MiKTeX)
$ErrorActionPreference = "Stop"
Set-Location $PSScriptRoot

$env:PATH = "E:\Git\usr\bin;C:\ProgramData\mingw64\mingw64\bin;$env:PATH"

if (-not (Test-Path "build")) {
    New-Item -ItemType Directory -Path "build" | Out-Null
}

Write-Host "[1/3] Pase 1 de LaTeX..." -ForegroundColor Cyan
& pdflatex -shell-escape -interaction=nonstopmode -include-directory="content/tex" -output-directory=build content/kactl.tex | Out-Null

Write-Host "[2/3] Pase 2 de LaTeX (resolviendo indice y referencias)..." -ForegroundColor Cyan
& pdflatex -shell-escape -interaction=nonstopmode -include-directory="content/tex" -output-directory=build content/kactl.tex | Out-Null

if (Test-Path "build/kactl.pdf") {
    Copy-Item "build/kactl.pdf" "kactl.pdf" -Force
    Write-Host "`n[OK] KACTL compilado con exito: kactl.pdf" -ForegroundColor Green
} else {
    Write-Host "`n[ERROR] No se pudo generar build/kactl.pdf" -ForegroundColor Red
}
