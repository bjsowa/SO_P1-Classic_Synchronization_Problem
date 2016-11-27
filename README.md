# SO_P1-Classic_Synchronization_Problem

# Drinking Philosophers Problem

Jest to uogólnienie Problemu Ucztujących Filozofów.
Filozofowie siedzą przy okrągłym stole. Pomiędzy każdym z nich leżą butelki z trunkiem (butelki mają przypisane miejsca). Każdy filozof jest w jednym z trzech stanów: (1) śpiący, (2) spragniony, albo (3) pijący. Mogą oni pić tylko z butelek przypisanych do miejsc po ich lewej albo prawej stronie. Śpiący filozof po obudzeniu jest spragniony. Spragniony filozof wybiera sobie niepusty zbiór butelek, z których chce się napić, ale może zacząć pić tylko jeśli ma wszystkie wymagane butelki. Pozostaje w stanie pijącym przez skończoną ilość czasu, po czym zasypia na skończoną ilość czasu. Sąsiadujący filozofowie mogą wysyłać miedzy sobą wiadomości (wysłanie zajmuje pewną skończoną ilość czasu). Butelki także mogą być wysyłane.

# Problem

Problem polega na tym, aby opracować nieprobabilistyczne rozwiązanie spełniające ograniczenia:
- żaden z filozofów nie może pozostać spragniony na zawsze
- wszyscy przestrzegają tych samych zasad w zdobywaniu i oddawaniu butelek. Nie ma ustalonych priorytetów
- filozofowie wysyłają i otrzymują skończoną ilość wiadomości pomiędzy zmianami stanu
- rozwiązanie ma pozwolić na picie kilku filozofom na raz jeśli to możliwe

