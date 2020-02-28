pila segment stack 'stack'
	 dw 100h dup (?)
pila ends

datos segment 'data'
	 msg db 'Hola, mundo$'
	 newline db 10,13,'$'
	 iters dw 7
datos ends

codigo segment 'code'
	 assume cs:codigo, ds:datos, ss:pila
	 main PROC
		  mov ax,datos
		  mov ds,ax

		  mov cx, 0
		  mov ah,9
		  bucle:
				mov dx,OFFSET msg
				int 21h
				mov dx,OFFSET newline
				int 21h

				inc cx
				cmp cx, iters
				jl bucle

		  mov ax,4C00h
		  int 21h

	 main ENDP
codigo ends

END main
