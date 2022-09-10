# Compilação

- O comando **make** gera o executável **elenco**
- A flag **clean** remove os arquivos **.o**
- A flag **purge** remove os arquivos **.o** e o executável **elenco**

# Execução

- **./elenco** lê da entrada padrão *stdin* e escreve na saída padrão *stdout*, assim como na saída de erro *stderr*
- Flags opcionais:
  - **-f** desabilita os cortes por viabilidade
  - **-o** desabilita os cortes por otimalidade
  - **-a** utiliza a função de *bound* dada na especificação do trabalho

# Formato da entrada

**[número de grupos] [número *m* de atores que podem ser elencados] [número de papéis disponíveis]** <br>
**[custo do ator 1] [número *s1* de grupos ao qual ele pertence]** <br>
**[grupo 1]**<br>
**[grupo 2]**<br>
...<br>
**[grupo *s1*]**<br>
**[custo do ator 2] [número *s2* de grupos ao qual ele pertence]** <br>
**[grupo 1]**<br>
**[grupo 2]**<br>
...<br>
**[grupo *s2*]**<br>
...<br>
**[custo do ator *m*] [número *sm* de grupos ao qual ele pertence]** <br>
**[grupo 1]**<br>
**[grupo 2]**<br>
...<br>
**[grupo *sm*]**<br>

# Formato da saída

- *stdout:*<br>
**[indices dos atores escolhidos]**<br>
**[custo de contratação]**<br><br>
ou, caso a entrada seja um problema inviável: <br><br>
**Inviável**<br>

- *stderr:*<br>
**Tempo: [tempo de execução do *branch and bound*] microssegundos**<br>
**Nodos: [número de nós criados na árvore]**<br>
