# Vídeo 1: rosto na tela OLED

[Voltar ao índice da série](../README.md)

Um rostinho que **pisca** e **muda de expressão** (feliz, surpreso e sonolento) usando só um **ESP32** e uma **tela OLED**. Dá para fazer de graça, direto no navegador, com o simulador Wokwi, ou numa placa real.

> **Vídeo tutorial:** _(cole aqui o link do vídeo no TikTok)_
> **Abrir o projeto pronto no Wokwi:** _(cole aqui o link do projeto compartilhado)_

---

## O que você precisa

| Peça | Observação |
|---|---|
| ESP32 | Modelo WROOM (DevKit). No Wokwi: **ESP32 DevKit** |
| Tela OLED 0,96" (128x64) | Controlador **SSD1306**, comunicação **I2C** |
| 4 fios | Se for montar na placa real, use jumpers |

---

## Ligações

Todo componente precisa de um caminho de ida e outro de volta, e o de volta é o **GND**.

| Pino da tela OLED | Liga no ESP32 | Para que serve |
|---|---|---|
| **VCC** | 3V3 | Energia |
| **GND** | GND | Volta da energia |
| **SDA** | GPIO 27 | Dados |
| **SCL** | GPIO 26 | Relógio (sincronização) |

A comunicação usada se chama **I2C**: só dois fios (SDA e SCL) levam todas as informações para a tela. O endereço da tela é `0x3C`.

---

## Bibliotecas

| Biblioteca | Para que serve | Instalar? |
|---|---|---|
| **Wire** | Comunicação I2C | Não, já vem com o ESP32 |
| **Adafruit GFX Library** | Desenhar formas e textos | Sim |
| **Adafruit SSD1306** | Controlar a tela OLED | Sim |

Resumindo: a **SSD1306** é o "motorista" da tela, e a **GFX** é o "lápis" que desenha.

---

## Como rodar

### Opção 1: no Wokwi (sem comprar nada)
1. Acesse o [Wokwi](https://wokwi.com) e crie um projeto **ESP32** com o modelo **Arduino**. O código deve ficar em `sketch.ino`.
2. Cole o conteúdo de `rosto.ino` no `sketch.ino`.
3. Cole o conteúdo de `libraries.txt` na aba de bibliotecas.
4. _(Opcional)_ Cole o `diagram.json` para as ligações aparecerem prontas. Se preferir, monte o circuito na mão, como no vídeo.
5. Clique em **Play**.

### Opção 2: na placa real (Arduino IDE)
1. Instale o suporte ao ESP32 na Arduino IDE.
2. Em **Ferramentas → Placa**, escolha **ESP32 Dev Module**.
3. Em **Sketch → Incluir Biblioteca → Gerenciar Bibliotecas**, instale **Adafruit GFX Library** e **Adafruit SSD1306**.
4. Abra o `rosto.ino`, monte as ligações da tabela acima e clique em **Carregar**.

---

## Como funciona

- **Expressões:** uma lista (`enum`) com as 3 opções. O programa passa para a próxima a cada 8 segundos.
- **Piscada:** os olhos fecham por 150 ms e abrem de novo, em intervalos aleatórios de 2 a 5 segundos.
- **`millis()` em vez de `delay()`:** o código consulta o relógio interno do ESP32 para saber a hora de piscar e de trocar de expressão. Assim, uma coisa não trava a outra.
- **Desenho:** os olhos e a boca são formados com retângulos, círculos e linhas da biblioteca GFX.

---

## Personalize

| Quer mudar... | Altere... |
|---|---|
| Tempo de cada expressão | `TEMPO_EXPRESSAO` (em milissegundos) |
| Frequência da piscada | os valores de `random(2000, 5000)` |
| Pinos da tela | `PIN_SDA` e `PIN_SCL` |
| Formato dos olhos e da boca | a função `desenharRosto()` |

Dica: tente criar uma **quarta expressão** (brava, triste, apaixonada...). Basta adicionar um nome no `enum`, um novo `case` no `desenharRosto()` e ajustar o `% 3` para `% 4` na função `atualizarExpressao()`.

---

## Arquivos desta pasta

| Arquivo | O que é |
|---|---|
| `rosto.ino` | Código do vídeo 1 |
| `diagram.json` | Ligações para importar no Wokwi |
| `libraries.txt` | Bibliotecas usadas no Wokwi |

---

## Próximo vídeo

No vídeo 2, vamos adicionar um **botão** e um **buzzer**. Veja o andamento da série no [índice](../README.md).

---

## Problemas comuns

| Sintoma | O que conferir |
|---|---|
| Tela preta | Fios **SDA** e **SCL** (não podem estar trocados) e o fio **GND** |
| Erro `SSD1306_SWITCHVCC` | O nome correto é `SSD1306_SWITCHCAPVCC` |
| Erro com `main.c` no Wokwi | O projeto foi criado com o modelo errado. Use o modelo **Arduino** |
| Tela não responde na placa real | O endereço pode ser `0x3D` em vez de `0x3C` |

---

## Autor

Estudante de Engenharia Eletrônica. Siga a série para ver os próximos passos:
**TikTok:** _(seu @)_ · **Instagram:** _(seu @)_

---

## Licença

Este projeto está sob a licença **MIT**. Use, modifique e compartilhe à vontade. Se ele te ajudar, marque o perfil no vídeo
