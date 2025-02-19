#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))



void lookForMatches(int x, int y, char** map, int* height, int width, char** matches_in_dir);
void markMatches(int x, int y, char** map, char** matches_in_dir, int* lowest_gap_closer_ptr);
int fallInArea(int xl, int xr, int y, char** map, int* height, int* lowest_replace);



int main(int argc, char *argv[]) {

    // Eingabe:
    int line_count = 0;
    int min_column = 0;
    int max_column = 0;

    char* colour = malloc(sizeof(char));
    if (colour == NULL) {
        fprintf(stderr, "Allokationsfehler");
        return 1;
    }
    int* column = malloc(sizeof(int));
    if (column == NULL) {
        fprintf(stderr, "Allokationsfehler");
        return 1;
    }

    char* line_str = malloc(sizeof(char));
    if (line_str == NULL) {
        fprintf(stderr, "Allokationsfehler");
        return 1;
    }
    char* num_str = malloc(sizeof(char));
    if (num_str == NULL) {
        fprintf(stderr, "Allokationsfehler");
        return 1;
    }

    while (1) {

        // while-Schleife liest einzelne Zeichen von stdin ins String line_str bis zum Zeilen-
        // oder Dateiende. length bezeichnet die Länge von line_str
        int length = 0;
        char c;
        while (1) {
            c = getchar();

            line_str = realloc(line_str, (length+1)*sizeof(char));
            if (line_str == NULL) {
                fprintf(stderr, "Allokationsfehler");
                free(colour);
                free(column);
                free(line_str);
                free(num_str);
                return 1;
            }

            line_str[length] = c;
            ++length;

            if (c == '\n' || c == EOF || c == 13)
                break;
        }

        if (line_str[0] == EOF) {
            //Leere Eingabe ist gültig: Erzeugt leere Ausgabe.
            if (line_count == 0) {
                free(colour);
                free(column);
                free(line_str);
                free(num_str);
                return 0;
            }

            break;
        }


        // Zeile muss mit Ziffer beginnen
        if (line_str[0] < '0' || '9' < line_str[0]) {
            fprintf(stderr, "Fehlerhafte Eingabe");
            free(colour);
            free(column);
            free(line_str);
            free(num_str);
            return 1;
        }
        

        // Führende Nullen abzählen:
        int i = 0;
        while (line_str[i] == '0') {
            ++i;
        }
        int first_non_zero = i;

        while ('0' <= line_str[i] && line_str[i] <= '9') {
            ++i;
        }

        // Ist die Anzahl der nicht-Nullen größer als 3, so kann die eingegebene Zahl nicht im
        // Bereich [0,254] liegen.
        if (i-first_non_zero > 3 || line_str[i] != ' ') {
            fprintf(stderr, "Fehlerhafte Eingabe: erste Zahl nicht in erlaubtem Wertebereich.");
            free(colour);
            free(column);
            free(line_str);
            free(num_str);
            return 1;
        }

        // Farbe wird als int eingelesen, um Wertebereich zu überprüfen
        int int_colour = atoi(line_str);
        if (int_colour < 0 || int_colour > 254) {
            fprintf(stderr, "Fehlerhafte Eingabe: erste Zahl nicht in erlaubtem Wertebereich.");
            free(colour);
            free(column);
            free(line_str);
            free(num_str);
            return 1;
        }

        // Trennende Leerzeichen zwischen Zahlen werden akzeptiert.
        while (line_str[i] == ' ') {
            ++i;
        }

        // Nach den Leerzeichen muss eine Ziffer oder ein Minus-Zeichen stehen.
        if (line_str[i] != '-' && (line_str[i] < '0' || '9' < line_str[i])) {
            fprintf(stderr, "Fehlerhafte Eingabe");
            free(colour);
            free(column);
            free(line_str);
            free(num_str);
            return 1;
        }

        // String num_str enthält die zweite Zahl, inklusive eines möglichen Minuszeichen und
        // führender Nullen. Es wird in den verschiedenen Abschnitte (führende Nullen, Rest)
        // iteriert und num_str mithilfe von line_str und realloc gefüllt.
        num_str[0] = line_str[i];
        int i0 = i;
        if (num_str[0] == '-' || num_str[0] == '0') {
            ++i;
            // Um die Anzahl der Ziffern hinter den führenden Nullen in der zweiten Zahl zu
            // berechnen, müssen die führenden Nullen iteriert werden.
            while (line_str[i] == '0') {
                num_str = realloc(num_str, (i-i0+1)*sizeof(char));
                if (num_str == NULL) {
                    fprintf(stderr, "Allokationsfehler");
                    return 1;
                }

                num_str[i-i0] = line_str[i];
                ++i;
            }

            first_non_zero = i;
        }
        else {
            first_non_zero = i;
            ++i;
        }

        while (line_str[i] >= '0' && line_str[i] <= '9') {
            // zweite Zahl soll im Bereich [-2^20,2^20] liegen, darf also maximal 7 Stellen haben
            if (i-first_non_zero > 6) {
                fprintf(stderr, "Fehlerhafte Eingabe: zweite Zahl nicht in erlaubtem Wertebereich.");
                free(colour);
                free(column);
                free(line_str);
                free(num_str);
                return 1;
            }
            num_str = realloc(num_str, (i-i0+1)*sizeof(char));
            if (num_str == NULL) {
                fprintf(stderr, "Allokationsfehler");
                return 1;
            }

            num_str[i-i0] = line_str[i];
            ++i;
        }

        num_str = realloc(num_str, (i-i0+1)*sizeof(char));
        if (num_str == NULL) {
            fprintf(stderr, "Allokationsfehler");
            return 1;
        }
        num_str[i-i0] = 0;

        // Zahl wird aus num_str eingelesen, darf betragsmäßig nicht größer sein als 2^20
        int x_coord = atoi(num_str);
        if (abs(x_coord) > 1048576) {
            fprintf(stderr, "Fehlerhafte Eingabe: zweite Zahl nicht in erlaubtem Wertebereich.");
            free(colour);
            free(column);
            free(line_str);
            free(num_str);
            return 1;
        }

        // Ist der Index nicht am String-Ende angekommen, so kommen nach der zweiten Zahl
        // noch weitere Zeichen, was unerlaubt ist.
        if (i != length-1) {
            fprintf(stderr, "Fehlerhafte Eingabe");
            free(colour);
            free(column);
            free(line_str);
            free(num_str);
            return 1;
        }



        // Die Speicherblöcke colour und column werden reallokiert,
        // eingelesene Inhalte gespeichert.

        colour = realloc(colour, (line_count+1)*sizeof(char));
        if (colour == NULL) {
            fprintf(stderr, "Allokationsfehler");
            free(colour);
            free(column);
            free(line_str);
            free(num_str);
            return 1;
        }
        column = realloc(column, (line_count+1)*sizeof(int));
        if (column == NULL) {
            fprintf(stderr, "Allokationsfehler");
            free(colour);
            free(column);
            free(line_str);
            free(num_str);
            return 1;
        }

        colour[line_count] = (char) int_colour;
        column[line_count] = x_coord;

        // Um die Breite des Spielbereichs zu berechnen müssen der niedrigste und höchste
        // Spaltenindex berechnet werden.
        if (line_count == 0) {
            min_column = x_coord;
            max_column = x_coord;
        }
        else {
            if (x_coord < min_column)
                min_column = x_coord;
            if (x_coord > max_column)
                max_column = x_coord;
        }

        ++line_count;
        if (c == EOF)
            break;
    }

    free(line_str);
    free(num_str);




    // width ist die horizontale Breite des (zusammenhängenden) relevanten Spielbereichs
    int width = max_column-min_column+1;

    int* height = malloc(width*sizeof(int));
    if (height == NULL) {
        fprintf(stderr, "Allokationsfehler");
        return 1;
    }
    char **map = malloc(width*sizeof(char*));
    if (map == NULL) {
        fprintf(stderr, "Allokationsfehler");
        return 1;
    }

    // map[x][y] enthält die Farbe des an den Koordinaten (x+min_column,y) liegenden Steins,
    // height[x] enthält die Anzahl der in Spalte x+min_column liegenden Steine.
    for (int x=0; x<width; x++) {
        height[x] = 0;
        map[x] = malloc(sizeof(char));
        if (map[x] == NULL) {
            fprintf(stderr, "Allokationsfehler");
            return 1;
        }
    }




    // Abarbeitung des Spielplans (Zeile um Zeile):

    for (int row=0; row<line_count; row++) {
        int x = column[row]-min_column;
        char col = colour[row];
        int y = height[x];

        // Der Block der Farbe colour[row] landet ganz oben auf dem Stapel in Spalte x:
        map[x][y] = col;

        height[x] ++;
        map[x] = realloc(map[x], (height[x]+1)*sizeof(char));
        if (map[x] == NULL) {
            fprintf(stderr, "Allokationsfehler");
            return 1;
        }



        // 3x3-Matrix matches_in_dir wie in der Funktion lookForMatches
        char** matches_in_dir = malloc(3*sizeof(char*));
        if (matches_in_dir == 0) {
            fprintf(stderr, "Allokationsfehler");
            return 1;
        }
        for (int xx=0; xx<3; xx++) {
            matches_in_dir[xx] = malloc(3*sizeof(char));
            if (matches_in_dir[xx] == NULL) {
                fprintf(stderr, "Allokationsfehler");
                return 1;
            }
        }

        // In der Umgebung von (x,y) werden Steinlinien gleicher Farbe identifiziert, die
        // Informationen in Matrix matches_in_dir abgelegt.
        lookForMatches(x, y, map, height, width, matches_in_dir);


        int lowest_gap_closer = INT_MAX;
        // markMatches ersetzt die zuvor erkannten Steinlinien um (x,y) in map durch -1
        // In lowest_gap_closer wird in diesem Fall nur y abgelegt.
        markMatches(x, y, map, matches_in_dir, &lowest_gap_closer);


        free(matches_in_dir[0]);
        free(matches_in_dir[1]);
        free(matches_in_dir[2]);
        free(matches_in_dir);



        // am weitesten linke Spalte des Bereichs, in dem möglicherweise Blöcke ersetzt werden
        int xl = MAX(x-3, 0);
        // am weitesten rechte Spalte des Bereichs, in dem möglicherweise Blöcke ersetzt werden
        int xr = MIN(x+3, width-1);
        // Breite des Bereichs, in dem möglicherweise Blöcke ersetzt werden = "aktiver Bereich"
        int n_columns = xr-xl+1;

        int* lowest_replace = malloc(n_columns*sizeof(int));
        if (lowest_replace == NULL) {
            fprintf(stderr, "Allokationsfehler");
            return 1;
        }
        // fallInArea ersetzt die mit -1 markierten Blöcke im aktiven Bereich ab einer Mindesthöhe
        // durch nachrutschende Steine. Rückgabewert something_fell ist 0, wenn nichts rutschte,
        // sonst 1. lowest_replace[x-xl] wird mit der Höhe des niedrigsten ersetzten Stein in Spalte x
        // beschrieben.
        int something_fell = fallInArea(xl, xr, MAX(y-3,0), map, height, lowest_replace);






        while (something_fell) {

            // match_array kann als Matrix, deren Einträge Matrizen der Art matches_in_dir sind,
            // verstanden werden. Für jede Spalte i=xx-xl im aktiven Bereich gibt es l solche
            // "matches_in_dir", wobei l=height[xl+i]-lowest_replace[i], das heißt die Anzahl der
            // Blöcke über dem ersten nachgerutschten Block. match_array[i][j] bezeichnet dann
            // die "matches_in_dir"-Matrix für Block (i+xl,j+lowest_replace[i]).

            char**** match_array = malloc(n_columns*sizeof(char***));
            if (match_array == NULL) {
                fprintf(stderr, "Allokationsfehler");
                return 1;
            }

            int l;
            for (int i=0; i<n_columns; i++) {
                l = height[xl+i]-lowest_replace[i];
                match_array[i] = malloc(l*sizeof(char**));
                if (match_array[i] == NULL) {
                    fprintf(stderr, "Allokationsfehler");
                    return 1;
                }

                for (int j=0; j<l; j++) {
                    match_array[i][j] = malloc(3*sizeof(char*));
                    if (match_array[i][j] == NULL) {
                        fprintf(stderr, "Allokationsfehler");
                        return 1;
                    }

                    for (int k=0; k<3; k++) {
                        match_array[i][j][k] = malloc(3*sizeof(char));
                        if (match_array[i][j][k] == NULL) {
                            fprintf(stderr, "Allokationsfehler");
                            return 1;
                        }
                    }
                }
            }



            // Steine im aktiven Bereich werden iteriert und um sie mit lookForMatches
            // die Längen gleichfarbiger Linien durch sie ermittelt und gespeichert in
            // der "matches_in_dir"-Matrix match_array[xx-xl][yy-lowest_replace[xx-xl]].
            for (int xx=xl; xx<=xr; xx++) {
                for (int yy=lowest_replace[xx-xl]; yy<height[xx]; yy++) {
                    lookForMatches(xx, yy, map, height, width, match_array[xx-xl][yy-lowest_replace[xx-xl]]);
                }
            }

            // Wieder werden Steine im aktiven Bereich iteriert und in ihrer Umgebung werden
            // anhand der Informationen in der jeweiligen "matches_in_dir"-Matrix Steinfarben
            // durch -1 ersetzt, also Blöcke als leer markiert.
            // In lowest_gap_closer wird die Höhe des tiefsten gerade zuvor gefallenen Steins, der
            // gelöscht wird, gespeichert.
            int lowest_gap_closer = INT_MAX;
            for (int xx=xl; xx<=xr; xx++) {
                for (int yy=lowest_replace[xx-xl]; yy<height[xx]; yy++) {
                    markMatches(xx, yy, map, match_array[xx-xl][yy-lowest_replace[xx-xl]], &lowest_gap_closer);
                }
            }


            // match_array wird nicht mehr benötigt, also deallokiert.
            for (int i=0; i<n_columns; i++) {
                for (int j=0; j<height[xl+i]-lowest_replace[i]; j++) {
                    for (int k=0; k<3; k++) {
                        free(match_array[i][j][k]);
                    }
                    free(match_array[i][j]);
                }
                free(match_array[i]);
            }
            free(match_array);



            // Der aktive Bereich wird neu vermessen, dazu xl und xr verschoben:
            // lowest_replace[xx-xl] >= height[xx], wenn in Spalte xx keine Steine
            // nachgerutscht sind.
            // xl wird also auf die am weitesten rechts liegende Spalte gesetzt, in der ein Stein
            // nachrutschte, xr analog.
            int xx = xl;
            while (lowest_replace[xx-xl] >= height[xx] && xx < xr) {
                ++xx;
            }
            int tmp = xx;
            xx = xr;
            while (lowest_replace[xx-xl] >= height[xx] && xx > xl) {
                --xx;
            }
            xl = MAX(tmp-3, 0);
            xr = MIN(xx+3, width-1);

            n_columns = xr-xl+1;

            // Der Speicherblock, auf den lowest_replace zeigt, wird auf die neue Breite des
            // aktiven Bereichs reallokiert.
            lowest_replace = realloc(lowest_replace, n_columns*sizeof(int));
            if (lowest_replace == NULL) {
                fprintf(stderr, "Allokationsfehler");
                return 1;
            }

            // Im aktiven Bereich werden -1en durch Nachrutscher ersetzt. Von something_fell
            // hängt ab, ob der Programmblock in der Schleife nochmal durchgeführt wird.
            something_fell = fallInArea(xl, xr, MAX(lowest_gap_closer-3, 0), map, height, lowest_replace);

        }

        free(lowest_replace);

    }

    free(colour);
    free(column);



    // Ausgabe: (cast auf unsigned char für Farbbereich [0,254])
    
    for (int x=0; x<width; x++) {
        for (int y=0; y<height[x]; y++) {
            printf("%d %d %d\n", (unsigned char) map[x][y], x+min_column, y);
        }
        free(map[x]);
    }
    free(map);
    free(height);

    return 0;
    
}


void lookForMatches(int x, int y, char** map, int* height, int width, char** matches_in_dir) {
    // Sucht in 8 Richtungen (Nord, Nordwest, West,...) um den Stein der Position (x,y) in map
    // nach gleichfarbigen Steinen. Es wird so lang gesucht, bis auf einen andersfarbigen Stein
    // oder an das Ende von map gestoßen wird. In matches_in_dir[1+x_dir][1+y_dir] wird die Anzahl
    // der so in Richtung (x_dir,y_dir) gefundenen zusammenhängenden gleichfarbigen Steine
    // eingetragen.

    char col = map[x][y];

    int s;
    int x_new, y_new;

    // for-Schleifen iterieren die 8 Richtungen in Reihenfolge (-1,-1), (-1,0), (-1,1), (0,-1),
    // (0,1), (1,-1), (1,0), (1,1)

    for (int x_dir=-1; x_dir<2; x_dir++) {
        for (int y_dir=-1; y_dir<2; y_dir+=2-abs(x_dir)) {
            s = 1;
            while (1) {
                x_new = x+s*x_dir;
                y_new = y+s*y_dir;
                if (x_new < 0 || x_new >= width || y_new < 0 || y_new >= height[x_new] ||  map[x_new][y_new] != col || s > 3)
                    break;
                ++s;
            }
            matches_in_dir[1+x_dir][1+y_dir] = s-1;
        }
    }

    return;
}

void markMatches(int x, int y, char** map, char** matches_in_dir, int* lowest_gap_closer_ptr) {
    // Ersetzt mithilfe von matches_in_dir identifizierte gleichfarbige Steine um die Koordinate
    // (x+min_column,y) mit der Nicht-Farbe -1 (char), markiert sie also als gelöscht.

    for (int x_dir=-1; x_dir<1; x_dir++) {
        for (int y_dir=-1; y_dir<2; y_dir+=2-abs(x_dir)) {
            if (matches_in_dir[1+x_dir][1+y_dir] + matches_in_dir[1-x_dir][1-y_dir] >= 3) {
                map[x][y] = -1;
                *lowest_gap_closer_ptr = MIN(y, *lowest_gap_closer_ptr);
                for (int s=1; s<=matches_in_dir[1+x_dir][1+y_dir]; s++) {
                    map[x+s*x_dir][y+s*y_dir] = -1;
                }
                for (int s=1; s<=matches_in_dir[1-x_dir][1-y_dir]; s++)
                    map[x-s*x_dir][y-s*y_dir] = -1;
            }
        }
    }

    return;
}

int fallInArea(int xl, int xr, int y_min, char** map, int* height, int* lowest_replace) {
    // Lässt die Lücken ("Steine" der Farbe -1) im horizontalen Bereich [xl,xr] von map durch 
    // höherliegende Steine schließen, d.h. simuliert das Fallen.
    // Zur Beschleunigung werden nur Steine ab einer Mindesthöhe y_min berücksichtigt.

    // Der Rückgabewert something_fell ist 1, wenn in einer Spalte ein Block eine Lücke ersetzt
    // hat und sonst 0.
    int something_fell = 0;

    int falls;
    for (int x=xl; x<=xr; x++) {
        lowest_replace[x-xl] = height[x];
        falls = 0;

        // Steine von y_min bis zum obersten Stein der Spalte werden iteriert. Ist ein Block mit
        // -1 markiert, so steigt die Rutschhöhe (falls) aller nachfolgenden Blöcke um 1 an.
        // Hat zum Beispiel der map[x][y]=14 und falls=3, wird an map[x][y-3] die Farbe 14
        // eingetragen.
        for (int y=y_min; y<height[x]; y++) {
            map[x][y-falls] = map[x][y];
            if (map[x][y] == -1) {
                // lowest_replace[x-xl] bezeichnet die Höhe der niedrigsten Lücke.
                if (falls == 0)
                    lowest_replace[x-xl] = y;
                ++ falls;
            }
        }
        
        // Die Höhe einer Spalte muss entsprechend der letzten Fallhöhe herabgesetzt werden.
        height[x] -= falls;

        // So wird geprüft, ob wirklich eine Lücke durch einen farbigen Block ersetzt wurde (und
        // sich nicht etwa nur der höchste Block der Spalte map[x] aufgelöst hat).
        if (lowest_replace[x-xl] < height[x])
            something_fell = 1;
    }

    return something_fell;
}
