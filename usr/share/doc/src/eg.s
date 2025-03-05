	.file	"eg.c"
	.text
	.globl	window
	.bss
	.align 8
	.type	window, @object
	.size	window, 8
window:
	.zero	8
	.globl	renderer
	.align 8
	.type	renderer, @object
	.size	renderer, 8
renderer:
	.zero	8
	.globl	texture
	.align 8
	.type	texture, @object
	.size	texture, 8
texture:
	.zero	8
	.globl	imager
	.data
	.align 16
	.type	imager, @object
	.size	imager, 16
imager:
	.long	0
	.long	0
	.long	640
	.long	640
	.globl	surface
	.bss
	.align 8
	.type	surface, @object
	.size	surface, 8
surface:
	.zero	8
	.section	.rodata
	.align 8
.LC0:
	.string	"SDL could not initialize! SDL_Error: %s\n"
.LC1:
	.string	"Tic-Tac-Toe"
.LC2:
	.string	"rb"
	.align 8
.LC3:
	.string	"/home/darkemperor/aathi/my-learnig-path-/TIC_TAC_TOE/assets/image/t.bmp"
	.align 8
.LC4:
	.string	"Window could not be created! SDL_Error: %s\n"
	.align 8
.LC5:
	.string	"/home/darkemperor/aathi/my-learnig-path-/TIC_TAC_TOE/assets/image/welcome_message.bmp"
	.align 8
.LC6:
	.string	"Renderer could not be created! SDL_Error: %s\n"
	.text
	.globl	initSDL
	.type	initSDL, @function
initSDL:
.LFB5023:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$32, %edi
	call	SDL_Init@PLT
	testl	%eax, %eax
	jns	.L2
	call	SDL_GetError@PLT
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	jmp	.L3
.L2:
	movl	$4, %r9d
	movl	$640, %r8d
	movl	$640, %ecx
	movl	$536805376, %edx
	movl	$536805376, %esi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	SDL_CreateWindow@PLT
	movq	%rax, window(%rip)
	leaq	.LC2(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	SDL_RWFromFile@PLT
	movl	$1, %esi
	movq	%rax, %rdi
	call	SDL_LoadBMP_RW@PLT
	movq	%rax, surface(%rip)
	movq	surface(%rip), %rdx
	movq	window(%rip), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	SDL_SetWindowIcon@PLT
	movq	window(%rip), %rax
	testq	%rax, %rax
	jne	.L4
	call	SDL_GetError@PLT
	movq	%rax, %rsi
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	jmp	.L3
.L4:
	movq	window(%rip), %rax
	movl	$2, %edx
	movl	$-1, %esi
	movq	%rax, %rdi
	call	SDL_CreateRenderer@PLT
	movq	%rax, renderer(%rip)
	leaq	.LC2(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	SDL_RWFromFile@PLT
	movl	$1, %esi
	movq	%rax, %rdi
	call	SDL_LoadBMP_RW@PLT
	movq	%rax, surface(%rip)
	movq	surface(%rip), %rdx
	movq	renderer(%rip), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	SDL_CreateTextureFromSurface@PLT
	movq	%rax, texture(%rip)
	movq	surface(%rip), %rax
	movq	%rax, %rdi
	call	SDL_FreeSurface@PLT
	movq	renderer(%rip), %rax
	movq	%rax, %rdi
	call	SDL_RenderClear@PLT
	movq	texture(%rip), %rsi
	movq	renderer(%rip), %rax
	leaq	imager(%rip), %rdx
	movq	%rdx, %rcx
	movl	$0, %edx
	movq	%rax, %rdi
	call	SDL_RenderCopy@PLT
	movq	renderer(%rip), %rax
	movq	%rax, %rdi
	call	SDL_RenderPresent@PLT
	movl	$2000, %edi
	call	SDL_Delay@PLT
	movq	renderer(%rip), %rax
	testq	%rax, %rax
	jne	.L5
	call	SDL_GetError@PLT
	movq	%rax, %rsi
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	jmp	.L3
.L5:
	movq	renderer(%rip), %rax
	movl	$255, %r8d
	movl	$255, %ecx
	movl	$255, %edx
	movl	$255, %esi
	movq	%rax, %rdi
	call	SDL_SetRenderDrawColor@PLT
	movl	$1, %eax
.L3:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5023:
	.size	initSDL, .-initSDL
	.globl	closeSDL
	.type	closeSDL, @function
closeSDL:
.LFB5024:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	renderer(%rip), %rax
	movq	%rax, %rdi
	call	SDL_DestroyRenderer@PLT
	movq	window(%rip), %rax
	movq	%rax, %rdi
	call	SDL_DestroyWindow@PLT
	call	SDL_Quit@PLT
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5024:
	.size	closeSDL, .-closeSDL
	.section	.rodata
	.align 8
.LC7:
	.string	"/home/darkemperor/aathi/my-learnig-path-/SDL/assets/image/tic_win.bmp"
.LC8:
	.string	"Player %d wins!\n"
	.align 8
.LC9:
	.string	"/home/darkemperor/aathi/my-learnig-path-/SDL/assets/image/tic_tac_toe_draw.bmp"
	.text
	.globl	handleMouseClick
	.type	handleMouseClick, @function
handleMouseClick:
.LFB5025:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	%edx, -32(%rbp)
	movl	-32(%rbp), %eax
	movslq	%eax, %rdx
	imulq	$-1713954085, %rdx, %rdx
	shrq	$32, %rdx
	addl	%eax, %edx
	movl	%edx, %ecx
	sarl	$7, %ecx
	cltd
	movl	%ecx, %eax
	subl	%edx, %eax
	movl	%eax, -4(%rbp)
	movl	-28(%rbp), %eax
	movslq	%eax, %rdx
	imulq	$-1713954085, %rdx, %rdx
	shrq	$32, %rdx
	addl	%eax, %edx
	movl	%edx, %ecx
	sarl	$7, %ecx
	cltd
	movl	%ecx, %eax
	subl	%edx, %eax
	movl	%eax, -8(%rbp)
	movq	-24(%rbp), %rcx
	movl	-8(%rbp), %eax
	movslq	%eax, %rsi
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	addq	%rsi, %rax
	movl	(%rcx,%rax,4), %eax
	testl	%eax, %eax
	jne	.L13
	movq	-24(%rbp), %rax
	movl	36(%rax), %esi
	movq	-24(%rbp), %rcx
	movl	-8(%rbp), %eax
	movslq	%eax, %rdi
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	addq	%rdi, %rax
	movl	%esi, (%rcx,%rax,4)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	checkWin
	testl	%eax, %eax
	je	.L9
	leaq	.LC2(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	SDL_RWFromFile@PLT
	movl	$1, %esi
	movq	%rax, %rdi
	call	SDL_LoadBMP_RW@PLT
	movq	%rax, surface(%rip)
	movq	surface(%rip), %rdx
	movq	renderer(%rip), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	SDL_CreateTextureFromSurface@PLT
	movq	%rax, texture(%rip)
	movq	surface(%rip), %rax
	movq	%rax, %rdi
	call	SDL_FreeSurface@PLT
	movq	renderer(%rip), %rax
	movq	%rax, %rdi
	call	SDL_RenderClear@PLT
	movq	texture(%rip), %rsi
	movq	renderer(%rip), %rax
	leaq	imager(%rip), %rdx
	movq	%rdx, %rcx
	movl	$0, %edx
	movq	%rax, %rdi
	call	SDL_RenderCopy@PLT
	movq	renderer(%rip), %rax
	movq	%rax, %rdi
	call	SDL_RenderPresent@PLT
	movl	$2000, %edi
	call	SDL_Delay@PLT
	movq	-24(%rbp), %rax
	movl	36(%rax), %eax
	movl	%eax, %esi
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-24(%rbp), %rax
	movb	$0, 40(%rax)
	jmp	.L13
.L9:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	isfull
	cmpl	$1, %eax
	jne	.L10
	leaq	.LC2(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	call	SDL_RWFromFile@PLT
	movl	$1, %esi
	movq	%rax, %rdi
	call	SDL_LoadBMP_RW@PLT
	movq	%rax, surface(%rip)
	movq	surface(%rip), %rdx
	movq	renderer(%rip), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	SDL_CreateTextureFromSurface@PLT
	movq	%rax, texture(%rip)
	movq	surface(%rip), %rax
	movq	%rax, %rdi
	call	SDL_FreeSurface@PLT
	movq	renderer(%rip), %rax
	movq	%rax, %rdi
	call	SDL_RenderClear@PLT
	movq	texture(%rip), %rsi
	movq	renderer(%rip), %rax
	movl	$0, %ecx
	movl	$0, %edx
	movq	%rax, %rdi
	call	SDL_RenderCopy@PLT
	movq	renderer(%rip), %rax
	movq	%rax, %rdi
	call	SDL_RenderPresent@PLT
	movl	$4000, %edi
	call	SDL_Delay@PLT
	movq	-24(%rbp), %rax
	movb	$0, 40(%rax)
	jmp	.L13
.L10:
	movq	-24(%rbp), %rax
	movl	36(%rax), %eax
	cmpl	$1, %eax
	jne	.L11
	movl	$2, %edx
	jmp	.L12
.L11:
	movl	$1, %edx
.L12:
	movq	-24(%rbp), %rax
	movl	%edx, 36(%rax)
.L13:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5025:
	.size	handleMouseClick, .-handleMouseClick
	.globl	renderGame
	.type	renderGame, @function
renderGame:
.LFB5026:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	renderer(%rip), %rax
	movl	$0, %r8d
	movl	$0, %ecx
	movl	$0, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	SDL_SetRenderDrawColor@PLT
	movq	renderer(%rip), %rax
	movq	%rax, %rdi
	call	SDL_RenderClear@PLT
	movl	$0, %eax
	call	drawGrid
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	drawSymbols
	movq	renderer(%rip), %rax
	movq	%rax, %rdi
	call	SDL_RenderPresent@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5026:
	.size	renderGame, .-renderGame
	.globl	drawGrid
	.type	drawGrid, @function
drawGrid:
.LFB5027:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	renderer(%rip), %rax
	movl	$255, %r8d
	movl	$255, %ecx
	movl	$255, %edx
	movl	$255, %esi
	movq	%rax, %rdi
	call	SDL_SetRenderDrawColor@PLT
	movl	$1, -4(%rbp)
	jmp	.L16
.L17:
	movl	-4(%rbp), %eax
	imull	$213, %eax, %edx
	movl	-4(%rbp), %eax
	imull	$213, %eax, %esi
	movq	renderer(%rip), %rax
	movl	$640, %r8d
	movl	%edx, %ecx
	movl	$0, %edx
	movq	%rax, %rdi
	call	SDL_RenderDrawLine@PLT
	addl	$1, -4(%rbp)
.L16:
	cmpl	$2, -4(%rbp)
	jle	.L17
	movl	$1, -8(%rbp)
	jmp	.L18
.L19:
	movl	-8(%rbp), %eax
	imull	$213, %eax, %ecx
	movl	-8(%rbp), %eax
	imull	$213, %eax, %edx
	movq	renderer(%rip), %rax
	movl	%ecx, %r8d
	movl	$640, %ecx
	movl	$0, %esi
	movq	%rax, %rdi
	call	SDL_RenderDrawLine@PLT
	addl	$1, -8(%rbp)
.L18:
	cmpl	$2, -8(%rbp)
	jle	.L19
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5027:
	.size	drawGrid, .-drawGrid
	.globl	drawSymbols
	.type	drawSymbols, @function
drawSymbols:
.LFB5028:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L21
.L26:
	movl	$0, -8(%rbp)
	jmp	.L22
.L25:
	movq	-24(%rbp), %rcx
	movl	-8(%rbp), %eax
	movslq	%eax, %rsi
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	addq	%rsi, %rax
	movl	(%rcx,%rax,4), %eax
	cmpl	$1, %eax
	jne	.L23
	movl	-8(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	draw_X
	jmp	.L24
.L23:
	movq	-24(%rbp), %rcx
	movl	-8(%rbp), %eax
	movslq	%eax, %rsi
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	addq	%rsi, %rax
	movl	(%rcx,%rax,4), %eax
	cmpl	$2, %eax
	jne	.L24
	movl	-8(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	draw_O
.L24:
	addl	$1, -8(%rbp)
.L22:
	cmpl	$2, -8(%rbp)
	jle	.L25
	addl	$1, -4(%rbp)
.L21:
	cmpl	$2, -4(%rbp)
	jle	.L26
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5028:
	.size	drawSymbols, .-drawSymbols
	.globl	draw_X
	.type	draw_X, @function
draw_X:
.LFB5029:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -36(%rbp)
	movl	%esi, -40(%rbp)
	movl	$213, -8(%rbp)
	movl	$15, -12(%rbp)
	movl	-40(%rbp), %eax
	imull	-8(%rbp), %eax
	movl	%eax, %edx
	movl	-12(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -16(%rbp)
	movl	-36(%rbp), %eax
	imull	-8(%rbp), %eax
	movl	%eax, %edx
	movl	-12(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -20(%rbp)
	movl	-40(%rbp), %eax
	addl	$1, %eax
	imull	-8(%rbp), %eax
	subl	-12(%rbp), %eax
	movl	%eax, -24(%rbp)
	movl	-36(%rbp), %eax
	addl	$1, %eax
	imull	-8(%rbp), %eax
	subl	-12(%rbp), %eax
	movl	%eax, -28(%rbp)
	movq	renderer(%rip), %rax
	movl	$255, %r8d
	movl	$255, %ecx
	movl	$255, %edx
	movl	$255, %esi
	movq	%rax, %rdi
	call	SDL_SetRenderDrawColor@PLT
	movl	$5, -32(%rbp)
	movl	-32(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	negl	%eax
	movl	%eax, -4(%rbp)
	jmp	.L28
.L29:
	movl	-24(%rbp), %edx
	movl	-4(%rbp), %eax
	leal	(%rdx,%rax), %ecx
	movl	-16(%rbp), %edx
	movl	-4(%rbp), %eax
	leal	(%rdx,%rax), %esi
	movq	renderer(%rip), %rax
	movl	-28(%rbp), %edi
	movl	-20(%rbp), %edx
	movl	%edi, %r8d
	movq	%rax, %rdi
	call	SDL_RenderDrawLine@PLT
	movl	-24(%rbp), %edx
	movl	-4(%rbp), %eax
	leal	(%rdx,%rax), %ecx
	movl	-16(%rbp), %edx
	movl	-4(%rbp), %eax
	leal	(%rdx,%rax), %esi
	movq	renderer(%rip), %rax
	movl	-20(%rbp), %edi
	movl	-28(%rbp), %edx
	movl	%edi, %r8d
	movq	%rax, %rdi
	call	SDL_RenderDrawLine@PLT
	addl	$1, -4(%rbp)
.L28:
	movl	-32(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	cmpl	%eax, -4(%rbp)
	jle	.L29
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5029:
	.size	draw_X, .-draw_X
	.globl	draw_O
	.type	draw_O, @function
draw_O:
.LFB5030:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	$213, -4(%rbp)
	movl	-24(%rbp), %eax
	imull	-4(%rbp), %eax
	movl	%eax, %edx
	movl	-4(%rbp), %eax
	movl	%eax, %ecx
	shrl	$31, %ecx
	addl	%ecx, %eax
	sarl	%eax
	addl	%edx, %eax
	movl	%eax, -8(%rbp)
	movl	-20(%rbp), %eax
	imull	-4(%rbp), %eax
	movl	%eax, %edx
	movl	-4(%rbp), %eax
	movl	%eax, %ecx
	shrl	$31, %ecx
	addl	%ecx, %eax
	sarl	%eax
	addl	%edx, %eax
	movl	%eax, -12(%rbp)
	movl	-4(%rbp), %eax
	leal	3(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$2, %eax
	movl	%eax, -16(%rbp)
	movq	renderer(%rip), %rax
	movl	-16(%rbp), %ecx
	movl	-12(%rbp), %edx
	movl	-8(%rbp), %esi
	movl	$5, %r8d
	movq	%rax, %rdi
	call	draw_thick_circle
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5030:
	.size	draw_O, .-draw_O
	.globl	draw_thick_circle
	.type	draw_thick_circle, @function
draw_thick_circle:
.LFB5031:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	%edx, -32(%rbp)
	movl	%ecx, -36(%rbp)
	movl	%r8d, -40(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L32
.L33:
	movl	-36(%rbp), %edx
	movl	-4(%rbp), %eax
	leal	(%rdx,%rax), %ecx
	movl	-32(%rbp), %edx
	movl	-28(%rbp), %esi
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	draw_circle
	movl	-36(%rbp), %eax
	subl	-4(%rbp), %eax
	movl	%eax, %ecx
	movl	-32(%rbp), %edx
	movl	-28(%rbp), %esi
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	draw_circle
	addl	$1, -4(%rbp)
.L32:
	movl	-4(%rbp), %eax
	cmpl	-40(%rbp), %eax
	jl	.L33
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5031:
	.size	draw_thick_circle, .-draw_thick_circle
	.globl	draw_circle
	.type	draw_circle, @function
draw_circle:
.LFB5032:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	%edx, -32(%rbp)
	movl	%ecx, -36(%rbp)
	movl	-36(%rbp), %eax
	movl	%eax, -4(%rbp)
	movl	$0, -8(%rbp)
	movl	$1, %eax
	subl	-36(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	-32(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%eax, %edx
	movl	-28(%rbp), %ecx
	movl	-4(%rbp), %eax
	addl	%eax, %ecx
	movq	-24(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	SDL_RenderDrawPoint@PLT
	movl	-32(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%eax, %edx
	movl	-28(%rbp), %eax
	subl	-4(%rbp), %eax
	movl	%eax, %ecx
	movq	-24(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	SDL_RenderDrawPoint@PLT
	movl	-32(%rbp), %edx
	movl	-4(%rbp), %eax
	addl	%eax, %edx
	movl	-28(%rbp), %ecx
	movl	-8(%rbp), %eax
	addl	%eax, %ecx
	movq	-24(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	SDL_RenderDrawPoint@PLT
	movl	-32(%rbp), %edx
	movl	-4(%rbp), %eax
	addl	%eax, %edx
	movl	-28(%rbp), %eax
	subl	-8(%rbp), %eax
	movl	%eax, %ecx
	movq	-24(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	SDL_RenderDrawPoint@PLT
	jmp	.L35
.L38:
	addl	$1, -8(%rbp)
	cmpl	$0, -12(%rbp)
	jg	.L36
	movl	-8(%rbp), %eax
	leal	(%rax,%rax), %edx
	movl	-12(%rbp), %eax
	addl	%edx, %eax
	addl	$1, %eax
	movl	%eax, -12(%rbp)
	jmp	.L37
.L36:
	subl	$1, -4(%rbp)
	movl	-8(%rbp), %eax
	leal	(%rax,%rax), %edx
	movl	-12(%rbp), %eax
	addl	%eax, %edx
	movl	-4(%rbp), %eax
	addl	%eax, %eax
	subl	%eax, %edx
	leal	1(%rdx), %eax
	movl	%eax, -12(%rbp)
.L37:
	movl	-32(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%eax, %edx
	movl	-28(%rbp), %ecx
	movl	-4(%rbp), %eax
	addl	%eax, %ecx
	movq	-24(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	SDL_RenderDrawPoint@PLT
	movl	-32(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%eax, %edx
	movl	-28(%rbp), %eax
	subl	-4(%rbp), %eax
	movl	%eax, %ecx
	movq	-24(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	SDL_RenderDrawPoint@PLT
	movl	-32(%rbp), %eax
	subl	-8(%rbp), %eax
	movl	%eax, %edx
	movl	-28(%rbp), %ecx
	movl	-4(%rbp), %eax
	addl	%eax, %ecx
	movq	-24(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	SDL_RenderDrawPoint@PLT
	movl	-32(%rbp), %eax
	subl	-8(%rbp), %eax
	movl	%eax, %edx
	movl	-28(%rbp), %eax
	subl	-4(%rbp), %eax
	movl	%eax, %ecx
	movq	-24(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	SDL_RenderDrawPoint@PLT
	movl	-32(%rbp), %edx
	movl	-4(%rbp), %eax
	addl	%eax, %edx
	movl	-28(%rbp), %ecx
	movl	-8(%rbp), %eax
	addl	%eax, %ecx
	movq	-24(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	SDL_RenderDrawPoint@PLT
	movl	-32(%rbp), %edx
	movl	-4(%rbp), %eax
	addl	%eax, %edx
	movl	-28(%rbp), %eax
	subl	-8(%rbp), %eax
	movl	%eax, %ecx
	movq	-24(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	SDL_RenderDrawPoint@PLT
	movl	-32(%rbp), %eax
	subl	-4(%rbp), %eax
	movl	%eax, %edx
	movl	-28(%rbp), %ecx
	movl	-8(%rbp), %eax
	addl	%eax, %ecx
	movq	-24(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	SDL_RenderDrawPoint@PLT
	movl	-32(%rbp), %eax
	subl	-4(%rbp), %eax
	movl	%eax, %edx
	movl	-28(%rbp), %eax
	subl	-8(%rbp), %eax
	movl	%eax, %ecx
	movq	-24(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	SDL_RenderDrawPoint@PLT
.L35:
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jg	.L38
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5032:
	.size	draw_circle, .-draw_circle
	.globl	checkWin
	.type	checkWin, @function
checkWin:
.LFB5033:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L40
.L45:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %ecx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movl	4(%rax), %eax
	cmpl	%eax, %ecx
	jne	.L41
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movl	4(%rax), %ecx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movl	8(%rax), %eax
	cmpl	%eax, %ecx
	jne	.L41
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L42
.L41:
	movq	-16(%rbp), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %edx
	movq	-16(%rbp), %rax
	leaq	12(%rax), %rcx
	movl	-4(%rbp), %eax
	cltq
	movl	(%rcx,%rax,4), %eax
	cmpl	%eax, %edx
	jne	.L43
	movq	-16(%rbp), %rax
	leaq	12(%rax), %rdx
	movl	-4(%rbp), %eax
	cltq
	movl	(%rdx,%rax,4), %edx
	movq	-16(%rbp), %rax
	leaq	24(%rax), %rcx
	movl	-4(%rbp), %eax
	cltq
	movl	(%rcx,%rax,4), %eax
	cmpl	%eax, %edx
	jne	.L43
	movq	-16(%rbp), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	testl	%eax, %eax
	je	.L43
.L42:
	movq	-24(%rbp), %rax
	movl	36(%rax), %eax
	jmp	.L44
.L43:
	addl	$1, -4(%rbp)
.L40:
	cmpl	$2, -4(%rbp)
	jle	.L45
	movq	-16(%rbp), %rax
	movl	(%rax), %edx
	movq	-16(%rbp), %rax
	addq	$12, %rax
	movl	4(%rax), %eax
	cmpl	%eax, %edx
	jne	.L46
	movq	-16(%rbp), %rax
	addq	$12, %rax
	movl	4(%rax), %edx
	movq	-16(%rbp), %rax
	addq	$24, %rax
	movl	8(%rax), %eax
	cmpl	%eax, %edx
	jne	.L46
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L47
.L46:
	movq	-16(%rbp), %rax
	movl	8(%rax), %edx
	movq	-16(%rbp), %rax
	addq	$12, %rax
	movl	4(%rax), %eax
	cmpl	%eax, %edx
	jne	.L48
	movq	-16(%rbp), %rax
	addq	$12, %rax
	movl	4(%rax), %edx
	movq	-16(%rbp), %rax
	addq	$24, %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jne	.L48
	movq	-16(%rbp), %rax
	movl	8(%rax), %eax
	testl	%eax, %eax
	je	.L48
.L47:
	movq	-24(%rbp), %rax
	movl	36(%rax), %eax
	jmp	.L44
.L48:
	movl	$0, %eax
.L44:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5033:
	.size	checkWin, .-checkWin
	.globl	isfull
	.type	isfull, @function
isfull:
.LFB5034:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, -24(%rbp)
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L50
.L55:
	movl	$0, -12(%rbp)
	jmp	.L51
.L54:
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	addq	%rax, %rdx
	movl	-12(%rbp), %eax
	cltq
	movl	(%rdx,%rax,4), %eax
	cmpl	$1, %eax
	je	.L52
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	addq	%rax, %rdx
	movl	-12(%rbp), %eax
	cltq
	movl	(%rdx,%rax,4), %eax
	cmpl	$2, %eax
	jne	.L53
.L52:
	addl	$1, -4(%rbp)
.L53:
	addl	$1, -12(%rbp)
.L51:
	cmpl	$2, -12(%rbp)
	jle	.L54
	addl	$1, -8(%rbp)
.L50:
	cmpl	$2, -8(%rbp)
	jle	.L55
	cmpl	$9, -4(%rbp)
	sete	%al
	movzbl	%al, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5034:
	.size	isfull, .-isfull
	.globl	resetGame
	.type	resetGame, @function
resetGame:
.LFB5035:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movl	$1, 36(%rax)
	movq	-24(%rbp), %rax
	movb	$1, 40(%rax)
	movl	$0, -4(%rbp)
	jmp	.L58
.L61:
	movl	$0, -8(%rbp)
	jmp	.L59
.L60:
	movq	-24(%rbp), %rcx
	movl	-8(%rbp), %eax
	movslq	%eax, %rsi
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	addq	%rsi, %rax
	movl	$0, (%rcx,%rax,4)
	addl	$1, -8(%rbp)
.L59:
	cmpl	$2, -8(%rbp)
	jle	.L60
	addl	$1, -4(%rbp)
.L58:
	cmpl	$2, -4(%rbp)
	jle	.L61
	nop
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5035:
	.size	resetGame, .-resetGame
	.section	.rodata
.LC10:
	.string	"Failed to initialize!"
	.text
	.globl	main
	.type	main, @function
main:
.LFB5036:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	addq	$-128, %rsp
	movl	%edi, -116(%rbp)
	movq	%rsi, -128(%rbp)
	movl	$0, %eax
	call	initSDL
	xorl	$1, %eax
	testb	%al, %al
	je	.L63
	leaq	.LC10(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$-1, %eax
	jmp	.L70
.L63:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	resetGame
	jmp	.L65
.L68:
	movl	-112(%rbp), %eax
	cmpl	$256, %eax
	jne	.L67
	movb	$0, -8(%rbp)
	jmp	.L66
.L67:
	movl	-112(%rbp), %eax
	cmpl	$1025, %eax
	jne	.L66
	leaq	-56(%rbp), %rdx
	leaq	-52(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	SDL_GetMouseState@PLT
	movl	-56(%rbp), %edx
	movl	-52(%rbp), %ecx
	leaq	-48(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	handleMouseClick
.L66:
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	SDL_PollEvent@PLT
	testl	%eax, %eax
	jne	.L68
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	renderGame
.L65:
	movzbl	-8(%rbp), %eax
	testb	%al, %al
	jne	.L66
	movl	$0, %eax
	call	closeSDL
	movl	$0, %eax
.L70:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5036:
	.size	main, .-main
	.ident	"GCC: (Debian 14.2.0-3) 14.2.0"
	.section	.note.GNU-stack,"",@progbits
