bits 16

global _start
global _putInMemory
global _getChar
global _printString   ; <--- Daftarkan secara global agar bisa dibaca kernel.c
global _clearScreen   ; <--- Daftarkan secara global
global _newline       ; <--- Daftarkan secara global
global _readString    ; <--- Daftarkan secara global
global _updateCursor  ; <--- [PASANG DI SINI 1] Daftarkan kursor global
extern _main

_start:

    cli

    mov ax, cs
    mov ds, ax
    mov es, ax

    sti

    call _main

.hang:
    jmp .hang


_putInMemory:
    push bp
    mov bp, sp

    push ds

    mov ax, [bp+4]
    mov si, [bp+6]
    mov cl, [bp+8]

    mov ds, ax
    mov [si], cl

    pop ds

    pop bp
    ret

; === 1. FUNGSI UNTUK MENGAMBIL KARAKTER DARI KEYBOARD ===
_getChar:
    mov ah, 0x00        ; Interrupt membaca karakter tekan
    int 0x16            ; BIOS Keyboard Service (Hasil ASCII masuk ke AL)
    mov ah, 0x00        ; Bersihkan AH, return value bcc diletakkan di AX
    ret

; === 2. FUNGSI UNTUK MENCETAK STRING KE LAYAR ===
_printString:
    push bp
    mov bp, sp
    mov si, [bp+4]      ; Mengambil argumen pointer char* string (alamat memori)

.loop_print:
    lodsb               ; Muat karakter dari [DS:SI] ke register AL, lalu SI++
    cmp al, 0           ; Cek apakah karakternya string terminator '\0'
    je .end_print       ; Jika iya, lompat ke selesai
    
    mov ah, 0x0E        ; Mode teletype BIOS (Cetak karakter ke layar)
    int 0x10            ; BIOS Video Service
    jmp .loop_print

.end_print:
    pop bp
    ret

; === 3. FUNGSI UNTUK MEMBERSIHKAN LAYAR ===
_clearScreen:
    mov ah, 0x00        ; Set video mode
    mov al, 0x03        ; Mode teks standar 80x25 warna
    int 0x10            ; BIOS Video Service (Otomatis membersihkan layar)
    ret

; === 4. FUNGSI UNTUK BARIS BARU (NEWLINE) ===
_newline:
    mov ah, 0x0E
    mov al, 0x0D        ; Carriage Return (\r) -> Mengembalikan kursor ke kiri
    int 0x10
    mov al, 0x0A        ; Line Feed (\n) -> Menurunkan kursor ke baris baru
    int 0x10
    ret

; === 5. FUNGSI UNTUK MEMBACA SATU BARIS STRING DARI KEYBOARD ===
_readString:
    push bp
    mov bp, sp
    mov di, [bp+4]      ; Mengambil argumen buffer char* dari C
    
.loop_read:
    mov ah, 0x00        ; Baca input keyboard
    int 0x16
    
    cmp al, 0x0D        ; Cek apakah user menekan tombol ENTER (\r)
    je .end_read        ; Jika ENTER, selesai membaca
    
    mov [di], al        ; Masukkan karakter dari AL ke alamat memori buffer [DI]
    inc di              ; Geser pointer memori buffer ke indeks berikutnya
    
    mov ah, 0x0E        ; Cetak karakter yang diketik ke layar (Echoing)
    int 0x10
    jmp .loop_read

.end_read:
    mov byte [di], 0    ; Tambahkan string terminator '\0' di akhir array char
    mov ah, 0x0E
    mov al, 0x0D        ; Buat kursor turun ke bawah setelah enter
    int 0x10
    mov al, 0x0A
    int 0x10
    
    pop bp
    ret

; === 6. FUNGSI UPDATE KURSOR HARDWARE VIA BIOS ===
; [PASANG DI SINI 2] Diletakkan di paling bawah agar rapi
_updateCursor:
    push bp
    mov bp, sp
    
    mov ax, [bp+4]      ; Ambil argumen nilai 'cursor' dari C (misal: 80, 160, dst)
    
    ; Cari koordinat Baris (Row) dan Kolom (Column)
    ; Baris = cursor / 80, Kolom = cursor % 80
    mov cl, 80
    div cl              ; AX dibagi 80. Hasil bagi (Baris) di AL, Sisa bagi (Kolom) di AH
    
    mov dh, al          ; DH = Baris (Row)
    mov dl, ah          ; DL = Kolom (Column)
    mov bh, 0           ; BH = Page number (0)
    
    mov ah, 0x02        ; Service BIOS: Set Cursor Position
    int 0x10            ; Panggil interupsi video BIOS
    
    pop bp
    ret
