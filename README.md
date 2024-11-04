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

**Tydzień 1–2: Rozpoczęcie projektu**

•	**Cel**: Zapoznanie się z wymaganiami projektu, ustalenie użytych technologii.

•	**Zadania**:

•	Zainstalowanie SFML i FFT.

•	Skonfigurowanie środowiska programistycznego (VS Code/CMake).

•	Przetestowanie prostego projektu w SFML (np. otwarcie okna).

**Tydzień 3–4: Obsługa dźwięku**

•	**Cel**: Wczytanie i odtwarzanie plików audio.

•	**Zadania**:

•	Wczytanie pliku audio MP3/WAV przy użyciu SFML (sf::SoundBuffer i sf::Sound).

•	Odtwarzanie dźwięku w aplikacji.

•	Testowanie różnych formatów plików audio.

**Tydzień 5–6: Analiza dźwięku – FFT**

•	**Cel**: Implementacja FFT do analizy częstotliwości dźwięku.

•	**Zadania**:

•	Integracja wybranej biblioteki FFT z projektem.

•	Implementacja podstawowej analizy FFT na próbkach dźwięku.

•	Wyświetlanie wyników FFT w konsoli (dla weryfikacji poprawności).

**Tydzień 7–8: Podstawowa wizualizacja**

•	**Cel**: Stworzenie podstawowej wizualizacji wyników FFT.

•	**Zadania**:

•	Implementacja prostej wizualizacji (np. słupki dla różnych pasm częstotliwości).

•	Synchronizacja dźwięku z wizualizacją.

•	Testowanie wydajności i płynności animacji.

**Tydzień 9–10: Rozbudowa wizualizacji**

•	**Cel**: Uatrakcyjnienie wizualizacji, dodanie efektów.

•	**Zadania**:

•	Dodanie kolorów i animacji do wizualizacji (np. dynamicznie zmieniające się kolory w zależności od intensywności dźwięku).

•	Implementacja różnych typów wizualizacji (np. fale, okręgi, sinusoidy).

•	Testowanie różnych plików audio i optymalizacja wydajności.

**Tydzień 11–12: Interaktywność i kontrola**

•	**Cel**: Dodanie funkcji interaktywnych.

•	**Zadania**:

•	Implementacja sterowania klawiaturą (zmiana trybu wizualizacji, pauza, wybór pliku audio).

•	Dodanie suwaków lub innych elementów GUI (np. czułość wizualizacji, szybkość animacji).

•	Optymalizacja wielowątkowości (jeśli potrzebne).

**Tydzień 13–14: Testy i finalizacja projektu**

•	**Cel**: Testowanie, optymalizacja i przygotowanie do prezentacji.

•	**Zadania**:

•	Testowanie projektu na różnych urządzeniach i systemach operacyjnych.

•	Debugowanie i poprawki kodu (wydajność, synchronizacja).

•	Przygotowanie dokumentacji projektu (opis, instrukcja obsługi).

•	Przygotowanie projektu do prezentacji (np. wgranie na GitHub, przygotowanie slajdów).

**Tydzień 15–16: Prezentacja i ewaluacja**

•	**Cel**: Prezentacja gotowego projektu.

•	**Zadania**:

•	Finalna prezentacja projektu na zajęciach.

•	Zbiór opinii i ewaluacja projektu.

•	Dalsze poprawki (jeśli potrzebne) na podstawie feedbacku.

**Wskazówki**

•	Każde spotkanie co dwa tygodnie powinno zakończyć się przeglądem postępu z prowadzącym i dyskusją na temat ewentualnych problemów technicznych.

•	Testuj projekt regularnie, aby unikać problemów z wydajnością lub błędami w późniejszych etapach.