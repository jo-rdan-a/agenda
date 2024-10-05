# 📒 Projeto de Estrutura de Dados - Nó Encadeado

Este projeto é uma implementação de uma **Agenda de Contatos** usando listas duplamente encadeadas em C, com a parte lógica e visual desenvolvida usando **GTK**. Faz parte da disciplina de **Estrutura de Dados** no **Instituto Federal do Ceará - Campus Boa Viagem**, orientada pelo professor **Gabriel Tavares**.

## 👥 Equipe

- Jordana dos Reis
- Iasmin Azevedo
- Weslem Rodrigues

## 🛠️ Descrição

Este projeto tem como foco o uso de **nós encadeados** para organizar os dados de uma agenda de contatos. Aqui, você pode:

- 📇 **Criar** um novo contato
- 📝 **Inserir** contatos no início da lista
- ❌ **Remover** contatos pelo nome
- 📜 **Exibir** todos os contatos cadastrados
- 🔍 **Pesquisar** por um contato específico

## 🚀 Funcionalidades

- Adicione, remova e pesquise contatos de forma simples e eficiente!
- Gerencie seus contatos em uma lista dinâmica com **nós duplamente encadeados**.

## 💻 Como rodar o projeto

### Instalação do GTK

1. **Instalar MSYS2**  
   Baixe e instale o MSYS2. Após a instalação, siga os passos abaixo:

   - Abra o terminal MSYS2 e atualize os pacotes:
     ```bash
     pacman -Syu
     ```
   - Reinicie o terminal e continue a atualização:
     ```bash
     pacman -Su
     ```

2. **Instalar GTK e Ferramentas de Desenvolvimento**  
   No terminal MSYS2, instale o GTK3 e o conjunto de ferramentas de desenvolvimento:
   ```bash
   pacman -S mingw-w64-x86_64-gtk3 mingw-w64-x86_64-toolchain
   pacman -S mingw-w64-x86_64-toolchain mingw-w64-x86_64-pkg-config
   ```

   ## 💻 Compilação e Execução

3. **Compilação e Execução**  
   Navegue até o seu diretório, por exemplo:
   ```bash
   cd /c/Users/Aluno/Desktop/atividade
   ```

Compile o código usando o GCC no terminal MSYS2:

```bash
gcc -o agenda agenda.c `pkg-config --cflags --libs gtk+-3.0`
Execute o programa:
```

```bash
./agenda.exe
```

4. Verificar o PATH
Se após a instalação houver problemas com os comandos gcc ou pkg-config, você pode verificar se o caminho /mingw64/bin foi adicionado ao PATH do MSYS2. Isso garante que os comandos sejam encontrados corretamente.

Você pode adicionar o caminho manualmente executando o seguinte comando no terminal do MSYS2:

```bash
export PATH=/mingw64/bin:$PATH
```

## 📞 Exemplo de Uso

```plaintext
Selecione uma operação:
1. Criar Agenda
2. Inserir contato
3. Remover contato
4. Mostrar lista de contatos
5. Pesquisar contato por nome
X. Sair

>> Opção: 2
>> Digite o nome: Jordana
>> Digite o telefone: 1234-5678
>> Digite o email: jord@email.com
>> Contato inserido no início.
```

## 🖼️ Parte Visual
![Agenda](AgendaVisual.JPG)
