# Submissão de desafios web

## Qual padrão devo seguir?

- A aplicação pode ser feita em qualquer linguagem, desde que esteja containerizada com Docker.
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
      - "3000:3000" # sua porta local deverá ser externalizada
    networks:
      - hackincariri 
    healthcheck:
      test: "curl -f http://localhost:3000/health || exit 1" # sua aplicação deverá retornar 200 nesse path 
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

FROM node:20

WORKDIR /usr/src/app

COPY package*.json ./

RUN npm install

COPY . .

EXPOSE 3000

CMD ["npm", "start"]
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

## Estrutura da pasta do projeto

```sh

├── README.md
└── src
    ├── Dockerfile
    ├── index.js
    └── package.json

```

Recomendamos seguir a estrutra de pastas descrita acima. 

Modifique o arquivo README.md com as informações do seu desafio.

## Como submeter um desafio de web

Para submeter o seu desafio, siga o passo a passo abaixo:

1. Crie um repositório privado com o seu desafio.

2. Adicione o email organizacao@hackincariri.com.br como contribuidor do projeto.

3. Acesse ao formulário nesse [link](https://forms.gle/bnVjrsWELCpWpf1g8).

4. Coloque o link do projeto compartilhado.

5. Selecione o tipo do desafio Web.

6. Coloque o seu nickname e seu melhor email.

7. Aguarde o nosso contato. ;)