
; hello_world.asm
  BITS 64
  org 0x400000

  ehdr:           ; Elf64_Ehdr
    db 0x7f, "ELF", 2, 1, 1, 0 ; e_ident
    times 8 db 0
    dw  2         ; e_type
    dw  0x3e      ; e_machine
    dd  1         ; e_version
    dq  _start    ; e_entry
    dq  phdr - $$ ; e_phoff
    dq  0         ; e_shoff
    dd  0         ; e_flags
    dw  ehdrsize  ; e_ehsize
    dw  phdrsize  ; e_phentsize
  phdr:           ; Elf64_Phdr
    dd  1         ; e_phnum      ; p_type
	              ; e_shentsize
    dd  5         ; e_shnum      ; p_flags
	              ; e_shstrndx
  ehdrsize  equ  $ - ehdr
    dq  0         ; p_offset
    dq  $$        ; p_vaddr
    dq  $$        ; p_paddr
    dq  filesize  ; p_filesz
    dq  filesize  ; p_memsz
    dq  0x1000    ; p_align
  phdrsize  equ  $ - phdr
  
  _start:
    ; write "Hello World!" to stdout
	  mov al, 1
    mov dl, 13
    mov esi, hello
    syscall
    mov al, 231
    syscall

  hello: db "Hello World!", 10 ; 10 is the ASCII code for newline

  filesize  equ  $ - $$