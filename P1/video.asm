pila segment stack 'stack'
	dw 100h dup (?)
pila ends

datos segment 'data'
	msg db 'Hola, mundo$'
datos ends

codigo segment 'code'
	assume cs:codigo, ds:datos, ss:pila
	main PROC
		mov ax,datos
		mov ds,ax

		; Modo grafico
		mov al, 4
		mov ah, 0
		int 10h

		; Rectángulo
		mov cx, 60
		mov dx, 50
		mov ah, 0Ch
		mov al, 3
		sqloop:
			int 10h
			inc cx
			cmp cx, 260
			jl sqloop

			mov cx, 60
			inc dx
			cmp dx, 150
			jl sqloop

		; Linea vertical
		mov cx, 160
		mov dx, 50
		mov ah, 0Ch
		mov al, 1
		vloop:
			int 10h
			inc dx
			cmp dx, 150
			jl vloop

		; Linea horizontal
		mov cx, 60
		mov dx, 100
		mov ah, 0Ch
		mov al, 2
		hloop:
			int 10h
			inc cx
			cmp cx, 260
			jl hloop


		; Pausa
		mov ah, 8
		int 21h

		; Modo 80x25
		mov al, 3
		mov ah, 0
		int 10h

		; Exit
		mov ax,4C00h
		int 21h

	main ENDP
codigo ends

END main

