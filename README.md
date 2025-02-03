#Harmonogram

Oto harmonogram pracy na cały semestr dla projektu audio wizualizera wraz z użytymi technologiami i środowiskami:

**Technologie i Środowiska**

•	**Język programowania**: C++

•	**Biblioteka graficzna**: SFML (Simple and Fast Multimedia Library)

•	**Analiza dźwięku**: FFT (Fast Fourier Transform) – zewnętrzna biblioteka np. FFTW lub KissFFT

•	**Środowisko programistyczne**: Visual Studio Code (VS Code)

•	**System kompilacji**: CMake 

•	**System operacyjny**: macOS

**Harmonogram na Semestr (około 14 tygodni, zajęcia co dwa tygodnie)**

#📅 Etap 1: Analiza i Planowanie (1-2 dni)#

✅ Cel: Określenie funkcjonalności i technologii
🔹 Wybór języka programowania (C++) i bibliotek (SFML, FFTW3)
🔹 Opracowanie ogólnej architektury aplikacji
🔹 Określenie interfejsu użytkownika (UI)

#📅 Etap 2: Inicjalizacja Projektu (1 dzień)#

✅ Cel: Utworzenie podstawowego szkieletu aplikacji
🔹 Konfiguracja środowiska programistycznego (kompilator, VS Code)
🔹 Utworzenie głównej pętli SFML (main.cpp)
🔹 Tworzenie okna aplikacji przy użyciu SFML

#📅 Etap 3: Obsługa Plików Audio i Odtwarzanie (2-3 dni)#

✅ Cel: Wczytywanie i odtwarzanie plików dźwiękowych
🔹 Implementacja AudioVisualizer
🔹 Wczytywanie plików (sf::SoundBuffer)
🔹 Obsługa odtwarzania (sf::Sound)

#📅 Etap 4: Implementacja Transformacji Fouriera (FFT) (3-4 dni)#

✅ Cel: Przetwarzanie sygnału dźwiękowego w celu analizy częstotliwości
🔹 Integracja biblioteki FFTW3
🔹 Tworzenie planu FFT (fftw_plan)
🔹 Pobieranie próbek i obliczanie ich widma częstotliwości
🔹 Konwersja danych FFT do postaci gotowej do wizualizacji

#📅 Etap 5: Tworzenie Wizualizacji (3-5 dni)#

✅ Cel: Dynamiczne rysowanie wizualizacji dźwięku
🔹 Analiza wyników FFT i ich interpretacja
🔹 Rysowanie słupków amplitudy przy użyciu SFML
🔹 Optymalizacja wydajności (aktualizacja na bieżąco)

#📅 Etap 6: Interfejs Użytkownika – Panel Ustawień (2-3 dni)#

✅ Cel: Dodanie interaktywnego UI do sterowania aplikacją
🔹 Tworzenie SettingsPanel
🔹 Obsługa wyboru katalogu z muzyką
🔹 Implementacja dynamicznych zmian ustawień

#📅 Etap 7: System Zarządzania Playlistą (2-3 dni)#

✅ Cel: Możliwość wybierania i zmiany utworów
🔹 Implementacja SongPanel
🔹 Wczytywanie plików z katalogu
🔹 Obsługa zmiany piosenek

#📅 Etap 8: Optymalizacja i Poprawki (2-4 dni)#

✅ Cel: Usprawnienie działania aplikacji i eliminacja błędów
🔹 Optymalizacja FFT i SFML dla lepszej wydajności
🔹 Poprawki interfejsu użytkownika
🔹 Debugowanie i testowanie różnych plików audio

#📅 Etap 9: Finalizacja i Dokumentacja (1-2 dni)#

✅ Cel: Przygotowanie aplikacji do prezentacji i dalszego rozwoju
🔹 Dodanie komentarzy w kodzie
🔹 Tworzenie README.md z opisem działania
🔹 Przetestowanie wszystkich funkcji


**⏳ Czas całkowity: ~16-24 dni**