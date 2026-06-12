; Marco Calderón Guevara C31426: 33% de participacion
; Rolbin Castillo Matamoros B81771: 33% de participacion
; Jordan Barquero Araya C30965 33% de participacion

section .note.GNU-stack noalloc noexec nowrite progbits

section .data
urandom db '/dev/urandom', 0  ; Ruta al dispositivo urandom

section .bss
buffer resq  1         ; Buffer para almacenar el número aleatorio
casillas resq 1      ; BUffer para almacenar el total de casillas o limite superior

section .text
global colocar_minas
global calcular_minas
global colocar_misiles
global calcular_minas_esquinas
global borde_Superior_Inferior
global borde_Izquierdo_Derecho
global contar_minas_matriz_central

colocar_minas:
    ; Entradas: 
    ; rdi -> tablero 
    ; rsi -> casillas 
    ; rdx -> numMinas 

    mov rcx, rdx        ; Copiar el número de minas a rcx
    mov [casillas], rsi

colocando_minas:
    ; Cargar la posición de la mina
    call num_random
    ;mov eax, [rsi + rcx*4]  ; Cargar el índice de mina desde minas

    ; Colocar la mina
    mov qword [rdi + rax*8], -1 ; Colocar mina en tablero
    sub rcx, 1                 ; Decrementar el contador de minas
    cmp rcx, 0              ; Comprobar si hemos colocado todas las minas
    jne colocando_minas            ; Si no, seguir colocando

    ret

num_random:
    push rdi
    push rcx
    ; Abrir /dev/urandom
    mov rax, 2                ; syscall: open
    lea rdi, [urandom]        ; ruta
    mov rsi, 0                ; O_RDONLY
    syscall

    ; Leer 4 bytes de /dev/urandom
    mov rdi, rax              ; Descriptor de archivo
    lea rsi, [buffer]         ; Buffer para almacenar el resultado
    mov rdx, 8                ; Número de bytes a leer
    mov rax, 0                ; syscall: read
    syscall

    ; Aquí puedes usar el número aleatorio que está en buffer
    ; Convertirlo a un número entre 0 y 99
    movzx rax, byte [buffer]  ; Cargar el primer byte como número
    xor rdx, rdx              ; Limpiar RDX
    mov rcx, [casillas]       ; Limite superior
    div rcx                   ; EAX = EAX / 100

    mov eax, edx
    pop rcx
    pop rdi
    ret
colocar_misiles:
    ; Entradas: 
    ; rdi -> tablero 
    ; rsi -> casillas 
    ; rdx -> misiles

    mov rcx, rdx               ; Copiar el número de misiles a rcx
    mov [casillas], rsi

colocando_misiles:
    ; Cargar la posición del misil
    call num_random
    ;mov eax, [rsi + rcx*4]    ; Cargar el índice de mina desde minas

    ; Colocar la mina
    mov qword [rdi + rax*8], 9 ; Colocar misil en tablero
    sub rcx, 1                    ; Decrementar el contador de misiles
    cmp rcx, 0                 ; Comprobar si hemos colocado todas las minas
    jne colocando_misiles      ; Si no, seguir colocando

    ret

calcular_minas_esquinas:       ; Conteo de las minas alrededor de las esquinas 
    ; rdi -> tablero 
    ; rsi -> index_esquinas
    push r10
    push r8

    ; Esquina superior izquierda
    xor r10, r10
    xor r8, r8 
    mov rbx, [rsi + r8 * 8]    ; Base index esquinas
    
    cmp rbx, -1
    je esquiSupDer
    cmp rbx, 9
    je esquiSupDer
    
    add rbx, 1
    call acumular
    add rbx, 14
    call acumular
    add rbx, 1
    call acumular
    mov rbx, [rsi + r8 * 8]
    mov [rdi + rbx * 8], r10
    
    ; Esquina superior derecha
    esquiSupDer:
        xor r10, r10
        xor rbx, rbx
        add r8, 1
        mov rbx, [rsi + r8 * 8]    ; Base index esquinas
        
        cmp rbx, -1
        je esquiInfIzq
        cmp rbx, 9
        je esquiInfIzq
        
        sub rbx, 1
        call acumular
        add rbx, 15
        call acumular
        add rbx, 1
        call acumular
        mov rbx, [rsi + r8 * 8]
        mov [rdi + rbx * 8], r10

    ; Esquina inferior izquierda
    esquiInfIzq:
        xor r10, r10
        xor rbx, rbx
        add r8, 1
        mov rbx, [rsi + r8 * 8]    ; Base index esquinas
        
        cmp rbx, -1
        je esquiInfDer
        cmp rbx, 9
        je esquiInfDer
        
        add rbx, 1
        call acumular
        sub rbx, 15
        call acumular
        sub rbx, 1
        call acumular
        mov rbx, [rsi + r8 * 8]
        mov [rdi + rbx * 8], r10

    ; Esquina inferior derecha
    esquiInfDer:
        xor r10, r10
        xor rbx, rbx
        add r8, 1
        mov rbx, [rsi + r8 * 8]    ; Base index esquinas
        
        cmp rbx, -1
        je fin_calcular
        cmp rbx, 9
        je fin_calcular
        
        sub rbx, 1
        call acumular
        sub rbx, 14
        call acumular
        sub rbx, 1
        call acumular
        mov rbx, [rsi + r8 * 8]
        mov [rdi + rbx * 8], r10

    fin_calcular:
        pop r8
        pop r10
        ret



borde_Superior_Inferior:          ; Conteo de minas en las filas de los bordes superior e inferior
    ; rdi -> tablero 
    ; rsi -> index borde superior
    ; rdx -> index borde inferior

    mov r9, 13
    xor r8, r8
    xor rbx, rbx
    borde_superior:
        xor r10, r10
        mov rbx, [rsi + r8 * 8]
        mov r11, [rdi + rbx * 8]
        
        cmp r11, -1
        je fin_ciclo_borde_sup
        cmp r11, 9
        je fin_ciclo_borde_sup
        
        sub rbx, 1 
        call acumular
        add rbx, 2
        call acumular
        add rbx, 13
        call acumular
        add rbx, 1
        call acumular
        add rbx, 1
        call acumular

        mov rbx, [rsi + r8 * 8]
        mov [rdi + rbx * 8], r10

        fin_ciclo_borde_sup:
            add r8, 1
            sub r9, 1
            cmp r9, 0
            jne borde_superior
            ;ret
            
    borde_inferior:
        mov r9, 13
        xor r8, r8
        xor rbx, rbx
        
        ciclo_borde_inferior:
            xor r10, r10
            mov rbx, [rdx + r8 * 8]
            mov r11, [rdi + rbx * 8]
            
            cmp r11, -1
            je fin_ciclo_borde_inf
            cmp r11, 9
            je fin_ciclo_borde_inf
            
            add rbx, 1 
            call acumular
            sub rbx, 2
            call acumular
            sub rbx, 15
            call acumular
            add rbx, 1
            call acumular
            add rbx, 1
            call acumular

            mov rbx, [rdx + r8 * 8]
            mov [rdi + rbx * 8], r10

            fin_ciclo_borde_inf:
                add r8, 1
                sub r9, 1
                cmp r9, 0
                jne ciclo_borde_inferior
                ret

borde_Izquierdo_Derecho:              ; Conteo de las minas en las columnas del borde izquierdo y derecho  
    mov r9, 13
    xor r8, r8
    xor rbx, rbx

    borde_izquierdo:
        xor r10, r10
        mov rbx, [rsi + r8 * 8]        ; Cargo el indice del tablero
        mov r11, [rdi + rbx * 8]       ; Cargo el contenido para saber si hay una mina
        
        cmp r11, -1
        je fin_ciclo_borde_izq
        cmp r11, 9
        je fin_ciclo_borde_izq
        
        add rbx, 1
        call acumular
        sub rbx, 16
        call acumular
        add rbx, 1
        call acumular
        add rbx, 30
        call acumular
        sub rbx, 1
        call acumular

        mov rbx, [rsi + r8 * 8]
        mov [rdi + rbx * 8], r10

        fin_ciclo_borde_izq:
            add r8, 1
            sub r9, 1
            cmp r9, 0
            jne borde_izquierdo
        
        borde_derecho:
        mov r9, 13
        xor r8, r8
        xor rbx, rbx
        
        ciclo_borde_derecho:
            xor r10, r10
            mov rbx, [rdx + r8 * 8]
            mov r11, [rdi + rbx * 8]
            
            cmp r11, -1
            je fin_ciclo_borde_der
            cmp r11, 9 
            je fin_ciclo_borde_der
            
            sub rbx, 1 
            call acumular
            sub rbx, 14
            call acumular
            sub rbx, 1
            call acumular
            add rbx, 30
            call acumular
            add rbx, 1
            call acumular

            mov rbx, [rdx + r8 * 8]
            mov [rdi + rbx * 8], r10

            fin_ciclo_borde_der:
                add r8, 1
                sub r9, 1
                cmp r9, 0
                jne ciclo_borde_derecho
                ret

contar_minas_matriz_central:
    mov r9, 169                        ; 169: tamaño de la matriz interna del tablero sin contar los bordes
    xor r8, r8
    xor rbx, rbx

    contar_minas:
        xor r10, r10
        mov rbx, [rsi + r8 * 8]        ; Cargo el indice del tablero
        mov r11, [rdi + rbx * 8]       ; Cargo el contenido para saber si hay una mina
        

        cmp r11, -1                    ; Comprobar si hay una mina
        je fin_contar_minas
        cmp r11, 9                     ; Comprobar si hay un misil
        je fin_contar_minas
        
        sub rbx, 16
        call conteo
        add rbx, 13
        call conteo
        add rbx, 13
        call conteo

        mov rbx, [rsi + r8 * 8]
        mov [rdi + rbx * 8], r10


        fin_contar_minas:
                add r8, 1
                sub r9, 1
                cmp r9, 0
                jne contar_minas
                ret
        
        conteo:
            call acumular
            add rbx, 1
            call acumular
            add rbx, 1
            call acumular
            ret
acumular:
    mov rcx, [rdi + rbx * 8]  ; Cargo lo que esta en la casilla
    cmp rcx, -1               ; Comparo con -1 para saber si es una mina
    jne fin_acumular          ; Si no es igual salgo de la funcion
    add r10, 1                ; Si es igual incremento el contador
    
    fin_acumular:
        ret 