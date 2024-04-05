# Submissão de desafios de pwn

## Qual padrão devo seguir?

- A aplicação pode ser feita em qualquer linguagem ou imagens linux, desde que esteja containerizada com Docker.
- A aplicação precisa estar em container junto com todas as dependências necessárias. 
- A aplicação precisa ter uma rota de health check.

## Estrutura do projeto

A estrutura do projeto deve seguir da seguinte forma:

Dependências

 - Docker
 - Docker swarm
 - Dockerfile

Para executar o seu serviço em Docker swarm, será necessário seguir estes passos:

```sh
docker swarm init
```

Após a inicialização do Docker swarm na sua máquina, vamos para os passos de disponibilizar o serviço:

Seu Docker deverá utilizar redes criadas a partir deste comando:

```sh

docker network create --driver overlay hackincariri

```
Deverá haver um arquivo docker-compose.yml dentro do projeto que siga a seguinte estrutura:

```yaml

version: "3.8"

services:
  app:
    image: "nome_da_imagem"
    deploy:
      replicas: 1
      restart_policy:
        condition: any
    ports:
      - "8080:8080" # sua porta local deverá ser externalizada
    networks:
      - hackincariri 
    healthcheck:
      test: "curl -f http://localhost:8080/health || exit 1" # sua aplicação deverá retornar 200 nesse path 
      interval: 10s
      timeout: 5s
      retries: 3
      start_period: 20s
networks:
  hackincariri:
    external: true
```

Deverá haver um arquivo Dockerfile como esse abaixo:

```Dockerfile
# Usa uma imagem base do Ubuntu
FROM ubuntu:18.04

# Atualiza os pacotes e instala as dependências necessárias
RUN apt-get update && \
    apt-get install -y \
    wget \
    curl \
    git \
    nano \
    vim \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

# Cria o diretório de trabalho
WORKDIR /home/hackincariri/app

# Baixa o arquivo do Go com permissões adequadas
RUN wget -O go.tar.gz https://golang.org/dl/go1.21.1.linux-amd64.tar.gz

# Extrai o arquivo do Go
RUN tar -C /home/hackincariri -xzf go.tar.gz && \
    rm go.tar.gz

# Define as variáveis de ambiente para Go
ENV PATH $PATH:/home/hackincariri/go/bin
ENV GOPATH /home/hackincariri/go

# Copia o código fonte para o contêiner
COPY . .

# Compila o código Go
RUN go build -o app -buildvcs=false

# Remove o Dockerfile após a compilação
RUN rm -f Dockerfile
RUN rm -f go.mod
RUN rm -f README.md
RUN rm -f main.go

# Adiciona um arquivo somente leitura como root
USER root
RUN touch /root/flag_pwn.txt && chmod 400 /root/flag_pwn.txt
RUN echo "HIK_PWN_6630db853468e9c768a584981349e924" > /root/flag_pwn.txt

# Muda de volta para o usuário não-root
USER hackincariri

# Comando para iniciar o servidor SSH e o servidor Go quando o contêiner for executado
CMD ./app
```

Para executar o seu container será necessário utilizar os seguintes comandos:

Gerar a imagem do Dockerfile:

```sh
docker build . -t "nome_da_imagem"
```

Subir o serviço no Docker swarm a partir do docker-compose.yml:

```sh
docker stack deploy -c docker-compose.yml "nome_do_servico"
```

### Estrutura da pasta do projeto

```sh

├── README.md
└── src
    ├── Dockerfile
    ├── index.js
    └── package.json

```

Recomendamos seguir a estrutra de pastas descrita acima. 

Modifique o arquivo README.md com as informações do seu desafio.

## Como submeter um desafio de pwn

Para submeter o seu desafio, siga o passo a passo abaixo:

1. Crie um repositório privado com o seu desafio.

2. Adicione o email organizacao@hackincariri.com.br como contribuidor do projeto.

3. Acesse ao formulário nesse [link](https://forms.gle/bnVjrsWELCpWpf1g8).

4. Coloque o link do projeto compartilhado.

5. Selecione o tipo do desafio Pwn.

6. Coloque o seu nickname e seu melhor email.

7. Aguarde o nosso contato. ;)


