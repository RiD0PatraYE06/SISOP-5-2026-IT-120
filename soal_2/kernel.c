int cursor = 0;
char color = 0x07;

void putInMemory(int segment, int address, char character);
int getChar();

/*
 * Final Challenge
 *
 * Commands:
 * - check
 * - add <a> <b>
 * - sub <a> <b>
 * - fac <n>
 * - season <name>
 * - triangle <n>
 * - clear
 * - about
 *
 * Season list:
 * - winter
 * - spring
 * - summer
 * - fall
 * - radiant
 *
 * Restrictions:
 * - no stdlib
 * - avoid division (/)
 * - avoid modulo (%)
 */

/*
 * TODO:
 * 1. printChar()       v
 * 2. printString()     v
 * 3. clearScreen()     v
 * 4. readString()      v
 * 5. strcmp()          v
 * 6. startsWith()      v
 * 7. atoi()            v
 * 8. intToString()     v
 * 9. factorial()       v
 * 10. add handler
 * 11. sub handler
 * 12. fac handler
 * 13. season handler
 * 14. triangle handler
 * 15. shell loop
 */


// 1. DEKLARASI / PROTOTIPE FUNGSI (Agar main() kenal)
void putInMemory(int segment, int address, char character);
int getChar();
void printChar(char character);
void printString(char* string);
void clearScreen();
void readString(char* string);
int strcmp(char* str1, char* str2);
void newline();
void updateCursor(int cursor_pos); // <--- Tambahkan ini di baris deklarasi atas
int startsWith(char* str, char* prefix);
int atoi(char* str);
void intToString(int num, char* str);
int factorial(int n);


// 2. FUNGSI UTAMA (Wajib Paling Atas agar Sukses Booting)
void main() {

    char cmd[64];

    clearScreen();

    // Sesuaikan dengan ucapan dari Asisten Praktikum di gambar
    printString("Welcome to Assistant's Last Gift");
    newline();

    printString("type 'help'");
    newline();
    newline();

    while (1) {

        printString("> ");

        readString(cmd);

        /*
         * TODO:
         * command handler
         *
         * example:
         *
         * if (strcmp(cmd, "check")) {
         *     printString("ok");
         * }
         */

        // --- TODO: command handler untuk 'check' ---
        if (strcmp(cmd, "check")) {
            printString("ok");
            newline();
        } 
        // --- Handler Perintah 'help' [SUDAH DIPERBARUI] ---
        else if (strcmp(cmd, "help")) {
            printString("check add sub fac season triangle clear about");
            newline();
        }
        else if (startsWith(cmd, "add ")) {
            char* arg1 = cmd + 4; // Menunjuk ke awal angka pertama
            char* arg2 = 0;
            int i = 4;
            int num1, num2, hasil;
            char hasilStr[16];

            // Cari spasi pemisah antara angka pertama dan kedua
            while (cmd[i] != '\0') {
                if (cmd[i] == ' ') {
                    cmd[i] = '\0'; // Potong string di sini agar arg1 hanya membaca angka pertama
                    arg2 = cmd + i + 1; // Angka kedua dimulai setelah spasi
                    break;
                }
                i++;
            }

            if (arg2 != 0) {
                num1 = atoi(arg1);
                num2 = atoi(arg2);
                hasil = num1 + num2;

                intToString(hasil, hasilStr);
                printString(hasilStr);
                newline();
            } else {
                printString("Error: Format salah. Gunakan 'add <a> <b>'");
                newline();
            }
        }
        else if (startsWith(cmd, "sub ")) {
            char* arg1 = cmd + 4; // Menunjuk ke awal angka pertama setelah "sub "
            char* arg2 = 0;
            int i = 4;
            int num1, num2, hasil;
            char hasilStr[16];

            // Cari spasi pemisah antara angka pertama dan kedua
            while (cmd[i] != '\0') {
                if (cmd[i] == ' ') {
                    cmd[i] = '\0'; // Potong string di spasi pemisah
                    arg2 = cmd + i + 1; // Angka kedua dimulai setelah spasi
                    break;
                }
                i++;
            }

            if (arg2 != 0) {
                num1 = atoi(arg1);
                num2 = atoi(arg2);
                hasil = num1 - num2; // Operasi Pengurangan

                intToString(hasil, hasilStr);
                printString(hasilStr);
                newline();
            } else {
                printString("Error: Format salah. Gunakan 'sub <a> <b>'");
                newline();
            }
        }
        else if (startsWith(cmd, "fac ")) {
            char* arg = cmd + 4; // Menunjuk ke angka setelah "fac "
            int n = atoi(arg);
            int hasil = factorial(n);
            char hasilStr[16];

            if (hasil == -1) {
                // Sesuai request asisten yang super chill di soal
                printString("know your limit little bro.");
                newline();
            } else {
                intToString(hasil, hasilStr);
                printString(hasilStr);
                newline();
            }
        }
        else if (startsWith(cmd, "season ")) {
            char* arg = cmd + 7; // Menunjuk ke nama musim setelah "season "

            if (strcmp(arg, "winter")) {
                color = 0x09; // Ubah warna global ke Biru Terang
                printString("winter mode");
                newline();
            } 
            else if (strcmp(arg, "spring")) {
                color = 0x0A; // Ubah warna global ke Hijau Terang
                printString("spring mode");
                newline();
            } 
            else if (strcmp(arg, "summer")) {
                color = 0x0E; // Ubah warna global ke Kuning Terang
                printString("summer mode");
                newline();
            } 
            else if (strcmp(arg, "fall")) {
                color = 0x06; // Ubah warna global ke Cokelat
                printString("fall mode");
                newline();
            } 
            else if (strcmp(arg, "radiant")) {
                color = 0x0D; // Ubah warna global ke Pink/Light Magenta
                printString("radiant mode");
                newline();
            } 
            else {
                printString("Musim tidak diketahui! Pilih: winter, spring, summer, fall, radiant");
                newline();
            }
        }
        else if (startsWith(cmd, "triangle ")) {
            char* arg = cmd + 9; // Menunjuk ke angka setelah "triangle "
            int n = atoi(arg);
            int i, j;

            // Proteksi jika input minus atau nol
            if (n <= 0) {
                printString("Error: Masukkan angka lebih dari 0.");
                newline();
            } else {
                // Loop luar untuk mengatur tinggi baris
                for (i = 1; i <= n; i++) {
                    // Loop dalam untuk mencetak karakter 'x' di baris tersebut
                    for (j = 1; j <= i; j++) {
                        printChar('x');
                    }
                    newline(); // Pindah baris setelah karakter 'x' di baris itu beres
                }
            }
        }
        // --- Handler Perintah 'clear' ---
        else if (strcmp(cmd, "clear")) {
            clearScreen();
        }
        // --- Handler Perintah 'about' ---
        else if (strcmp(cmd, "about")) {
            printString("OS: Assistant's Last Gift v1.0");
            newline();
            printString("Developer: Student of IT ITS");
            newline();
        }
        else {
            printString("Command tidak dikenali.");
            newline();
        }

    }
}


// 3. IMPLEMENTASI FITUR (TODO 1 - 5)
// TODO 1. PrintChar()
void printChar(char character) {
    putInMemory(0xB800, cursor * 2, character);      
    putInMemory(0xB800, (cursor * 2) + 1, color);    
    cursor++; 
    updateCursor(cursor); // <--- Selipkan di sini
}

// TODO 2. PrintString()
void printString(char* string) {
    int i = 0;
    while (string[i] != '\0') {
        printChar(string[i]);
        i++;
    }
}

// TODO 3. ClearScreen()
void clearScreen() {
    int i;
    for (i = 0; i < 2000; i++) {
        putInMemory(0xB800, i * 2, ' ');       
        putInMemory(0xB800, (i * 2) + 1, 0x07); 
    }
    cursor = 0; 
    updateCursor(cursor); // <--- Selipkan ini biar kursor fisik ikut reset ke (0,0) saat boot
}

// TODO 4. ReadString()
void readString(char* string) {
    int i = 0;
    while (1) {
        char ch = getChar(); 

        if (ch == 0x0D) { // Enter
            string[i] = '\0'; 
            newline();        
            break;
        } 
        else if (ch == 0x08) { // Backspace
            if (i > 0) {
                i--;
                cursor--;        
                printChar(' ');  
                cursor--;        
            }
        } 
        else { 
            string[i] = ch;
            printChar(ch); 
            i++;
        }
    }
}

// TODO 5. Strcmp()
int strcmp(char* str1, char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return 0; 
        }
        i++;
    }
    if (str1[i] == '\0' && str2[i] == '\0') {
        return 1;
    }
    return 0;
}

// Fungsi Newline versi C
void newline() {
    int baris_sekarang = 0;
    while (baris_sekarang <= cursor) {
        baris_sekarang += 80;
    }
    cursor = baris_sekarang;
    updateCursor(cursor); // <--- Selipkan di sini
}

// TODO 6. StartsWith()
// Fungsi untuk mengecek apakah suatu string diawali oleh substring tertentu
int startsWith(char* str, char* prefix) {
    int i = 0;
    while (prefix[i] != '\0') {
        if (str[i] != prefix[i]) {
            return 0; // Karakternya beda, berarti bukan prefix-nya
        }
        i++;
    }
    return 1; // Semua karakter prefix cocok!
}

// TODO 7. Atoi()
// Mengubah string angka menjadi integer murni
int atoi(char* str) {
    int res = 0;
    int i = 0;
    
    // Geser jika ada spasi di awal string argumen
    while (str[i] == ' ') {
        i++;
    }

    while (str[i] >= '0' && str[i] <= '9') {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return res;
}

// TODO 8. IntToString() - Upgraded version for Negative Numbers
void intToString(int num, char* str) {
    int i = 0;
    int j = 0;
    char temp;
    int isNegative = 0;

    // Handle jika angkanya tepat 0
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    // Cek apakah angka bernilai negatif
    if (num < 0) {
        isNegative = 1;
        num = -num; // Ubah ke positif dulu untuk diekstrak digitnya
    }

    // Ambil digit dari belakang
    while (num > 0) {
        int quotient = num / 10; 
        int rem = num - (quotient * 10);
        str[i++] = rem + '0';
        num = quotient;
    }

    // Jika awalnya negatif, tambahkan karakter '-' di belakang sebelum dibalik
    if (isNegative) {
        str[i++] = '-';
    }
    str[i] = '\0';

    // Balikkan string
    i--;
    while (j < i) {
        temp = str[j];
        str[j] = str[i];
        str[i] = temp;
        j++;
        i--;
    }
}

// TODO 9. Factorial()
// Menghitung faktorial dengan proteksi overflow untuk sistem 16-bit
int factorial(int n) {
    int res = 1;
    int i;

    // Faktorial bilangan negatif tidak terdefinisi dalam case ini
    if (n < 0) return -1;
    
    // 0! atau 1! adalah 1
    if (n == 0 || n == 1) return 1;

    for (i = 2; i <= n; i++) {
        // Proteksi overflow 16-bit signed integer (Max: 32767)
        // Kita cek apakah res * i akan melebihi 32767
        // Menggunakan trik pembagian konstan: jika 32767 / i < res, maka pasti overflow!
        if (32767 / i < res) {
            return -1; // Overflow terdeteksi!
        }
        res = res * i;
    }
    return res;
}
