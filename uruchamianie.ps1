$folderPath = "C:\Users\piotr\projects\OK_projekt_ind\cmake-build-debug\inputs"

# Ścieżka do programu, który ma być uruchomiony
$programPath = "C:\Users\piotr\projects\OK_projekt_ind\cmake-build-debug\OK_projekt_ind.exe"

# Pobierz listę plików w folderze, w tym z podfolderów
$files = Get-ChildItem -Path $folderPath -File -Recurse

# Pętla for
for ($i = 0; $i -lt $files.Count; $i++) {
    $file = $files[$i]

    # Ścieżka do pliku
    $filePath = $file.FullName

    # Uruchomienie programu dla pliku
    Write-Host "Uruchamiam $programPath dla pliku $filePath"
    Start-Process -FilePath $programPath -ArgumentList $filePath -Wait
}