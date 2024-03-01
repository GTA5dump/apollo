PUBLIC _spoofer_stub
 
.code
 
_spoofer_stub PROC
    mov rax, [rsp + 24]
    mov [rax + 16], rdi
    jmp r10
_spoofer_stub ENDP
 
END
