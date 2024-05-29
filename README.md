# Lan Party 

## Descriere

LAN Party este o soluție software creată pentru organizarea și gestionarea evenimentelor LAN organizate de către Facultatea de Automatică și Calculatoare prin LSAC. În fiecare semestru, această facultate organizează un LAN Party la care participă toți studenții interesați de jocurile video și care doresc să își testeze abilitățile în cadrul unui mediu competitiv.
Aplicația are ca scop automatizarea procesului de organizare a acestui eveniment, facilitând înregistrarea echipelor și a jucătorilor, gestionarea meciurilor și a scorurilor, precum și generarea unui top al echipelor câștigătoare. Cu ajutorul acestei soluții software, organizatorii pot gestiona eficient competițiile și pot oferi o experiență mai bună participanților.

## Conținut

- [Utilizare](#utilizare)
- [Structuri de Date](#structuri-de-date)
- [Task 1: Gestionarea Echipelor](#task-1-gestionarea-echipelor)
- [Task 2: Eliminarea Echipelor](#task-2-eliminarea-echipelor)
- [Task 3: Meciuri și Scoruri](#task-3-meciuri-și-scoruri)
- [Task 4: Generarea Topului de Echipe](#task-4-generarea-topului-de-echipe)
- [Task 5: Implementarea Structurii AVL a Topului Echipelor](#task-5-implementarea-structurii-avl-a-topului-echipelor)

## Utilizare 
Programul poate fi compilat ruland in terminal comanda `./checker.sh`. Totodata daca se doreste compilarea unui singur set de date se foloseste comanda `make build` care creaza executabilul lanParty cu ajutorul Makefile-ului ,iar apoi comanda `./lanParty c.in d.in r.out`, unde c.in si d.in sunt fisierele de input de unde sunt citite datele si r.out reprezinta fisierul in care vom scrie.

## Structuri de Date
### `typedef struct player`
Structura `Player` reprezintă un jucător individual , avand următoarele atribute:

`firstName`: Un pointer către un șir de caractere (string) care reprezintă prenumele jucătorului.
`secondName`: Un pointer către un șir de caractere (string) care reprezintă numele de familie al jucătorului.
`points`: Un număr întreg care reprezintă punctele marcate de jucător.

### `typedef struct team`
Structura `Team` reprezintă o echipă ce poate la parte la turneu și include următoarele atribute:

`nr_players`: Un număr întreg care reprezintă numărul de jucători din echipă.
`teamName`: Un pointer către un șir de caractere (string) care reprezintă numele echipei.
`players`: Un pointer către un array de structuri Player, reprezentând lista de jucători din echipă.
`scoreTeam`: Un număr cu virgulă mobilă care reprezintă scorul echipei.

### `typedef struct node`
Structura `node` reprezinta un nod al listei de echipe ce urmeaza a fi creata, unde fiecare nod conține:

`team`: O structură Team reprezentând o echipă.
`next`: Un pointer către următorul nod din lista înlănțuită.

### `typedef struct match`
Structura Match reprezintă un meci între două echipe, continand doua structuri de tip `Team` ,respectiv echipele  `team1` si `team2` 

### `typedef struct nodeQueue`
Structura `NodeQueue` este destinată a fi utilizată într-o coadă  de meciuri, reprezentand un nod din coada de meciuri si  conținand:

`game`: O structură `Match` reprezentând un meci între două echipe.
`next`: Un pointer către următorul nod din coada de meciuri.

### `typedef struct teamQueue`
Structura `TeamQueue` reprezinta o coadă  de meciuri, gestionată prin pointeri către începutul și sfârșitul cozii.

## Task 1: Gestionarea Echipelor

### Descriere task
Acest task este responsabil pentru gestionarea echipelor participante la LAN Party, includzând funcționalități precum:

### `number_teams(char *nameFile)`

Această funcție primește numele fișierului de intrare și returnează numărul total de echipe din fișier.

### `FileInfo(char *nameFile)`

Această funcție primește numele fișierului de intrare și returnează un vector de structuri `Team`, care conțin informații despre fiecare echipă.

### `addTeams(char *nameFile, TeamName **teamList)`

Această funcție primește numele fișierului de intrare și o referință către o listă de echipe. Ea utilizează funcțiile `number_teams` și `FileInfo` pentru a adăuga echipele în lista specificată.

### `writeTeamList(char *InfoFile, char *nameFile)`

Această funcție primește numele fișierului de informații despre echipe și numele fișierului în care se va scrie lista de echipe. Ea utilizează funcția `addTeams` pentru a obține lista de echipe și scrie aceste informații în fișierul specificat.

## Funcții pentru Gestionarea Fișierelor

Aceste funcții sunt responsabile pentru gestionarea deschiderii și citirii fișierelor. Ele oferă funcționalități precum verificarea corectitudinii deschiderii fișierului, citirea valorilor din fișier.

### `verifyOpeningFile(FILE *fp)`

Această funcție primește un pointer către un fișier și verifică dacă acesta a fost deschis cu succes. În cazul în care fișierul nu poate fi deschis, funcția afișează un mesaj de eroare și închide fișierul.

### `int *Readtasks(FILE *fp)`

Această funcție primește un pointer către un fișier și citește din fisierul c.in in care se afla taskurile ce trebuie compilate, ea returneaza un vector de 1 si 0, unde 1 sugereaza ca taskul pozitiei i trebuie compilat ,iar 0 sugereaza ca taskul nu trebuie compilat.

### `int sumTasks(int *tasks)`

Această funcție primește un vector de întregi și calculează suma tuturor valorilor din acesta. Returnează suma calculată, respectiv numaerul taskului ce trebuie compilat.

### `FILE *openFile(char *nameFile)`

Această funcție primește numele unui fișier și încearcă să deschidă fișierul respectiv în modul de citire ("r"). Ea utilizează funcția `verifyOpeningFile` pentru a verifica corectitudinea deschiderii fișierului și returnează un pointer către fișier deschis.

## Task 2: Eliminarea Echipei 

### Descriere task
Acest task implică eliminarea echipei cu cel mai mic scor dintr-o listă de echipe și salvarea rezultatelor actualizate într-un fișier.

### `float score(Team team)`

Această funcție primește o echipă și calculează scorul mediu al acesteia pe baza punctajelor jucătorilor. Este utilizată pentru a determina echipa cu cel mai mic scor.

### `int nTeamsEliminated(int nr_teams)`

Această funcție primește numărul total de echipe și returnează numărul de echipe care trebuie eliminate într-o rundă de eliminare, în conformitate cu regulile LAN Party-ului.

### `float minScore(TeamName *team)`

Această funcție primește o listă de echipe și determină scorul minim din această listă, parcurgând toate echipele și comparând scorurile lor.

### `FILE *task2EliminateTeam(char *InfoFile, char *FileOutput, TeamName **teamlist, int nr_teams)`

Această funcție primește numele fișierului de informații despre echipe (`InfoFile`), numele fișierului de ieșire (`FileOutput`), lista de echipe și numărul total de echipe. Ea adaugă echipele în lista de echipe, determină numărul de echipe care trebuie eliminate, elimină echipele cu scorul minim și actualizează lista de echipe în consecință. Apoi, rezultatele actualizate sunt scrise în fișierul de ieșire.

## Task 3: Organizarea Meciurilor și Determinarea Echipelor Câștigătoare

### Descriere task
Această etapă a procesului implică organizarea meciurilor dintre echipe și determinarea echipelor câștigătoare, în funcție de rezultatele fiecărui meci.

### `void addGames(Match **game, TeamName *teamList, int nr_matches)`

Această funcție primește o listă de echipe și numărul total de meciuri, apoi creaza un vector de jocuri in care baga doua cate doua echipe.

### `void createQueueTeams(TeamQueue **teamQueue, TeamName *teamList, int nr_matches)`

Această funcție primește o listă de echipe și numărul total de meciuri și creează o  coada de meciuri pentru a gestiona meciurile.

### `void winnersVSlosers(FILE *fileInfo, TeamQueue *teamQueue, TeamName **stackWinner, TeamName **stackLoser, TeamName **topBest8, int *foundTop8)`

Această funcție primește coada de meciuri și gestionează meciurile, determinând echipele câștigătoare și pierzătoare în fiecare rundă si verifica daca a fost gasit topul celor 8 echipe.
Funcția parcurge coada de echipe (teamQueue) până când nu mai există meciuri programate.
Pentru fiecare meci, este extrasă prima echipă (firstTeam) și a doua echipă (secondTeam) din coadă.
Se compară scorurile echipelor și se decid echipele câștigătoare și pierzătoare

### `FILE *addMatch(char *inputFile, char *outputFile, int nr_matches, TeamName **WinnersList, TeamName *teamslist)`

Această funcție primește numele fișierului de intrare (`inputFile`), numele fișierului de ieșire (`outputFile`), numărul total de meciuri, lista de echipe și lista câștigătorilor. Ea organizează meciurile și actualizează lista câștigătorilor, scriind rezultatele în fișierul de ieșire.
Se creează o coadă de echipe (Q) pentru a planifica meciurile și a le organiza în rundele competiției, apoi folosind functia (`winnersVSlosers`) se inițializează lista stackwinners, stacklossers și topBest8 pentru a stoca temporar echipele câștigătoare, echipele pierzătoare și primele 8 echipe din competiție.
Se parcurge coada de echipe (Q) până când nu mai există meciuri programate sau până când s-au jucat toate meciurile din competiție (i < nr_matches / 2).
#### Pentru fiecare rundă:
##### Se determină câștigătorii și pierzătorii rundei folosind funcția winnersVSlosers.
##### Se afișează lista câștigătorilor rundei în fișier.
##### Se actualizează coada de echipe (Q) pentru următoarea rundă, ștergând echipele care au fost eliminate și reducând numărul de meciuri programate la jumătate.
##### Se actualizează lista WinnersList cu primele 8 echipe din competiție, dacă acestea nu au fost încă găsite.La final, se șterg toate echipele din lista teamslist, deoarece competiția s-a încheiat și nu mai sunt necesare.

### Task 4: Binary Search Tree (BTS) (Generarea Topului de Echipe)

### `void task4BTS(char *outputfile, char *inputfile, NodeBTS **topWinners)`
Gestionează BTS-ul pentru echipele cu cele mai bune performanțe,salvate anterior int WinnersList. Funcția construiește și afișează un arbore de căutare binară (BTS) ce conține cele mai bune 8 echipe, 
bazat pe performanța acestora, salvate in taskul anterior intr-o lista. Fișierul de ieșire este actualizat cu aceste informații, iar procesul se încheie prin închiderea fișierului de ieșire. Această funcție oferă un instrument eficient pentru 
gestionarea și prezentarea rezultatelor importante ale unui turneu într-un format ușor de înțeles și de utilizat.

### Task 5: Conversia BTS la AVL și Afișarea Nivelului 2

### `void task4BTS(char *outputfile, char *inputfile, NodeBTS **topWinners)`

Această funcție urmărește să organizeze echipele câștigătoare din BTS într-un arbore AVL și să afișeze echipele de pe nivelul 2.
Prin utilizarea unui arbore AVL, echipele sunt stocate într-o structură de date echilibrată, facilitând căutarea și afișarea ordonată a acestora. 
Rezultatele sunt scrise într-un fișier de ieșire, oferind o vizualizare clară a echipelor de pe nivelul 2.





