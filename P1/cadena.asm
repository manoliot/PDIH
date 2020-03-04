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

		; Modo 40x25
		mov al, 1
		mov ah, 0
		int 10h

		; Mensaje
		mov dx,OFFSET msg
		mov ah,9
		int 21h

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
