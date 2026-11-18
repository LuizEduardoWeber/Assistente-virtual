# Assistente ESP32: série de vídeos

Projeto feito em vídeos curtos, do zero, para quem está começando em eletrônica. A ideia é construir um **assistente com rosto**, passo a passo, usando um ESP32 e uma tela OLED. Tudo pode ser testado **de graça, no navegador**, com o simulador Wokwi, e depois montado numa placa real.

Cada vídeo tem uma pasta própria, com o código, as ligações e um README explicando o que foi feito.

---

## Índice dos vídeos

| Vídeo | O que você aprende | Pasta | Status |
|---|---|---|---|
| 1 | Ligar uma tela OLED no ESP32 e fazer um rosto que pisca e muda de expressão | [`video1-rosto`](video1-rosto/) | Disponível |
| 2 | Adicionar um botão e um buzzer (sons) | `video2-botao-buzzer` | Em breve |
| 3 | Buscar o clima pela internet e mostrar na tela | `video3-clima` | Em breve |
| 4 | Fantasias para datas festivas | `video4-fantasias` | Em breve |
| 5 | Versão com bateria e carcaça | `video5-bateria` | Em breve |

Links dos vídeos no TikTok: _(cole aqui o link de cada vídeo conforme for publicando)_

---

## O que você vai usar na série

| Peça | Observação |
|---|---|
| ESP32 | Modelo WROOM (DevKit). No Wokwi: **ESP32 DevKit** |
| Tela OLED 0,96" (128x64) | Controlador **SSD1306**, comunicação **I2C** |
| Botão | A partir do vídeo 2 |
| Buzzer | A partir do vídeo 2 |

Você não precisa comprar nada para começar: o Wokwi simula todas as peças.

---

## Como usar este repositório

### No Wokwi (sem comprar nada)
1. Acesse o [Wokwi](https://wokwi.com) e crie um projeto **ESP32** com o modelo **Arduino**. O código deve ficar em `sketch.ino`.
2. Abra a pasta do vídeo que você quer testar aqui no GitHub.
3. Cole o conteúdo do arquivo `.ino` no `sketch.ino`.
4. Cole o conteúdo do `libraries.txt` na aba de bibliotecas.
5. Clique em **Play**.

### Na placa real (Arduino IDE)
1. Instale o suporte ao ESP32 na Arduino IDE.
2. Em **Ferramentas → Placa**, escolha **ESP32 Dev Module**.
3. Instale as bibliotecas listadas no `libraries.txt` da pasta do vídeo.
4. Monte as ligações descritas no README da pasta e clique em **Carregar**.

---

## Estrutura do repositório

```
assistente-esp32/
├── README.md                 (este arquivo: índice da série)
├── video1-rosto/
│   ├── README.md
│   ├── rosto.ino
│   ├── diagram.json
│   └── libraries.txt
├── video2-botao-buzzer/      (em breve)
├── video3-clima/             (em breve)
└── ...
```

Cada pasta é independente: você pode pular direto para o vídeo que te interessa.

---

## Dúvidas e sugestões

Abra uma **Issue** aqui no GitHub ou comente no vídeo. Se você criar uma expressão nova ou uma melhoria, compartilhe.

---

## Autor

Estudante de Engenharia Eletrônica.
**TikTok:**  · **Instagram:** @Luiz.weber.eng

---

## Licença

Este projeto está sob a licença **MIT**. Use, modifique e compartilhe à vontade.
